/*
 * Asn1SubjectPublicKeyInfo.h
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#ifndef ASN1SUBJECTPUBLICKEYINFO_H_
#define ASN1SUBJECTPUBLICKEYINFO_H_

#include "ASN1.hpp"
#include "Asn1AlgorithmIdentifier.h"

namespace asn1 {

class Asn1SubjectPublicKeyInfo {
public:
	Asn1SubjectPublicKeyInfo(ASN1 const& asn1);
	~Asn1SubjectPublicKeyInfo();
	const Asn1AlgorithmIdentifier* getAlgorithm() const;
	const ASN1::BitStringType& getSubjectPublicKey() const;
	vector<int8_t> getExponent() const;
	int getModulus() const;

private:
	Asn1AlgorithmIdentifier *algorithm;
	ASN1::BitStringType subjectPublicKey;
};

} /* namespace asn1 */

#endif /* ASN1SUBJECTPUBLICKEYINFO_H_ */
