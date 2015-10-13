/*
 * BitUtil.cpp
 *
 *  Created on: Oct 13, 2015
 *      Author: nissassin17
 */

#include "BitUtil.hpp"

bool BitUtil::isBitOn(long long val, int bitNo) {
	return (val >> bitNo) & 1b;
}

bool BitUtil::isBitOff(long long val, int bitNo) {
	return (val >> bitNo) & 1b == 0b;
}

long long BitUtil::turnBitOn(long long val, int bitNo) {
	return val | (1ll << bitNo);
}

long long BitUtil::turnBitOff(long long val, int bitNo) {
	return val & ~(1 << bitNo);
}

uint8_t BitUtil::filterByte(long long val, int lastBitNo) {
	return (val >> lastBitNo) & ((1 << 8) - 1);
}

uint16_t BitUtil::filterWord(long long val, int lastBitNo) {
	return (val >> lastBitNo) & ((1 << 16) - 1);
}

long long BitUtil::append(long long val, long long data, int nBit) {
	return (val << nBit) + (data & ((1 << nBit) - 1));
}

long long BitUtil::filter(long long val, int nBit, int lastBitNo) {
	return (val >> lastBitNo) & ((1 << nBit) - 1);
}

long long BitUtil::cutLastBits(long long val, int nBit) {
	return val >> nBit;
}

bool BitUtil::isAllOne(long long val, int nBit, int lastBitNo) {
	return BitUtil::filter(val, nBit, lastBitNo) == (1 << nBit) - 1;
}

bool BitUtil::isAllZero(long long val, int nBit, int lastBitNo) {
	return BitUtil::filter(val, nBit, lastBitNo) == 0b;
}
