//
//  record.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "record.hpp"

Record::Record(ContentType type){
    this->type = type;
}

vector<uint8_t> Record::toData(){
    vector<uint8_t> result;
    
    result.push_back(this->type);
    
    vector<uint8_t> bodyData;
    switch(this->type){
        case CHANGE_CIPHER_SPEC:
            break;
        case ALERT:
            break;
        case HANDSHAKE:
            bodyData = this->handshake->getData();
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