//
//  change-cipher-spec.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "change-cipher-spec.hpp"

ChangeCipherSpec::ChangeCipherSpec(){
    type = NONE;
}

ChangeCipherSpec::~ChangeCipherSpec(){
    
}

size_t ChangeCipherSpec::size(){
    return 1;
}

vector<uint8_t> ChangeCipherSpec::toData(){
    return vector<uint8_t>({(uint8_t)type});
}