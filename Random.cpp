//
//  random.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include <stddef.h>
#include <cstdlib>
#include <ctime>
#include <initializer_list>

#include "Random.hpp"
#include "Util.hpp"
#include "BitUtil.hpp"

Random::Random() {
	time_t t;
	this->gmtUnixTime = (uint32_t) time(&t);
	srand(this->gmtUnixTime);
	for (int i = 0; i < RANDOM_BYTES_NUM / 4; i++) {
		uint32_t r = rand();
		for (int j = 0; j < 3; j++) {
			this->randomBytes[i * 4 + j] = BitUtil::filterByte(r);
			r = (uint32_t) BitUtil::cutLastBits(r, 8);
		}

	}
}

size_t Random::size() const {
	return 4 + RANDOM_BYTES_NUM * 1;
}

Random::Random(const vector<uint8_t> &data, size_t offset) {
	this->gmtUnixTime = Util::takeData32(data, offset);
	offset += 4;

	for (int i = 0; i < RANDOM_BYTES_NUM; i++)
		this->randomBytes[i] = data[offset + i];
}

vector<uint8_t> Random::toData() const {
	vector<uint8_t> data;
	Util::addData(data, (uint32_t) this->gmtUnixTime);
	data.insert(data.end(), this->randomBytes,
			this->randomBytes + RANDOM_BYTES_NUM);
	return data;
}
