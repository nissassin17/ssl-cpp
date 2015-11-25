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
	const shared_ptr<const Asn1Name>& getIssuer() const;
	const shared_ptr<const Asn1CertificateSerialNumber>& getSerialNumber() const;
	const shared_ptr<const Asn1AlgorithmIdentifier>& getSignature() const;
	const shared_ptr<const Asn1Name>& getSubject() const;
	const shared_ptr<const Asn1SubjectPublicKeyInfo>& getSubjectPublicKeyInfo() const;
	const shared_ptr<const Asn1Validity>& getValidity() const;
	int getVersion() const;

private:
	int version;
	shared_ptr<const Asn1CertificateSerialNumber> serialNumber;
	shared_ptr<const Asn1AlgorithmIdentifier> signature;
	shared_ptr<const Asn1Name> issuer;
	shared_ptr<const Asn1Validity> validity;
	shared_ptr<const Asn1Name> subject;
	shared_ptr<const Asn1SubjectPublicKeyInfo> subjectPublicKeyInfo;
};

} /* namespace asn1 */

#endif /* ASN1TBSCERTIFICATE_H_ */
