//
//  change-cipher-spec.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef change_cipher_spec_hpp
#define change_cipher_spec_hpp

#include <stdio.h>
#include "util.hpp"
#include "exportable.hpp"

class ChangeCipherSpec : public Exportable {
public:
    ChangeCipherSpec();
    ~ChangeCipherSpec();
    size_t size();
    vector<uint8_t> toData();
private:
    enum ChangeCipherSpecType{
        CHANGE_CIPHER_SPEC = 1,
        NONE = 255
    };
    ChangeCipherSpecType type;
};

#endif /* change_cipher_spec_hpp */
