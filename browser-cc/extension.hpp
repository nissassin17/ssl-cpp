//
//  extension.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef extension_hpp
#define extension_hpp

#include <stdio.h>
#include "exportable.hpp"

class Extension : Exportable{
public:
    enum ExtensionType{
        SIGNATURE_ALGORITHMS = 13,
        NONE = 65535
    };
    vector<uint8_t> toData();
    uint16_t dataLength();
    
private:
    ExtensionType type;
    vector<uint8_t> data;
};

#endif /* extension_hpp */
