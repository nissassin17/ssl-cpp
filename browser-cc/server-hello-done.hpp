//
//  server-helllo-done.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef server_helllo_done_hpp
#define server_helllo_done_hpp

#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>

#include "exportable.hpp"

class ServerHelloDone: public Exportable {
public:
	ServerHelloDone(vector<uint8_t> &data, size_t offset = 0);
	size_t size();
	virtual ~ServerHelloDone();
};

#endif /* server_helllo_done_hpp */
