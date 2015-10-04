//
//  record.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "record.hpp"
#include "util.hpp"

Record::Record(){//default: create client hello handshake
    this->type = HANDSHAKE;
    this->handshake = new Handshake();
    this->isCompress = false;
}

vector<uint8_t> Record::toData(){
    vector<uint8_t> result;
    vector<uint8_t> bodyData;
    
    result.push_back(this->type);
    Util::addData(result, this->protocolVersion.toData());
    

    switch(this->type){
        case CHANGE_CIPHER_SPEC:
            break;
        case ALERT:
            break;
        case HANDSHAKE:
            bodyData = this->handshake->toData();
            break;
        case APPLICATION_DATA:
            break;
        default:
            break;
    }
    uint16_t length = bodyData.size();
    result.push_back(length >> 8);
    result.push_back(length & ((1 << 8) - 1));
    Util::addData(result, bodyData);

    return result;
}

Record::Record(vector<uint8_t> data, size_t offset){
    this->type = (ContentType)data[offset];
    offset += CONTENT_TYPE_LENGTH;
    
    this->protocolVersion = ProtocolVersion(data, offset);
    offset += this->protocolVersion.size();
    
    offset += BODY_LENGTH_LENGTH;

    switch (this->type) {
        case HANDSHAKE:
            this->handshake = new Handshake(data, offset);
            offset += this->handshake->size();
            break;
            
        default:
            break;
    }
}

size_t Record::size(){
    size_t ret(CONTENT_TYPE_LENGTH + this->protocolVersion.size() + BODY_LENGTH_LENGTH);
    
    switch (this->type){
        case HANDSHAKE:
            ret += this->handshake->size();
            break;
        default:
            break;
    }
    
    return ret;
}

Record::~Record(){
    delete this->handshake;
}
