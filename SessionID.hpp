//
//  session-id.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef session_id_hpp
#define session_id_hpp

#include <cstdint>
#include <vector>

#include "Exportable.hpp"

using namespace std;

class SessionID: public Exportable {
public:
	virtual vector<uint8_t> toData() const;
	virtual size_t size() const;
	SessionID(const vector<uint8_t> &data, size_t offset = 0);
	SessionID();
private:
	vector<uint8_t> id;
};

#endif /* session_id_hpp */
