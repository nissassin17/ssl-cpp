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
	serialNumber.reset(new Asn1CertificateSerialNumber(*(seq[1])));
	signature.reset(new Asn1AlgorithmIdentifier(*(seq[2])));
	issuer.reset(new Asn1Name(*(seq[3])));
	validity.reset(new Asn1Validity(*(seq[4])));
	subject.reset(new Asn1Name(*(seq[5])));
	subjectPublicKeyInfo.reset( new Asn1SubjectPublicKeyInfo(*(seq[6])));

}

const shared_ptr<const Asn1Name>& Asn1TBSCertificate::getIssuer() const {
	return issuer;
}

const shared_ptr<const Asn1CertificateSerialNumber>& Asn1TBSCertificate::getSerialNumber() const {
	return serialNumber;
}

const shared_ptr<const Asn1AlgorithmIdentifier>& Asn1TBSCertificate::getSignature() const {
	return signature;
}

const shared_ptr<const Asn1Name>& Asn1TBSCertificate::getSubject() const {
	return subject;
}

const shared_ptr<const Asn1SubjectPublicKeyInfo>& Asn1TBSCertificate::getSubjectPublicKeyInfo() const {
	return subjectPublicKeyInfo;
}

const shared_ptr<const Asn1Validity>& Asn1TBSCertificate::getValidity() const {
	return validity;
}

int Asn1TBSCertificate::getVersion() const {
	return version;
}

vector<string> Asn1TBSCertificate::getIssuerList() const {
	vector<shared_ptr<Asn1RelativeDistinguishedName> > seq = issuer->getRdnSequence();
	vector<string> ret;
	for(vector<shared_ptr<Asn1RelativeDistinguishedName> >::const_iterator it = seq.begin(); it != seq.end(); it++){
 
		for(set<ASN1::ObjectIdentifierType, shared_ptr<ASN1> >::const_iterator pair = (*it)->getData().begin(); pair != (*it)->getData().end(); pair++){
			string identifierName = "";
			for(ASN1::ObjectIdentifierType::const_iterator t = pair->first.begin(); t != pair->first.end(); t++)
                identifierName += to_string(*t);
			//TODO: get string value here from PrintableString
			//pair->second->getStringValue();
		}
	}
	return ret;
}

} /* namespace asn1 */
