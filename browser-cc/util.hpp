//
//  util.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef util_hpp
#define util_hpp

#include <stdio.h>
#include <vector>
using namespace std;

class Util{
public:
    static void addData(vector<uint8_t> &data, uint16_t value);
    static void addData(vector<uint8_t> &data, uint32_t value);
    static void addData(vector<uint8_t> &data, uint64_t value);
    static void addData24(vector<uint8_t> &data, uint32_t value);
};

#endif /* util_hpp */
