//
//  server-dh-params.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "server-dh-params.hpp"

ServerDHParams::ServerDHParams(vector<uint8_t> data, size_t offset){
    uint16_t length = Util::takeData16(data, offset);
    offset += 2;
    
    this->dhP = Util::takeData(data, length, offset);
    offset += this->dhP.size();
    
    length = Util::takeData16(data, offset);
    offset += 2;
    this->dhG = Util::takeData(data, length, offset);
    offset += this->dhG.size();
    
    length = Util::takeData16(data, offset);
    offset += 2;
    this->dhYs = Util::takeData(data, length, offset);
    offset += this->dhYs.size();

}

size_t ServerDHParams::size(){
    size_t result(0);
    result += 2 + this->dhG.size();
    result += 2 + this->dhP.size();
    result += 2 + this->dhYs.size();
    return result;
}