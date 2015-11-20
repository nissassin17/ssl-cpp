/*
 * Asn1SetClass.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#include "Asn1Set.h"

namespace asn1 {

Asn1Set::Asn1Set(ASN1 const& asn1) {
	const ASN1::SetType &seq = asn1.getSequenceVal();
	//**TODO**: hard copy asn1 value here instead of taking reference because the original asn1 object will be freed after being parsed to this constructor
	for(ASN1::SequenceType::const_iterator it = seq.begin(); it != seq.last.end(); it++)
		values[it->getSequenceVal()[0]->getObjectIdenfifierVal()] = values[it->getSequenceVal()[1]];

}

} /* namespace asn1 */
