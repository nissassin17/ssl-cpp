//
//  SubConnection.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef SubConnection_hpp
#define SubConnection_hpp

#include <cstdint>
#include <iostream>
#include <vector>
#include <netinet/in.h>

struct sockaddr_in;

using namespace std;

class SubConnection {
private:
	int sock;
	string ip;
	struct sockaddr_in server;
public:
	SubConnection(string ip, int port);
	void doConnect() const;
	void doSend(vector<uint8_t> request) const;
	vector<uint8_t> doReceive() const;
	const string& getIp() const;

};

#endif /* SubConnection_hpp */
