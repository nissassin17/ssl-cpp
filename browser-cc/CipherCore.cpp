/*
 * CipherCore.cpp
 *
 *  Created on: Oct 15, 2015
 *      Author: nissassin17
 */

#include "CipherCore.hpp"
#include "RSAPublicKey.h"
#include "BigNum.h"

std::vector<uint8_t> CipherCore::rsaep(const rsa::RSAPublicKey& publicKey,
		const std::vector<uint8_t>& message) {
	return BigNum(message).exponent(publicKey.getExponent(), publicKey.getModulus()).toVector();
}
