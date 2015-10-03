//
//  extension.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "extension.hpp"
#include "util.hpp"

vector<uint8_t> Extension::toData(){
    vector<uint8_t> data;
    Util::addData(data, (uint16_t)this->type);
    Util::addData(data, (uint16_t)this->data.size());
    data.insert(data.end(), this->data.begin(), this->data.end());
    return data;
}
uint16_t Extension::dataLength(){
    return 2 + 2 + this->data.size();
}