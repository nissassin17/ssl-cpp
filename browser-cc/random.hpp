//
//  random.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef random_hpp
#define random_hpp

#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>

using namespace std;

class Random {
public:
	Random();
	vector<uint8_t> toData();
	size_t size();
	Random(vector<uint8_t> &data, size_t offset = 0);
private:
	static const int RANDOM_BYTES_NUM = 28;
	uint32_t gmtUnixTime;
	uint8_t randomBytes[RANDOM_BYTES_NUM];
};

#endif /* random_hpp */
