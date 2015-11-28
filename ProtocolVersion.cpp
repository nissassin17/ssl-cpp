//
//  protocol-version.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include "ProtocolVersion.hpp"

ProtocolVersion::ProtocolVersion(uint8_t major, uint8_t minor) :
		major(major), minor(minor) {
}

size_t ProtocolVersion::size() const {
	return 2;
}

ProtocolVersion::ProtocolVersion(const vector<uint8_t> &data, size_t offset) {
	this->major = data[offset];
	this->minor = data[offset + 1];
}

vector<uint8_t> ProtocolVersion::toData() const {
	vector<uint8_t> data;
	data.push_back(major);
	data.push_back(minor);
	return data;

}
