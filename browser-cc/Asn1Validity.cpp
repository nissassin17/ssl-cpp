/*
 * Asn1Validity.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#include "Asn1Validity.h"

namespace asn1 {

Asn1Validity::Asn1Validity(ASN1 const& asn1) {
	ASN1::SequenceType const& seq = asn1.getSequenceVal();
	notBefore = new Asn1Time(*(seq[0]));
	notAfter = new Asn1Time(*(seq[1]));
}

} /* namespace asn1 */

asn1::Asn1Validity::~Asn1Validity() {
	delete notAfter;
	delete notBefore;
}

asn1::Asn1Time* asn1::Asn1Validity::getNotAfter() const {
	return notAfter;
}

asn1::Asn1Time* asn1::Asn1Validity::getNotBefore() const {
	return notBefore;
}
