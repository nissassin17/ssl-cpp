//
//  protocol-version.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef protocol_version_hpp
#define protocol_version_hpp

#include <stdio.h>
#include <cstdint>

#include <vector>
#include "exportable.hpp"

#define SSL_VERSION_MAJOR 3
#define SSL_VERSION_MINOR 3

using namespace std;

class ProtocolVersion : public Exportable{
public:
    ProtocolVersion();
    vector<uint8_t> toData();
private:
    uint8_t major, minor;
};

#endif /* protocol_version_hpp */
