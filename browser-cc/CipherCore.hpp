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
	static std::vector<uint8_t> rsaep(const rsa::PublicKey &publicKey, const std::vector<uint8_t> &message);

private:
	//exponent
	static std::vector<uint8_t> exponent(const std::vector<uint8_t> &base, long long exponent, const std::vector<uint8_t> &modulus);

	static std::vector<uint8_t> multiple(const std::vector<uint8_t> &left, const std::vector<uint8_t> &right, const std::vector<uint8_t> &modulus);

	static std::vector<uint8_t> divide(const std::vector<uint8_t> &dividend, const std::vector<uint8_t> &divider);

	static uint8_t smallDivide(std::vector<uint8_t> &devidend, const std::vector<uint8_t> divider);

	static bool isSmaller(std::vector<uint8_t> &a, std::vector<uint8_t> &b);

	static vector<uint8_t> smallMultiple(const vector<uint8_t> &x, uint8_t times);

	static vector<uint8_t> subtract(const vector<uint8_t> &a, const vector<uint8_t> &b);

	static vector<uint8_t> bigMultiple(const vector<uint8_t> &a, const vector<uint8_t> &b);
};

#endif /* CIPHERCORE_HPP_ */
