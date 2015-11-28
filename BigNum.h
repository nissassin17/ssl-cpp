/*
 * BigNum.h
 *
 *  Created on: Nov 26, 2015
 *      Author: nissassin17
 */

#ifndef BIGNUM_H_
#define BIGNUM_H_

#include <vector>
using namespace std;
class BigNum {
public:
	BigNum(vector<uint8_t> const& data, bool const& negative = false);
	BigNum(long long const& digit);
	vector<uint8_t> toVector() const;
	BigNum exponent(long long const& exponent,
			BigNum const& modulus = BigNum(0)) const;

	BigNum operator*(BigNum const& operand) const;
	BigNum operator-(BigNum const& operand) const;
	BigNum operator+(BigNum const& operand) const;
	BigNum operator-() const;
	BigNum operator%(BigNum const& operand) const;
	BigNum operator/(BigNum const& operand) const;
	BigNum abs() const;
	bool operator==(BigNum const& operand) const;
	bool operator!=(BigNum const& operand) const;
	bool operator<(BigNum const& operand) const;
	bool isNegative() const;

private:
	//digits are in reverse order
	vector<uint8_t> data;
	void refine();
	bool negative;

	/**
	 * result must be between 0 and 2^8-1
	 */
	uint8_t smallDivide(BigNum const& devider);
};

#endif /* BIGNUM_H_ */
