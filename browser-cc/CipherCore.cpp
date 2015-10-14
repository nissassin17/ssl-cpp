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

	return left;
}
