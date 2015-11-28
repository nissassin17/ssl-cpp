//
//  change-cipher-spec.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include "ChangeCipherSpec.hpp"

ChangeCipherSpec::ChangeCipherSpec() :
		type(NONE) {
}

size_t ChangeCipherSpec::size() const {
	return 1;
}

vector<uint8_t> ChangeCipherSpec::toData() const {
	vector<uint8_t> data;
	data.push_back((uint8_t) type);
	return data;
}
