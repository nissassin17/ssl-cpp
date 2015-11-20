/*
 * Asn1SubjectPublicKeyInfo.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#include "Asn1SubjectPublicKeyInfo.h"

namespace asn1 {

Asn1SubjectPublicKeyInfo::Asn1SubjectPublicKeyInfo(ASN1 const& asn1) {
	ASN1::SequenceType const& seq = asn1.getSequenceVal();
	algorithm = new Asn1AlgorithmIdentifier(*(seq[0]));
	subjectPublicKey = ASN1::BitStringType(seq[1]->getBitStringVal());
}

const Asn1AlgorithmIdentifier* Asn1SubjectPublicKeyInfo::getAlgorithm() const {
	return algorithm;
}

Asn1SubjectPublicKeyInfo::~Asn1SubjectPublicKeyInfo() {
	delete algorithm;
}

const ASN1::BitStringType& Asn1SubjectPublicKeyInfo::getSubjectPublicKey() const {
	return subjectPublicKey;
}

} /* namespace asn1 */
