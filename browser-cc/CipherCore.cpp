/*
 * CipherCore.cpp
 *
 *  Created on: Oct 15, 2015
 *      Author: nissassin17
 */

#include "CipherCore.hpp"
#include "RSAPublicKey.h"

std::vector<uint8_t> CipherCore::rsaep(const rsa::PublicKey& publicKey,
		const std::vector<uint8_t>& message) {
	return CipherCore::exponent(message, publicKey.getExponent(), publicKey.getModulus());
}

std::vector<uint8_t> CipherCore::exponent(const std::vector<uint8_t>& base,
		long long exponent, const std::vector<uint8_t>& modulus) {
	if (exponent == 0){
		std::vector<uint8_t> result;
		result.push_back(1);
		return result;
	}
	std::vector<uint8_t> result(CipherCore::exponent(base, exponent >> 1, modulus));

	//square result here
	result = CipherCore::multiple(result, result, modulus);

	if (exponent bitand 1)//odd
		result = CipherCore::multiple(result, base, modulus);

	return result;
}

std::vector<uint8_t> CipherCore::multiple(const std::vector<uint8_t>& left,
		const std::vector<uint8_t>& right,
		const std::vector<uint8_t>& modulus) {
	std::vector<uint32_t> ret(left.size() + right.size() - 1, 0);
	for(int i = 0; i < left.size(); i++)
		for(int j = 0; j < right.size(); j++)
			ret[i + j] += (uint16_t)left[i] * right[j];
	uint32_t carry(0);
	for(std::vector<uint32_t>::iterator it = ret.begin(); it != ret.end(); it++){
		*it += carry;
		carry = *it >> 8;
		*it &= (1 << 8)-1;
	}
	while (carry > 0){
		ret.push_back(carry & ((1 << 8) - 1));
		carry >>= 8;
	}
	while(not ret.empty() and *ret.rbegin() == 0)
		ret.pop_back();

	return CipherCore::divide(ret, modulus);
}
