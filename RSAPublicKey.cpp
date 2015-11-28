/*
 * RSAPublicKey.cpp
 *
 *  Created on: Oct 15, 2015
 *      Author: nissassin17
 */

#include "RSAPublicKey.h"

namespace rsa {

RSAPublicKey::RSAPublicKey(const std::vector<uint8_t> &modulus, int exponent) :
		modulus(modulus), exponent(exponent) {

}

} /* namespace rsa */

int rsa::RSAPublicKey::getExponent() const {
	return exponent;
}

const std::vector<uint8_t>& rsa::RSAPublicKey::getModulus() const {
	return modulus;
}
