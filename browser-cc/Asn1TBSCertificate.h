/*
 * Asn1TBSCertificate.h
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#ifndef ASN1TBSCERTIFICATE_H_
#define ASN1TBSCERTIFICATE_H_

#include "ASN1.hpp"
#include "Asn1AlgorithmIdentifier.h"
#include "Asn1Name.h"
#include "Asn1Validity.h"
#include "Asn1SubjectPublicKeyInfo.h"
#include "Asn1CertificateSerialNumber.h"

namespace asn1 {

class Asn1TBSCertificate {
public:
	Asn1TBSCertificate(ASN1 const& asn1);
	~Asn1TBSCertificate();
	int getVersion() const;
	Asn1Name* getIssuer() const;
	Asn1CertificateSerialNumber* getSerialNumber() const;
Asn1AlgorithmIdentifier* getSignature() const;
Asn1Name* getSubject() const;
Asn1SubjectPublicKeyInfo* getSubjectPublicKeyInfo() const;
Asn1Validity* getValidity() const;

private:
	int version;
	const Asn1CertificateSerialNumber *serialNumber;
	const Asn1AlgorithmIdentifier *signature;
	const Asn1Name *issuer;
	const Asn1Validity *validity;
	const Asn1Name *subject;
	const Asn1SubjectPublicKeyInfo *subjectPublicKeyInfo;
};

} /* namespace asn1 */

#endif /* ASN1TBSCERTIFICATE_H_ */
