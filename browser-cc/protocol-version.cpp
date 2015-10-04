//
//  protocol-version.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "protocol-version.hpp"

ProtocolVersion::ProtocolVersion(uint8_t major, uint8_t minor) :
major(major),
minor(minor){
}

size_t ProtocolVersion::size(){
    return 2;
}

ProtocolVersion::ProtocolVersion(vector<uint8_t> &data, size_t offset){
    this->major = data[offset];
    this->minor = data[offset + 1];
}

vector<uint8_t> ProtocolVersion::toData(){
    return vector<uint8_t>({this->major, this->minor});

}
