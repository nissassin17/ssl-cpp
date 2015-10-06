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

Handshake::Handshake() : type(CLIENT_HELLO), clientHello(new ClientHello()){//default create client hello request
}

vector<uint8_t> Handshake::toData(){
    vector<uint8_t> data;
    data.push_back(this->type);
    
    vector<uint8_t> body;
    switch (this->type){
        case HELLO_REQUEST:
            break;
        case CLIENT_HELLO:
            body = clientHello->toData();
            break;
        case SERVER_HELLO:
            body = serverHello->toData();
            break;
        case CERTIFICATE:
            body = certificate->toData();
            break;
        case SERVER_KEY_EXCHANGE:
            body = serverKeyExchange->toData();
            break;
        case CERTIFICATE_REQUEST:
            break;
        case SERVER_HELLO_DONE:
            body = serverHelloDone->toData();
            break;
        case CERTIFICATE_VERIFY:
            break;
        case CLIENT_KEY_EXCHANGE:
            break;
        case FINISHED:
            break;
        default://none
            break;
    }

    
    uint32_t length = (uint32_t)body.size();//uint24_t
    Util::addData24(data, length);
    Util::addData(data, body);
    //    cout << "#begin" << endl << Util::readableForm(data) << endl;
    
    return data;
}

size_t Handshake::size(){
    size_t size = 0;
    
    switch (this->type){
        case HELLO_REQUEST:
            break;
        case CLIENT_HELLO:
            size = clientHello->size();
            break;
        case SERVER_HELLO:
            size = serverHello->size();
            break;
        case CERTIFICATE:
            size = certificate->size();
            break;
        case SERVER_KEY_EXCHANGE:
            size = serverKeyExchange->size();
            break;
        case CERTIFICATE_REQUEST:

            break;
        case SERVER_HELLO_DONE:
            size = serverHelloDone->size();
            break;
        case CERTIFICATE_VERIFY:
            break;
        case CLIENT_KEY_EXCHANGE:
            break;
        case FINISHED:
            break;
        default://none
            break;
    }

    return 1 + 3 + size;
}

Handshake::~Handshake(){
    delete clientHello;
    delete serverHello;
    delete certificate;
    delete serverKeyExchange;
    delete serverHelloDone;
}

ServerHello *Handshake::getServerHello(){
    return serverHello;
}

Handshake::Handshake(vector<uint8_t> data, size_t offset, void *arg){
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
            break;
        case CERTIFICATE:
            this->certificate = new Certificate(data, offset);
            break;
        case SERVER_KEY_EXCHANGE:
            this->serverKeyExchange = new ServerKeyExchange(((ServerHello*)arg)->getCipherSuite()->encryptType(), data, offset);
            break;
        case CERTIFICATE_REQUEST:
            break;
        case SERVER_HELLO_DONE:
            this->serverHelloDone = new ServerHelloDone(data, offset);
            break;
        case CERTIFICATE_VERIFY:
            break;
        case CLIENT_KEY_EXCHANGE:
            break;
        case FINISHED:
            break;
        default: //NONE://default
            break;
    }
}
