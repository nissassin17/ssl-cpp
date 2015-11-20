/*
 * RSAPublicKey.cpp
 *
 *  Created on: Oct 15, 2015
 *      Author: nissassin17
 */

#include "RSAPublicKey.h"

namespace rsa {

PublicKey::PublicKey(const std::vector<uint8_t> &modulus, int exponent) :
	modulus(modulus), exponent(exponent){

}

} /* namespace rsa */

int rsa::PublicKey::getExponent() const {
	return exponent;
}

const std::vector<uint8_t>& rsa::PublicKey::getModulus() const {
	return modulus;
}
