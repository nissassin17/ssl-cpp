//
//  util.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "util.hpp"

string Util::readableForm(vector<uint8_t> data){
    string result;
    for(int i = 0; i < data.size(); i++){
        if (i && i % 16 == 0)
            result += "\n";
        else
        if (i && i % 8 == 0)
            result += " | ";
        char a[3];
        sprintf(a, "%02x", (uint8_t)data[i]);
        result += " ";
        result += a;
        
    }
    return result;
}

void Util::addData(vector<uint8_t> &data, uint16_t value){
    data.push_back(value >> 8);
    data.push_back(value & ((1 << 8) - 1));
}
void Util::addData(vector<uint8_t> &data, uint32_t value){
    const uint8_t PATTERN = (1 << 8) - 1;
    data.push_back(value >> 24);
    data.push_back((value >> 16) & PATTERN);
    data.push_back((value >> 8) & PATTERN);
    data.push_back(value & PATTERN);
}
void Util::addData(vector<uint8_t> &data, uint64_t value){
    const uint8_t PATTERN = (1 << 8) - 1;
    for(int i = (64 / 8) - 1; i >= 0; i--)
        data.push_back((value >> (i * 8)) & PATTERN);
}
void Util::addData24(vector<uint8_t> &data, uint32_t value){
    const uint8_t PATTERN = (1 << 8) - 1;
    data.push_back(value >> 16);
    data.push_back((value >> 8) & PATTERN);
    data.push_back(value & PATTERN);
}
