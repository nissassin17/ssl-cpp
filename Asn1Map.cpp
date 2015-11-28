/*
 * Asn1SetClass.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#include "Asn1Map.h"

namespace asn1 {

Asn1Map::Asn1Map(ASN1 const& asn1) {
	ASN1::SetType seq(asn1.getSetVal());
	for (ASN1::SetType::const_iterator it = seq.begin(); it != seq.end();
			it++) {
		ASN1::SequenceType seq((*it)->getSequenceVal());
		if (seq.size() >= 2) {
			data[seq[0]->getObjectIdentifierVal()] = seq[1];
		}
	}

}

const map<ASN1::ObjectIdentifierType, shared_ptr<ASN1> >& Asn1Map::getData() const {
	return data;
}

} /* namespace asn1 */
