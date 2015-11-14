//
//  SubConnection.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "SubConnection.hpp"


#include <stddef.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

#include "Log.h"
#include "Err.hpp"

extern int errno;

SubConnection::SubConnection(string ip, int port) {
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        throw Err(Err::CannotCreateSock, ip.c_str());
    
    this->server.sin_addr.s_addr = inet_addr(ip.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    /*
     this->server = {
     .sin_addr = {
     .s_addr = inet_addr(ip.c_str())
     },
     .sin_family = AF_INET,
     .sin_port = htons(port)
     };
     */
    
}

void SubConnection::doConnect() const{
    //try connect
    connect(this->sock, (struct sockaddr*) &server, sizeof(server));
    if (errno < 0)
        throw Err(Err::CannotConnect, this->ip.c_str());
}

void SubConnection::doSend(vector<uint8_t> request) const{
    if (send(this->sock, &request[0], request.size(), 0) < 0)
        throw Err(Err::CannotSend, this->ip.c_str());
}

vector<uint8_t> SubConnection::doReceive() const{
    vector<uint8_t> result;
    
    Log::info << "Start receive data (default block size: 2000 bytes)" << endl;
    do {
        const int RESPONSE_SIZE = 2000;
        char response[RESPONSE_SIZE];
        ssize_t size = recv(this->sock, response, RESPONSE_SIZE, 0);
        if (size < 0)
            throw Err(Err::CannotReceive);
        if (size == 0){ //server closed
        	Log::info << "Server closed (finish responding)" << endl;
            break;
        }
        Log::info << "Received " << size << " bytes from server" << endl;
        for (int i = 0; i < size; i++)
            result.push_back(response[i]);
    } while (true);
    Log::info << "Receive response finished" << endl;
    
    return result;
}
