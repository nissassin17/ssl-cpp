/*
 * Asn1AlgorithmIdentifier.h
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#ifndef ASN1ALGORITHMIDENTIFIER_H_
#define ASN1ALGORITHMIDENTIFIER_H_
#include "ASN1.hpp"
#include <vector>
using namespace std;

namespace asn1 {

class Asn1AlgorithmIdentifier {
public:
	Asn1AlgorithmIdentifier(ASN1 const& asn1);
private:
	vector<long long> algorithm;
	ASN1 *parameters;

};

} /* namespace asn1 */

#endif /* ASN1ALGORITHMIDENTIFIER_H_ */
