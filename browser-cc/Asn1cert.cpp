//
//  asn-1cert.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "Asn1Cert.hpp"

#include "Util.hpp"
#include "ASN1.hpp"

Asn1Cert::Asn1Cert(const vector<uint8_t> &data, size_t offset){
	uint32_t length = Util::takeData24(data, offset);
	offset += 3;

	this->data = Util::takeData(data, length, offset);
    ASN1 asn1 = ASN1(this->data, 0);
    //global sequence of 3 values
    vector<ASN1*> sequence = asn1.getSequenceVal();
    tbsCertificate = new Asn1TBSCertificate(*(sequence[0]));
    signatureAlgorithm = new Asn1AlgorithmIdentifier(*(sequence[1]));
    signatureValue = ASN1::BitStringType(sequence[2]->getBitStringVal());

	//NOTE: debug
    //NOTE TODO: get modulus from asn1 and assign to this->modulus
//	Util::writeToFile("/Users/nissassin17/Desktop/tmp.cert", this->data);
}

vector<uint8_t> Asn1Cert::toData()  const{
	vector<uint8_t> data;
	Util::addData24(data, (uint32_t) this->data.size());
	Util::addData(data, this->data);
	return data;
}

size_t Asn1Cert::size() const{
	return 3 + this->data.size();
}

int Asn1Cert::getExponent() const {
    return 0;
}

const vector<uint8_t>& Asn1Cert::getRSAModulus() const {
    vector<uint8_t> x;
    return x;
}

Asn1Cert::~Asn1Cert() {
	delete tbsCertificate;
	delete signatureAlgorithm;
}
