//
//  random.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "random.hpp"
#include "util.hpp"
#include <ctime>
#include <cstdlib>

Random::Random(){
    time_t t;
    this->gmtUnixTime = (uint32_t)time(&t);
    srand(this->gmtUnixTime);
    for(int i = 0; i < RANDOM_BYTES_NUM / 4; i++){
        uint32_t r = rand();
        for(int j = 0; j < 3; j++){
            this->randomBytes[i * 4 + j] = r & ((1 << 8) - 1);
            r <<= 8;
        }
        
    }
}

vector<uint8_t> Random::toData(){
    vector<uint8_t> data;
    Util::addData(data, (uint32_t)this->gmtUnixTime);
    data.insert(data.end(), this->randomBytes, this->randomBytes + RANDOM_BYTES_NUM);
    return data;
}