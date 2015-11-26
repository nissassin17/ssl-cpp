/*
 * CipherCore.hpp
 *
 *  Created on: Oct 15, 2015
 *      Author: nissassin17
 */

#ifndef CIPHERCORE_HPP_
#define CIPHERCORE_HPP_

#include <vector>
#include "RSAPublicKey.h"
using namespace std;

class CipherCore {
public:
	//RSA
	static std::vector<uint8_t> rsaep(const rsa::RSAPublicKey &publicKey, const std::vector<uint8_t> &message);
};

#endif /* CIPHERCORE_HPP_ */
