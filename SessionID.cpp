//
//  session-id.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include "SessionID.hpp"
#include "Util.hpp"

vector<uint8_t> SessionID::toData() const {
	vector<uint8_t> data;
	data.push_back(this->id.size());
	Util::addData(data, this->id);
	return data;
}

size_t SessionID::size() const {
	return 1 + this->id.size();
}

SessionID::SessionID(const vector<uint8_t> &data, size_t offset) {
	uint8_t length = data[offset];
	this->id = Util::takeData(data, length, offset + 1);
}

SessionID::SessionID() {
}

