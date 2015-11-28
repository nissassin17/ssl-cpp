/*
 * Asn1CertificateSerialNumber.h
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#ifndef ASN1CERTIFICATESERIALNUMBER_H_
#define ASN1CERTIFICATESERIALNUMBER_H_
#include "ASN1.hpp"
namespace asn1 {
class Asn1CertificateSerialNumber {
public:
	Asn1CertificateSerialNumber(ASN1 const& asn1);
	long long getNumber() const;

private:
	long long number;
};
}

#endif /* ASN1CERTIFICATESERIALNUMBER_H_ */
