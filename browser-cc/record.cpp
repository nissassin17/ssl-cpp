//
//  record.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "record.hpp"

Record::Record(){//default: create client hello handhshake
    this->type = HANDSHAKE;
    this->handshake = new Handshake();
}

vector<uint8_t> Record::toData(){
    vector<uint8_t> result;
    vector<uint8_t> bodyData;
    
    result.push_back(this->type);
    bodyData = this->protocolVersion.toData();
    result.insert(result.end(), bodyData.begin(), bodyData.end());
    

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
    result.insert(result.end(), bodyData.begin(), bodyData.end());

    return result;
}

Record::~Record(){
    delete this->handshake;
}