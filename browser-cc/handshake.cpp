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

Handshake::Handshake() : type(CLIENT_HELLO), body(new ClientHello()){//default create client hello request
}

vector<uint8_t> Handshake::toData(){
    vector<uint8_t> data;
    data.push_back(this->type);
    
    vector<uint8_t> body;
    switch (this->type){
        case HELLO_REQUEST:
            break;
        case CLIENT_HELLO:
            body = dynamic_cast<ClientHello*>(this->body)->toData();
            break;
        case SERVER_HELLO:
            body = dynamic_cast<ServerHello*>(this->body)->toData();
            break;
        case CERTIFICATE:
            body = dynamic_cast<Certificate*>(this->body)->toData();
            break;
        case SERVER_KEY_EXCHANGE:
            body = dynamic_cast<ServerKeyExchange*>(this->body)->toData();
            break;
        case CERTIFICATE_REQUEST:
            break;
        case SERVER_HELLO_DONE:
            body = dynamic_cast<ServerHelloDone*>(this->body)->toData();
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
            size = dynamic_cast<ClientHello*>(this->body)->size();
            break;
        case SERVER_HELLO:
            size = dynamic_cast<ServerHello*>(this->body)->size();
            break;
        case CERTIFICATE:
            size = dynamic_cast<Certificate*>(this->body)->size();
            break;
        case SERVER_KEY_EXCHANGE:
            size = dynamic_cast<ServerKeyExchange*>(this->body)->size();
            break;
        case CERTIFICATE_REQUEST:
            break;
        case SERVER_HELLO_DONE:
            size = dynamic_cast<ServerHelloDone*>(this->body)->size();
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
    delete this->body;
}

void *Handshake::getBody(){
    return this->body;
}

//Handshake *Handshake::certificate(vector<uint8_t> data, size_t offset){
//    return new Handshake(CERTIFICATE, data, offset);
//}
//Handshake *Handshake::serverKeyExchange(ServerHello *serverHello, vector<uint8_t> data, size_t offset){
//    return new Handshake(SERVER_KEY_EXCHANGE, serverHello, data, offset);
//}
//Handshake *Handshake::serverHelloDone(ServerHello *serverHello, vector<uint8_t> data, size_t offset){
//    return new Handshake(SERVER_HELLO_DONE, serverHello, data, offset);
//}
//Handshake *Handshake::certificateRequest(ServerHello *serverHello, vector<uint8_t> data, size_t offset){
//    return new Handshake(CERTIFICATE_REQUEST, serverHello, data, offset);
//}
//
//Handshake::Handshake(HandshakeType type, vector<uint8_t> data, size_t offset) : type(type){
//    switch (type){
//        case CERTIFICATE:
//            this->body = new Certificate(data, offset);
//
//            break;
//        default:
//            break;
//    }
//    offset += this->body->size();
//}

//Handshake::Handshake(HandshakeType type, ServerHello *serverHello, vector<uint8_t> data, size_t offset) : type(type){
//    switch (type){
//        case SERVER_KEY_EXCHANGE:
//            this->body = new ServerKeyExchange(serverHello->getCipherSuite()->encryptType(), data, offset);
//            break;
//        default:
//            break;
//    }
//    offset += this->body->size();
//}

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
            this->body = new ServerHello(data, offset);
            break;
        case CERTIFICATE:
            this->body = new Certificate(data, offset);
            break;
        case SERVER_KEY_EXCHANGE:
            this->body = new ServerKeyExchange(((ServerHello*)((Handshake*)arg)->getBody())->getCipherSuite()->encryptType(), data, offset);
            break;
        case CERTIFICATE_REQUEST:
            break;
        case SERVER_HELLO_DONE:
            this->body = new ServerHelloDone(data, offset);
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
