//
//  util.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright �� 2015 Nissassin Seventeen. All rights reserved.
//

#include <cstdio>
#include <initializer_list>
#include <iterator>
#include <string>
#include <iostream>
#include <fstream>
#include "Util.hpp"
#include "BitUtil.hpp"

using namespace std;

long long Util::vectorToInt(const vector<uint8_t> &vec) {
	long long ret = 0ll;
	for (int i = 0; i < vec.size(); i++)
		ret = BitUtil::append(ret, vec[i], 8);
	return ret;
}

void Util::addData(vector<uint8_t> &data, uint8_t value) {
	data.push_back(value);
}

uint8_t Util::takeData8(const vector<uint8_t> &data, size_t offset) {
	return data[offset];
}

void Util::addData(vector<uint8_t> &data, uint16_t value) {
	data.push_back(BitUtil::filterByte(value, 8));
	data.push_back(BitUtil::filterByte(value));
}
void Util::addData(vector<uint8_t> &data, uint32_t value) {
	data.push_back(BitUtil::filterByte(value, 24));
	data.push_back(BitUtil::filterByte(value, 16));
	data.push_back(BitUtil::filterByte(value, 8));
	data.push_back(BitUtil::filterByte(value));
}
void Util::addData(vector<uint8_t> &data, const vector<uint8_t> &toAdd) {
	data.insert(data.end(), toAdd.begin(), toAdd.end());
}

void Util::addData(vector<uint8_t> &data, uint64_t value) {
	for (int i = (64 / 8) - 1; i >= 0; i--)
		data.push_back(BitUtil::filterByte(value, i * 8));
}
void Util::addData24(vector<uint8_t> &data, uint32_t value) {
	data.push_back(BitUtil::filterByte(value, 16));
	data.push_back(BitUtil::filterByte(value, 8));
	data.push_back(BitUtil::filterByte(value));
}

uint16_t Util::takeData16(const vector<uint8_t> &data, size_t offset) {
	return BitUtil::append(data[offset], data[offset + 1], 8);
}

uint32_t Util::takeData24(const vector<uint8_t> &data, size_t offset) {
	const int SIZE = 3;
	uint32_t result(0);
	for (int i = 0; i < SIZE; i++) {
		result = (uint32_t) BitUtil::append(result, data[offset], 8);
		offset++;
	}
	return result;
}

uint64_t Util::takeData64(const vector<uint8_t> &data, size_t offset) {
	const int SIZE = 8;
	uint64_t result(0);
	for (int i = 0; i < SIZE; i++) {
		result = BitUtil::append(result, data[offset], 8);
		offset++;
	}

	return result;
}

uint32_t Util::takeData32(const vector<uint8_t> &data, size_t offset) {
	const int SIZE = 4;
	uint32_t result(0);
	for (int i = 0; i < SIZE; i++) {
		result = (uint32_t) BitUtil::append(result, data[offset], 8);
	}
	return result;
}

vector<uint8_t> Util::takeData(const vector<uint8_t> &data, size_t length,
		size_t offset) {
	return vector<uint8_t>(data.begin() + offset,
			data.begin() + offset + length);
}

