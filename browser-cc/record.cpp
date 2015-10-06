//
//  record.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "record.hpp"
#include "util.hpp"

Record::Record() : isCompressed(false), type(HANDSHAKE), fragment(new Handshake()),
protocolVersion(new ProtocolVersion()){//default: create client hello handshake
}

Record::~Record(){
    delete this->protocolVersion;
    delete this->fragment;
}

vector<uint8_t> Record::toData(){
    vector<uint8_t> bodyData;
    vector<uint8_t> data;
    
    Util::addData(data, (uint8_t)this->type);
    Util::addData(data, this->protocolVersion->toData());
    
    switch (this->type){
		case CHANGE_CIPHER_SPEC :
//			bodyData = dynamic_cast<ChangeCipherSpec*>(this->fragment)->toData();
			break;
		case ALERT :
			bodyData = dynamic_cast<Alert *>(this->fragment)->toData();
			break;
		case HANDSHAKE :
			bodyData = dynamic_cast<Handshake *>(this->fragment)->toData();
			break;
		case APPLICATION_DATA :
//			bodyData = static_cast<ApplicationData *>(this->fragment)->toData();
			break;
		default://case NONE :
			break;
    }
    uint16_t length = bodyData.size();
    Util::addData(data, length);
    Util::addData(data, bodyData);

    return data;
}
//Record::Record(Handshake::HandshakeType shortcut, vector<uint8_t> data, size_t offset){
//    this->type = HANDSHAKE;
//    switch (shortcut){
//        case Handshake::CERTIFICATE:
//            this->fragment =  Handshake::certificate(data, offset);
//            break;
//        default:
//            break;
//    }
//    offset += this->fragment->size();
//
//
//}

//Record::Record(Handshake::HandshakeType shortcut, ServerHello *serverHello, vector<uint8_t> data, size_t offset){
//    this->type = HANDSHAKE;
//    switch (shortcut) {
//        case Handshake::SERVER_HELLO_DONE:
//            this->fragment = Handshake::serverHelloDone(serverHello, data, offset);
//            break;
//            
//            
//        case Handshake::CERTIFICATE_REQUEST:
//            this->fragment = Handshake::certificateRequest(serverHello, data, offset);
//            break;
//            
//        case Handshake::SERVER_KEY_EXCHANGE:
//            this->fragment = Handshake::serverKeyExchange(serverHello, data, offset);
//            break;
//            
//        default:
//            break;
//    }
//    offset += this->fragment->size();
//}

//Record *Record::serverHelloDone(ServerHello *serverHello, vector<uint8_t> data, size_t offset){
//    return new Record(Handshake::SERVER_HELLO_DONE, serverHello, data, offset);
//}
//
//Record *Record::certificate(vector<uint8_t> data, size_t offset){
//    return new Record(Handshake::CERTIFICATE, data, offset);
//}
//
//Record *Record::certificateRequest(ServerHello *serverHello, vector<uint8_t> data, size_t offset){
//    return new Record(Handshake::CERTIFICATE_REQUEST, serverHello, data, offset);
//}
//
//Record *Record::serverKeyExchange(ServerHello *serverHello, vector<uint8_t> data, size_t offset){
//    return new Record(Handshake::SERVER_KEY_EXCHANGE, serverHello, data, offset);
//}

Record::Record(vector<uint8_t> data, size_t offset, void *arg){
    this->type = (ContentType)data[offset];
    offset += CONTENT_TYPE_LENGTH;
    
    this->protocolVersion = new ProtocolVersion(data, offset);
    offset += this->protocolVersion->size();
    
    uint16_t bodyLength = Util::takeData16(data, offset);
    offset += BODY_LENGTH_LENGTH;
    data.resize(offset + bodyLength);

    Handshake *handshake;
    Alert *alert;
    switch (this->type) {
        case HANDSHAKE:
            handshake = new Handshake(data, offset, arg);
            this->fragment =  handshake;
            offset += handshake->size();
            break;
            
        case ALERT:
            alert = new Alert(data, offset);
            this->fragment =  alert;
            break;
            
        default:
            break;
    }
}

size_t Record::size(){
    size_t ret(CONTENT_TYPE_LENGTH + this->protocolVersion->size() + BODY_LENGTH_LENGTH);
    switch (this->type){
        case  CHANGE_CIPHER_SPEC:
            break;
        case ALERT:
            ret += dynamic_cast<Alert*>(fragment)->size();
            break;
        case  HANDSHAKE:
            ret += dynamic_cast<Handshake*>(fragment)->size();
            break;
        case APPLICATION_DATA:
            break;
        default:// NONE = 24
            break;
    }

    return ret;
}

void *Record::getFragment(){
    return (this->fragment);
}
