//
//  session-id.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "session-id.hpp"

SessionID::SessionID(){
    
}

vector<uint8_t> SessionID::toData(){
    vector<uint8_t> data;
    data.push_back(this->id.size());
    data.insert(data.end(), this->id.begin(), this->id.end());
    return data;
}