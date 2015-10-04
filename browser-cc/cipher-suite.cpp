//
//  cipher-suite.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "cipher-suite.hpp"
#include "util.hpp"

CipherSuite::CipherSuite(CipherSuiteType type) : suite(type){
    
}

vector<uint8_t> CipherSuite::toData(){
    uint8_t high(this->suite >> 8);
    uint8_t low(this->suite & ((1 << 8) - 1));
    return vector<uint8_t>({high, low});
}

size_t CipherSuite::size(){
    return 2;
}

CipherSuite::CipherSuite(vector<uint8_t> data, size_t offset){
    this->suite = (CipherSuiteType)Util::takeData16(data, offset);
}