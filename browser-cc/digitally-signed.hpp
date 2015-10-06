//
//  digitally-signed.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef digitally_signed_hpp
#define digitally_signed_hpp

#include <stdio.h>
#include "util.hpp"
#include "exportable.hpp"
#include "server-dh-params.hpp"

class DigitallySigned{
public:
    DigitallySigned(vector<uint8_t> data, size_t offset = 0);
    size_t size();
    ~DigitallySigned();
private:
    uint8_t clientRandom[32];
    uint8_t serverRandom[32];
    ServerDHParams *params;
};

#endif /* digitally_signed_hpp */
