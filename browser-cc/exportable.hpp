//
//  exportable.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef exportable_hpp
#define exportable_hpp

#include <stdio.h>
#include <cstdint>
#include <vector>
using namespace std;

class Exportable {
public:
    virtual vector<uint8_t> toData() = 0;
    virtual size_t size() = 0;
};

#endif /* exportable_hpp */
