//
//  cipher-suite.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "cipher-suite.hpp"

CipherSuite::CipherSuite(uint16_t type) : suite(type){
    
}

vector<uint8_t> CipherSuite::toData(){
    uint8_t high(this->suite >> 8);
    uint8_t low(this->suite & ((1 << 8) - 1));
    return vector<uint8_t>({high, low});
}