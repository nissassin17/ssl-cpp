//
//  util.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright �� 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef util_hpp
#define util_hpp


#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

class Util {
public:
	static void writeToFile(const string &filename,
			const vector<uint8_t> &data);

	static void addData(vector<uint8_t> &data, uint8_t value);
	static void addData(vector<uint8_t> &data, uint16_t value);
	static void addData(vector<uint8_t> &data, uint32_t value);
	static void addData(vector<uint8_t> &data, uint64_t value);
	static void addData24(vector<uint8_t> &data, uint32_t value);
	static void addData(vector<uint8_t> &data, const vector<uint8_t>& toAdd);

	static uint8_t takeData8(const vector<uint8_t> &data, size_t offset = 0);
	static uint16_t takeData16(const vector<uint8_t> &data, size_t offset = 0);
	static uint32_t takeData32(const vector<uint8_t> &data, size_t offset = 0);
	static uint32_t takeData24(const vector<uint8_t> &data, size_t offset = 0);
	static uint64_t takeData64(const vector<uint8_t> &data, size_t offset = 0);
	static vector<uint8_t> takeData(const vector<uint8_t> &data, size_t length,
			size_t offset = 0);

	static string readableForm(const vector<uint8_t> &data);

	static long long vectorToInt(const vector<uint8_t> &vec);
};

#endif /* util_hpp */
