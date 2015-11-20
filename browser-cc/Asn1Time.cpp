/*
 * Asn1Time.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#include "Asn1Time.h"

namespace asn1 {

Asn1Time::Asn1Time(ASN1 const& asn1) {
	time = ASN1::TimeType(asn1.getOctetStringVal());
}

} /* namespace asn1 */
