//
//  record.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "record.hpp"
#include "util.hpp"

Record::Record() : isCompressed(false), type(HANDSHAKE),
protocolVersion(new ProtocolVersion()), handshake(new Handshake()){//default: create client hello handshake
}

Handshake *Record::getHandshake(){
    return handshake;
}

Record::~Record(){
    delete this->protocolVersion;
    delete this->handshake;
    delete alert;
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

Record::Record(vector<uint8_t> data, size_t offset, void *arg){
    this->type = (ContentType)data[offset];
    offset += CONTENT_TYPE_LENGTH;
    
    this->protocolVersion = new ProtocolVersion(data, offset);
    offset += this->protocolVersion->size();
    
    uint16_t bodyLength = Util::takeData16(data, offset);
    offset += BODY_LENGTH_LENGTH;
    data.resize(offset + bodyLength);


    switch (this->type) {
        case HANDSHAKE:
            handshake = new Handshake(data, offset, arg);
            offset += handshake->size();
            break;
            
        case ALERT:
            alert = new Alert(data, offset);
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