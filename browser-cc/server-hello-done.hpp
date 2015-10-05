//
//  server-helllo-done.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef server_helllo_done_hpp
#define server_helllo_done_hpp

#include <stdio.h>
#include "util.hpp"

class ServerHelloDone{
public:
    ServerHelloDone(vector<uint8_t> data, size_t offset = 0);
    size_t size();
};

#endif /* server_helllo_done_hpp */
