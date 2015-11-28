/*
 * BigNum.cpp
 *
 *  Created on: Nov 26, 2015
 *      Author: nissassin17
 */
#include <iostream>
#include "BigNum.h"
#include <cmath>

vector<uint8_t> BigNum::toVector() const {
	vector<uint8_t> result(data);
	reverse(result.begin(), result.end());
	return result;
}
bool BigNum::operator!=(BigNum const& operand) const {
	return not operator==(operand);
}
BigNum BigNum::exponent(long long const& exp, BigNum const& modulus) const {
	if (exp == 0)
		return BigNum(1);
	BigNum result(this->exponent(exp >> 1, modulus));

	//square result here
	result = result * result;
	if (modulus != 0)
		result = result % modulus;

	if (exp bitand 1) { //odd
		result = result * *this;
		if (modulus != 0)
			result = result % modulus;
	}

	return result;
}

/**
 * take data in forward order
 * don't forget to reverse it
 */
BigNum::BigNum(const vector<uint8_t>& data, bool const& negative) :
		data(data), negative(negative) {
	reverse(this->data.begin(), this->data.end());
	refine();
}

BigNum::BigNum(const long long& digit) :
		negative(digit < 0) {
	long long t(std::abs(digit));
	while (t > 0) {
		data.push_back(t & ((1 << 8) - 1));
		t >>= 8;
	}
}

void BigNum::refine() {
	while (!data.empty() and *data.rbegin() == 0)
		data.pop_back();
	if (data.empty())
		negative = false;
}

BigNum BigNum::operator *(const BigNum& operand) const {
	std::vector<uint32_t> ret(data.size() + operand.data.size() - 1, 0);
	std::vector<uint8_t> u8ret;
	for (int i = 0; i < data.size(); i++)
		for (int j = 0; j < operand.data.size(); j++) {
			//std::cout << "j: " << j << ". operand.data.size(): " << operand.data.size() << std::endl;
			ret[i + j] += (uint16_t) data[i] * operand.data[j];
		}
	uint32_t carry(0);
	for (std::vector<uint32_t>::iterator it = ret.begin(); it != ret.end();
			it++) {
		*it += carry;
		carry = *it >> 8;
		u8ret.push_back((*it) bitand ((1 << 8) - 1));
	}
	while (carry > 0) {
		u8ret.push_back(carry bitand ((1 << 8) - 1));
		carry >>= 8;
	}

	//redudant because u8ret will be refined in BigNum construction but for sake of logical purpose
//	while(not u8ret.empty() and *u8ret.rbegin() == 0)
//		u8ret.pop_back();

	BigNum bb(0);
	bb.data = u8ret;
	bb.negative = negative xor operand.negative;
	bb.refine();
	return bb;
}

BigNum BigNum::operator -(const BigNum& operand) const {
	return operator+(-operand);
}

BigNum BigNum::operator +(const BigNum& operand) const {
	if (negative)
		return -((-*this) + -operand);
	if (operand.negative) { //compare
		BigNum abs(operand.abs());
		if (operator==(abs))
			return BigNum(0);
		if (operator<(abs))
			return -(abs - *this);
		//do subtract here

		//we are sure here: *this > operand (strictly)
		vector<uint8_t> ret(data);
		int carry = 0;
		for (int i = 0; i < data.size(); i++) {
			if (i < operand.data.size())
				//if digit exists in b
				carry += operand.data[i];
			int tmp = (int) ret[i] - carry;
			if (tmp < 0) {
				carry = 1;
				ret[i] = tmp + (1 << 8);
			} else {
				ret[i] = tmp;
				carry = 0;
			}
		}
		//because *this > operand. carry must be 0 here
		//this refinement is redudant but just because of the sake of logic
		while (not ret.empty() and *ret.rbegin() == 0)
			ret.pop_back();
		BigNum big(0);
		big.data = ret;
		return big;
	}
	//do plus here
	vector<uint8_t> ret(data);
	int carry = 0;
	for (int i = 0; i < data.size(); i++) {
		if (i < operand.data.size())
			//if digit exists in b
			carry += operand.data[i];
		int tmp = (int) ret[i] + carry;
		carry = tmp >> 8;
		ret[i] = tmp bitand ((1 << 8) - 1);
	}
	while (carry > 0) {
		ret.push_back(carry & ((1 << 8) - 1));
		carry >>= 8;
	}
	while (not ret.empty() and *ret.rbegin() == 0)
		ret.pop_back();
	BigNum r(0);
	r.data = ret;
	return r;
}

BigNum BigNum::operator-() const {
	BigNum ret(0);
	ret.data = data;
	ret.negative = not negative;
	return ret;
}

BigNum BigNum::operator %(const BigNum& operand) const {
	return operator-(operator/(operand) * operand);
}

BigNum BigNum::operator /(const BigNum& operand) const {
	std::vector<uint8_t> quotient, current;
	bool started = false;
	for (ssize_t i = data.size() - 1; i >= 0; i--) {
		current.push_back(data[i]);
		BigNum bcurrent(current);
		uint8_t q = bcurrent.smallDivide(operand);
		current = (bcurrent - ((operand) * BigNum(q))).toVector();
		if (started or q != 0) {
			started = true;
			quotient.push_back(q);
		}
	}
	return BigNum(quotient, negative xor operand.negative);
}

bool BigNum::operator <(const BigNum& operand) const {
	if (negative xor operand.negative) {
		return negative;
	}
	if (data.size() != operand.data.size())
		return data.size() < operand.data.size();
	for (ssize_t i = data.size() - 1; i >= 0; i--)
		if (data[i] != operand.data[i])
			return data[i] < operand.data[i];
	return false;
}

bool BigNum::isNegative() const {
	return negative;
}

BigNum BigNum::abs() const {
	BigNum ret(0);
	ret.data = data;
	ret.negative = false;
	return ret;
}

bool BigNum::operator ==(const BigNum& operand) const {
	return negative == operand.negative and data == operand.data;
}

uint8_t BigNum::smallDivide(BigNum const& devider) {
	int16_t low = 0;
	int16_t high = (1 << 8) - 1;
	while (low <= high) {
		uint8_t mid = (low + high) >> 1;
		if (operator<(devider * BigNum(mid)))
			//low = high + 1
			//divider * high <= dividend < divider * (high + 1)
			high = (int16_t) mid - 1;
		else
			low = (int16_t) mid + 1;
	}
	return (uint8_t) high;
}
