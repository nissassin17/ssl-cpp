//
//  random.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef random_hpp
#define random_hpp


#include <cstdint>
#include <vector>

#include "Exportable.hpp"

using namespace std;

class Random : public Exportable{
public:
	Random();
	vector<uint8_t> toData() const ;
	size_t size() const;
	Random(const vector<uint8_t> &data, size_t offset = 0);
private:
	static const int RANDOM_BYTES_NUM = 28;
	uint32_t gmtUnixTime;
	uint8_t randomBytes[RANDOM_BYTES_NUM];
};

#endif /* random_hpp */
