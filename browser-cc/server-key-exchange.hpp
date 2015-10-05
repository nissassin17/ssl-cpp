//
//  server-key-exchange.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef server_key_exchange_hpp
#define server_key_exchange_hpp

#include <stdio.h>
#include "util.hpp"

class ServerKeyExchange{
public:
    ServerKeyExchange(vector<uint8_t> data, size_t offset = 0);
    size_t size();
private:
};

#endif /* server_key_exchange_hpp */
