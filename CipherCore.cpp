/*
 * CipherCore.cpp
 *
 *  Created on: Oct 15, 2015
 *      Author: nissassin17
 */

#include "CipherCore.hpp"
#include "RSAPublicKey.h"
#include "BigNum.h"
#include "Log.h"

std::vector<uint8_t> CipherCore::rsaep(const rsa::RSAPublicKey& publicKey,
		const std::vector<uint8_t>& message) {

	Log::info << "Rsa exponent: " << publicKey.getExponent() << endl;
	Log::info << "Rsa public key (first 16 bytes): "
			<< vector<uint8_t>(publicKey.getModulus().begin(),
					publicKey.getModulus().begin() + 16) << endl;
	Log::info << "Plain random message: " << message << endl;
	vector<uint8_t> encrypted(
			BigNum(message).exponent(publicKey.getExponent(),
					publicKey.getModulus()).toVector());
	Log::info << "Encrypted random message (first 32 bytes): "
			<< vector<uint8_t>(encrypted.begin(), encrypted.begin() + 32)
			<< endl;
	return encrypted;
}
