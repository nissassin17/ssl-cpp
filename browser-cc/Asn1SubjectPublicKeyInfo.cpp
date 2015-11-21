/*
 * Asn1SubjectPublicKeyInfo.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#include "Asn1SubjectPublicKeyInfo.h"
#include "Util.hpp"

namespace asn1 {

Asn1SubjectPublicKeyInfo::Asn1SubjectPublicKeyInfo(ASN1 const& asn1) {
	ASN1::SequenceType const& seq = asn1.getSequenceVal();
	algorithm = new Asn1AlgorithmIdentifier(*(seq[0]));
	//TODO:define type of subject public key info based on algorithm
	//here we just use rsa format
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

int Asn1SubjectPublicKeyInfo::getExponent() const {
	return static_cast<int>(Util::vectorToInt(ASN1(subjectPublicKey).getSequenceVal()[1]->getIntVal()));
}


vector<uint8_t> Asn1SubjectPublicKeyInfo::getModulus() const {
    return ASN1(subjectPublicKey).getSequenceVal()[0]->getIntVal();
}

} /* namespace asn1 */
