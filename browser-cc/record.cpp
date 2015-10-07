 //
//  record.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "record.hpp"
#include "util.hpp"
#include "err.hpp"

Record::Record(ContentType type): type(type){
    switch (type){
        case CHANGE_CIPHER_SPEC:
            changeCipherSpec = new ChangeCipherSpec();
            break;
        default:
            break;
    }
}

Record::Record(Handshake::HandshakeType handshakeType, void *arg, void *arg2) : isCompressed(false),
protocolVersion(new ProtocolVersion()){//default: create client hello handshake
    type = HANDSHAKE;
    switch (handshakeType){
        case Handshake::CLIENT_KEY_EXCHANGE:
            handshake = new Handshake(handshakeType, arg, arg2);
            break;
        case Handshake::CLIENT_HELLO:
            handshake = new Handshake(Handshake::CLIENT_HELLO);
            break;
        case Handshake::FINISHED:
            handshake = new Handshake(Handshake::FINISHED);
            break;
        default:
            break;
    }
}

Alert *Record::getAlert(){
    return alert;
}

Record::ContentType Record::getType(){
    return type;
}

Handshake *Record::getHandshake(){
    return handshake;
}

Record::~Record(){
    delete this->protocolVersion;
    delete this->handshake;
    delete changeCipherSpec;
    delete alert;
}

vector<uint8_t> Record::toData(){
    vector<uint8_t> bodyData;
    vector<uint8_t> data;
    
    Util::addData(data, (uint8_t)this->type);
    Util::addData(data, this->protocolVersion->toData());
    
    switch (this->type){
		case CHANGE_CIPHER_SPEC :
            bodyData = changeCipherSpec->toData();
			break;
		case ALERT :
            bodyData = alert->toData();
			break;
		case HANDSHAKE :
            bodyData = handshake->toData();
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

Record::Record(vector<uint8_t> &data, size_t offset, void *arg){
    this->type = (ContentType)data[offset];
    offset += CONTENT_TYPE_LENGTH;
    
    this->protocolVersion = new ProtocolVersion(data, offset);
    offset += this->protocolVersion->size();
    
    uint16_t bodyLength = Util::takeData16(data, offset);
    offset += BODY_LENGTH_LENGTH;
    
    //through error if not enough data
    if (offset + bodyLength > data.size())
        throw Err(Err::DECODING);
    //copy the fragment part
    vector<uint8_t> fragment(data.begin() + offset, data.begin() + offset + bodyLength);
    //reset offset
    offset = 0;
//    data.resize(offset + bodyLength);


    switch (this->type) {
        case HANDSHAKE:
            handshake = new Handshake(fragment, offset, arg);
            offset += handshake->size();
            break;
            
        case ALERT:
            alert = new Alert(fragment, offset);
            offset += alert->size();
            break;
            
        default:
            break;
    }
}

size_t Record::size(){
    size_t ret(CONTENT_TYPE_LENGTH + this->protocolVersion->size() + BODY_LENGTH_LENGTH);
    switch (this->type){
        case  CHANGE_CIPHER_SPEC:
            ret += changeCipherSpec->size();
            break;
        case ALERT:
            ret += alert->size();
            break;
        case  HANDSHAKE:
            ret += handshake->size();
            break;
        case APPLICATION_DATA:
            break;
        default:// NONE = 24
            break;
    }

    return ret;
}