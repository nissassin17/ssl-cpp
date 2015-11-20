/*
 * CipherCore.cpp
 *
 *  Created on: Oct 15, 2015
 *      Author: nissassin17
 */

#include "CipherCore.hpp"
#include "RSAPublicKey.h"

std::vector<uint8_t> CipherCore::rsaep(const rsa::RSAPublicKey& publicKey,
		const std::vector<uint8_t>& message) {
	return CipherCore::exponent(message, publicKey.getExponent(),
			publicKey.getModulus());
}

std::vector<uint8_t> CipherCore::exponent(const std::vector<uint8_t>& base,
		long long exponent, const std::vector<uint8_t>& modulus) {
	if (exponent == 0) {
		std::vector<uint8_t> result;
		result.push_back(1);
		return result;
	}
	std::vector<uint8_t> result(
			CipherCore::exponent(base, exponent >> 1, modulus));

	//square result here
	result = CipherCore::multiple(result, result, modulus);

	if (exponent bitand 1) //odd
		result = CipherCore::multiple(result, base, modulus);

	return result;
}

std::vector<uint8_t> CipherCore::multiple(const std::vector<uint8_t>& left,
		const std::vector<uint8_t>& right,
		const std::vector<uint8_t>& modulus) {


	return CipherCore::divide(CipherCore::bigMultiple(left, right), modulus);
}

std::vector<uint8_t> CipherCore::divide(const std::vector<uint8_t>& dividend,
		const std::vector<uint8_t>& divider) {
	std::vector<uint8_t> quotient, current;
	bool started = false;
	for (int i = 0; i < dividend.size(); i++) {
		current.push_back(dividend[i]);
		uint8_t q = CipherCore::smallDivide(current, divider);
		if (started or q != 0){
			started = true;
			quotient.push_back(q);
		}
	}
	return CipherCore::subtract(dividend, CipherCore::bigMultiple(quotient, divider));
}

uint8_t CipherCore::smallDivide(std::vector<uint8_t>& dividend,
		const std::vector<uint8_t> divider) {
	uint8_t low = 0;
	uint8_t high = (1 << 8) - 1;
	while (low < high) {
		uint8_t mid = (low + high) >> 1;
		std::vector<uint8_t> smallProduct = CipherCore::smallMultiple(divider,
				mid);
		//low = high + 1
		//divider * high <= dividend < divider * (high + 1)
		if (CipherCore::isSmaller(dividend, smallProduct))
			high = mid - 1;
		else
			low = mid + 1;
	}
	dividend = CipherCore::subtract(dividend, CipherCore::smallMultiple(divider, high));
	return high;
}

bool CipherCore::isSmaller(std::vector<uint8_t>& a, std::vector<uint8_t>& b) {
	if (a.size() != b.size())
		return a.size() < b.size();
	return a < b;
}

vector<uint8_t> CipherCore::smallMultiple(const vector<uint8_t>& x,
		uint8_t times) {
	uint8_t carry(0);
	vector<uint8_t> ret(x.size(), 0);
	for (ssize_t i = x.size() - 1; i >= 0; i--) {
		uint16_t tmp = static_cast<uint16_t>(x[i]) * times + carry;
		carry = tmp >> 8;
		ret[i] = tmp bitand ((1 << 8) - 1);
	}
	if (carry != 0)
		ret.insert(ret.begin(), carry);
	return ret;
}

vector<uint8_t> CipherCore::subtract(const vector<uint8_t>& a,
		const vector<uint8_t>& b) {
	vector<uint8_t> ret(a);
	int carry = 0;
	for(int i = 0; i < a.size(); i++){
		if (i < b.size())
			carry += b[b.size() - 1 - i];
		int tmp = (int)ret[ret.size() - 1 - i] - carry;
		if (tmp < 0){
			carry = 1;
			ret[ret.size() - 1 - i] = tmp + (1 << 8);
		}else{
			ret[ret.size() - 1 - i] = tmp;
			carry = 0;
		}
	}
	while (!ret.empty() and ret[0] == 0)
		ret.erase(ret.begin());
	return ret;
}

vector<uint8_t> CipherCore::bigMultiple(const vector<uint8_t>& left,
		const vector<uint8_t>& right) {
	std::vector<uint32_t> ret(left.size() + right.size() - 1, 0);
		for (int i = 0; i < left.size(); i++)
			for (int j = 0; j < right.size(); j++)
				ret[i + j] += (uint16_t) left[i] * right[j];
		uint32_t carry(0);
		for (std::vector<uint32_t>::iterator it = ret.begin(); it != ret.end();
				it++) {
			*it += carry;
			carry = *it >> 8;
			*it &= (1 << 8) - 1;
		}
		while (carry > 0) {
			ret.push_back(carry & ((1 << 8) - 1));
			carry >>= 8;
		}
		while (not ret.empty() and *ret.rbegin() == 0)
			ret.pop_back();
    
    vector<uint8_t> r8;
    for(int i = 0; i < ret.size(); i++)
        r8.push_back(static_cast<uint8_t>(ret[i]));
    return r8;
}
