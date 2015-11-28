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
	notBefore.reset( new Asn1Time(*(seq[0])));
	notAfter.reset(new Asn1Time(*(seq[1])));
}

const shared_ptr<Asn1Time>& Asn1Validity::getNotAfter() const {
	return notAfter;
}

const shared_ptr<Asn1Time>& Asn1Validity::getNotBefore() const {
	return notBefore;
}

} /* namespace asn1 */
