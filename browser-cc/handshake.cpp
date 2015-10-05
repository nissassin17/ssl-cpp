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
    Util::addData24(data, length);
    Util::addData(data, body);
//    cout << "#begin" << endl << Util::readableForm(data) << endl;
    
    return data;
}

size_t Handshake::size(){
    size_t result(0);
    result += 1 + 3;
    switch (this->type){
        case HELLO_REQUEST:
            break;
        case CLIENT_HELLO:
            result += this->clientHello->size();
            break;
        case SERVER_HELLO:
            break;
        case CERTIFICATE:
            result += this->certificate->size();
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
    return result;
}

Handshake::Handshake(vector<uint8_t> data, size_t offset){
    this->type = (HandshakeType)data[offset];
    offset ++;
    
    uint32_t length = Util::takeData32(data, offset);
    data.resize(offset + length);
    offset += 3;
    
    switch (this->type){
        case HELLO_REQUEST:
            break;
        case CLIENT_HELLO:
        	break;
        case SERVER_HELLO:
            this->serverHello = new ServerHello(data, offset);
            offset += this->serverHello->size();
        	break;
        case CERTIFICATE:
            this->certificate = new Certificate(data, offset);
            offset += this->certificate->size();
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
        case NONE://default
            break;
    }
}
