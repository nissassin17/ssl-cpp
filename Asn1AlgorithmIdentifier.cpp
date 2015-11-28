/*
 * Asn1AlgorithmIdentifier.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#include "Asn1AlgorithmIdentifier.h"

namespace asn1 {

Asn1AlgorithmIdentifier::Asn1AlgorithmIdentifier(ASN1 const& asn1) {
	algorithm = asn1.getSequenceVal()[0]->getObjectIdentifierVal();
	parameters = asn1.getSequenceVal()[1];
}

} /* namespace asn1 */
