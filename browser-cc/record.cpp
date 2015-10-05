//
//  record.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "record.hpp"
#include "util.hpp"

Record::Record() : isCompressed(false), type(HANDSHAKE), fragment(Handshake()){//default: create client hello handshake
}

vector<uint8_t> Record::toData(){
    vector<uint8_t> result;
    vector<uint8_t> bodyData;
    
    result.push_back(this->type);
    Util::addData(result, this->protocolVersion.toData());
    
    bodyData = this->fragment.toData();
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
    
    uint16_t bodyLength = Util::takeData16(data, offset);
    offset += BODY_LENGTH_LENGTH;
    data.resize(offset + bodyLength);

    switch (this->type) {
        case HANDSHAKE:
            this->fragment =  Handshake(data, offset);

            break;
            
        case ALERT:
            this->fragment =  Alert(data, offset);
            break;
            
        default:
            break;
    }
    offset += this->fragment.size();
}

size_t Record::size(){
    size_t ret(CONTENT_TYPE_LENGTH + this->protocolVersion.size() + BODY_LENGTH_LENGTH);
    ret += this->fragment.size();

    return ret;
}
