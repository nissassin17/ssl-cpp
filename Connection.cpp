//
//  connection.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>
#include <string>

#include "Log.h"
#include "Connection.hpp"
#include "Err.hpp"

using namespace std;

Connection::Connection(const string &hostname, bool isSsl) :
		isConnecting(false), activatingConnection(NULL) {
	const int SSL_PORT = 443;
	const int HTTP_PORT = 80;

	//get ip list
	vector<string> ipList = Connection::ipListFromHostname(hostname);
	for (int i = 0; i < ipList.size(); i++)
		this->subConnections.push_back(
				shared_ptr<SubConnection>(
						new SubConnection(ipList[i],
								isSsl ? SSL_PORT : HTTP_PORT)));
}

vector<string> Connection::ipListFromHostname(const string& hostname) {
	vector<string> ipList;

	struct addrinfo hints, *server_info;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // AF_INET6 for IPv6
	hints.ai_socktype = SOCK_STREAM;

	int er = getaddrinfo(hostname.c_str(), "http", &hints, &server_info);
	if (er != 0)
		throw Err(Err::CannotResolveHostname, gai_strerror(er));

	//iterate result
	//first loop to get number of result
	for (struct addrinfo *it = server_info; it != NULL; it = it->ai_next) {
		struct sockaddr_in *host = (struct sockaddr_in*) it->ai_addr;
		char *sin = inet_ntoa(host->sin_addr);
		ipList.push_back(string(sin));
	}
	freeaddrinfo(server_info);

	return ipList;
}

void Connection::send(const vector<uint8_t> &request) {
	Log::info << "Prepare to send request" << endl;
	if (this->isConnecting) {	//not first time. so just send
		if (not this->activatingConnection)
			throw Err(Err::NoConnection);
		Log::info
				<< "Connect is already established. Just try sending the request"
				<< endl;
		this->activatingConnection->doSend(request);
	} else {	//first time
		Log::info
				<< "First time sending request. Try establishing and find available connection out."
				<< endl;
		this->isConnecting = true;
		for (int i = 0; i < this->subConnections.size(); i++) {
			try {
				Log::info << "Try connection number " << (i + 1) << " with IP "
						<< this->subConnections[i]->getIp() << endl;
				this->subConnections[i]->doConnect();
				Log::info << "Connect ok. Send request now" << endl;
				this->subConnections[i]->doSend(request);
				//wait for error until here
				this->activatingConnection = this->subConnections[i];
				break;
			} catch (Err& err) {
				Log::warn << "Connecting via connection number " << (i + 1)
						<< " had failed" << endl;
			}
		}
	}
}

vector<uint8_t> Connection::receive() const {
	Log::info << "Receiving data" << endl;
	if (!this->isConnecting)
		throw Err(Err::DontSendButReceive);
	if (not activatingConnection)
		throw Err(Err::NoConnection);
	return this->activatingConnection->doReceive();
}
