/*
 * RSAPublicKey.h
 *
 *  Created on: Oct 15, 2015
 *      Author: nissassin17
 */

#ifndef RSAPUBLICKEY_H_
#define RSAPUBLICKEY_H_

#include <vector>
using namespace std;
namespace rsa {

class PublicKey {
public:
	PublicKey(const std::vector<uint8_t> &modulus, int exponent);
	int getExponent() const;
	const std::vector<uint8_t>& getModulus() const;

private:
	std::vector<uint8_t> modulus;
	int exponent;
};

} /* namespace rsa */

#endif /* RSAPUBLICKEY_H_ */
