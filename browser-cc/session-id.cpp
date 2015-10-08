//
//  session-id.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "session-id.hpp"
#include "util.hpp"

SessionID::SessionID() {

}

vector<uint8_t> SessionID::toData() {
	vector<uint8_t> data;
	data.push_back(this->id.size());
	Util::addData(data, this->id);
	return data;
}

size_t SessionID::size() {
	return 1 + this->id.size();
}

SessionID::SessionID(vector<uint8_t> &data, size_t offset) {
	uint8_t length = data[offset];
	this->id = Util::takeData(data, length, offset + 1);
}
