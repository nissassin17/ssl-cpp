/*
 * Asn1TBSCertificate.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#include "Asn1TBSCertificate.h"
#include "Util.hpp"

namespace asn1 {

Asn1TBSCertificate::Asn1TBSCertificate(ASN1 const& asn1) {
	ASN1::SequenceType const& seq = asn1.getSequenceVal();
    version = static_cast<int>(Util::vectorToInt(seq[0]->getIntVal()));
	serialNumber = new Asn1CertificateSerialNumber(*(seq[1]));
	signature = new Asn1AlgorithmIdentifier(*(seq[2]));
	issuer = new Asn1Name(*(seq[3]));
	validity = new Asn1Validity(*(seq[4]));
	subject = new Asn1Name(*(seq[5]));
	subjectPublicKeyInfo = new Asn1SubjectPublicKeyInfo(*(seq[6]));

}

Asn1TBSCertificate::~Asn1TBSCertificate() {
	delete serialNumber;
	delete signature;
	delete issuer;
	delete validity;
	delete subject;
	delete subjectPublicKeyInfo;

}


 int Asn1TBSCertificate::getVersion() const {
	return version;
}

const Asn1Name* Asn1TBSCertificate::getIssuer() const {
	return issuer;
}

const Asn1CertificateSerialNumber* Asn1TBSCertificate::getSerialNumber() const {
	return serialNumber;
}

const Asn1AlgorithmIdentifier* Asn1TBSCertificate::getSignature() const {
	return signature;
}

const Asn1Name* Asn1TBSCertificate::getSubject() const {
	return subject;
}

const Asn1SubjectPublicKeyInfo* Asn1TBSCertificate::getSubjectPublicKeyInfo() const {
	return subjectPublicKeyInfo;
}

const Asn1Validity* Asn1TBSCertificate::getValidity() const {
	return validity;
}

} /* namespace asn1 */
