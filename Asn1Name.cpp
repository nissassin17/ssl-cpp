/*
 * Asn1Name.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#include "Asn1Name.h"

asn1::Asn1Name::Asn1Name(ASN1 const& asn1) {
	const ASN1::SequenceType seq = asn1.getSequenceVal();
	for (int i = 0; i < seq.size(); i++) {
		rdnSequence.push_back(
				shared_ptr<Asn1RelativeDistinguishedName>(
						new Asn1RelativeDistinguishedName(*(seq[i]))));
	}
}

const vector<shared_ptr<asn1::Asn1RelativeDistinguishedName> > & asn1::Asn1Name::getRdnSequence() const {
	return rdnSequence;
}
