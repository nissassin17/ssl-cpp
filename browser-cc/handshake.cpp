//
//  handshake.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "handshake.hpp"
#include <iostream>
#include "util.hpp"
using namespace std;

Handshake::~Handshake(){
    delete this->clientHello;
}

Handshake::Handshake(){//default create client hello request
    this->type = CLIENT_HELLO;
    this->clientHello = new ClientHello();
}

vector<uint8_t> Handshake::toData(){
    vector<uint8_t> data;
    data.push_back(this->type);
    
    vector<uint8_t> body;
    switch (this->type){
        case HELLO_REQUEST:
            break;
        case CLIENT_HELLO:
            body = this->clientHello->toData();
            break;
        case SERVER_HELLO:
            break;
        case CERTIFICATE:
            break;
        case SERVER_KEY_EXCHANGE:
            break;
        case CERTIFICATE_REQUEST:
            break;
        case SERVER_HELO_DONE:
            break;
        case CERTIFICATE_VERIFY:
            break;
        case CLIENT_KEY_EXCHANGE:
            break;
        case FINISHED:
            break;
        default:
            break;
    }
    
    uint32_t length = (uint32_t)body.size();//uint24_t
    data.push_back(length >> 16);
    data.push_back((length >> 8) & ((1 << 8) - 1));
    data.push_back(length & ((1 << 8) - 1));
    data.insert(data.end(), body.begin(), body.end());
//    cout << "#begin" << endl << Util::readableForm(data) << endl;
    
    return data;
}