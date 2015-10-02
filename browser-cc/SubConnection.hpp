//
//  SubConnection.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef SubConnection_hpp
#define SubConnection_hpp

#include <stdio.h>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <vector>

using namespace std;

class SubConnection{
private:
    int sock;
    string ip;
    struct sockaddr_in server;
public:
    SubConnection(string ip);
    void doConnect();
    void doSend(vector<uint8_t> request);
    vector<uint8_t> doReceive();
};

#endif /* SubConnection_hpp */
