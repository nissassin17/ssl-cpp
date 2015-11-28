//
//  asn-1cert.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include "Asn1Cert.hpp"

#include "Util.hpp"
#include "ASN1.hpp"
#include "Log.h"
namespace rsa {

Asn1Cert::Asn1Cert(const vector<uint8_t> &data, size_t offset) {

	uint32_t length = Util::takeData24(data, offset);
	offset += 3;

	this->data = Util::takeData(data, length, offset);

//    Log::file("/Users/nissassin17/Desktop/tmp.cert") <<  this->data << Log::eof;

	ASN1 asn1 = ASN1(this->data, 0);
	//global sequence of 3 values
	vector<shared_ptr<ASN1> > sequence = asn1.getSequenceVal();
	tbsCertificate.reset(new Asn1TBSCertificate(*(sequence[0])));
	signatureAlgorithm.reset(new Asn1AlgorithmIdentifier(*(sequence[1])));
	signatureValue = ASN1::BitStringType(sequence[2]->getBitStringVal());

	rsaPublicKey.reset(
			new RSAPublicKey(
					tbsCertificate->getSubjectPublicKeyInfo()->getModulus(),
					tbsCertificate->getSubjectPublicKeyInfo()->getExponent()));
}

vector<uint8_t> Asn1Cert::toData() const {
	vector<uint8_t> data;
	Util::addData24(data, (uint32_t) this->data.size());
	Util::addData(data, this->data);
	return data;
}

size_t Asn1Cert::size() const {
	return 3 + this->data.size();
}

const shared_ptr<RSAPublicKey>& Asn1Cert::getRsaPublicKey() const {
	return rsaPublicKey;
}

}
