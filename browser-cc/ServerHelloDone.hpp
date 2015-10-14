//
//  server-helllo-done.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef server_helllo_done_hpp
#define server_helllo_done_hpp


#include <cstdint>
#include <vector>

#include "Exportable.hpp"

class ServerHelloDone: public Exportable {
public:
	ServerHelloDone(const vector<uint8_t> &data, size_t offset = 0);
	virtual size_t size() const;
	virtual ~ServerHelloDone();
};

#endif /* server_helllo_done_hpp */
