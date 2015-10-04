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

class Extension : public Exportable{
public:
    enum ExtensionType{
        SIGNATURE_ALGORITHMS = 13,
        NONE = 65535
    };
    vector<uint8_t> toData();
    size_t size();
    Extension(vector<uint8_t> data, size_t offset = 0);
    Extension(ExtensionType type = NONE);
    
    
private:
    ExtensionType type;
    vector<uint8_t> data;
};

#endif /* extension_hpp */
