/*
 * Asn1CertificateSerialNumber.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#include "Asn1CertificateSerialNumber.h"
#include "Util.hpp"
namespace asn1{
Asn1CertificateSerialNumber::Asn1CertificateSerialNumber(ASN1 const& asn1) {
    number = Util::vectorToInt(asn1.getIntVal());

}

long long Asn1CertificateSerialNumber::getNumber() const {
	return number;
}
}
