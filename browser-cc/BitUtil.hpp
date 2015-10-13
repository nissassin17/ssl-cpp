/*
 * BitUtil.h
 *
 *  Created on: Oct 13, 2015
 *      Author: nissassin17
 */

#ifndef BITUTIL_HPP_
#define BITUTIL_HPP_

class BitUtil {
public:
	static bool isBitOn(long long val, int bitNo);
	static bool isBitOff(long long val, int bitNo);
	static long long turnBitOn(long long val, int bitNo);
	static long long turnBitOff(long long val, int bitNo);
	static uint8_t filterByte(long long val, int lastBitNo = 0);
	static uint16_t filterWord(long long val, int lastBitNo = 0);
	static long long append(long long val, long long data, int nBit);

	/**
	 * filter nBit bits with last bit no is lastBitNo
	 */
	static long long filter(long long val, int nBit, int lastBitNo = 0);

	static long long cutLastBits(long long val, int nBit);

	static bool isAllOne(long long val, int nBit, int lastBitNo = 0);
	static bool isAllZero(long long val, int nBit, int lastBitNo = 0);

};

#endif /* BITUTIL_HPP_ */
