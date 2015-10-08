//
//  session-id.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef session_id_hpp
#define session_id_hpp

#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>

using namespace std;

class SessionID {
public:
	vector<uint8_t> toData();
	SessionID();
	size_t size();
	SessionID(vector<uint8_t> &data, size_t offset = 0);
private:
	vector<uint8_t> id;
};

#endif /* session_id_hpp */
