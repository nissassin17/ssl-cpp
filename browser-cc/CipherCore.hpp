/*
 * CipherCore.hpp
 *
 *  Created on: Oct 15, 2015
 *      Author: nissassin17
 */

#ifndef CIPHERCORE_HPP_
#define CIPHERCORE_HPP_

class CipherCore {
public:
	//RSA
	static std::vector<uint8_t> rsaep(const rsa::PublicKey &publicKey, const std::vector<uint8_t> &message);

private:
	//exponent
	static std::vector<uint8_t> exponent(const std::vector<uint8_t> &base, long long exponent, const std::vector<uint8_t> &modulus);

	static std::vector<uint8_t> multiple(const std::vector<uint8_t> &left, const std::vector<uint8_t> &right, const std::vector<uint8_t> &modulus);

	static std::vector<uint8_t> divide(const std::vector<uint8_t> &dividend, const std::vector<uint8_t> &divider);
};

#endif /* CIPHERCORE_HPP_ */
