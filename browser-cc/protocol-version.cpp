//
//  protocol-version.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "protocol-version.hpp"

ProtocolVersion::ProtocolVersion() :
major(SSL_VERSION_MAJOR),
minor(SSL_VERSION_MINOR){
}

vector<uint8_t> ProtocolVersion::toData(){
    return vector<uint8_t>({this->major, this->minor});

}