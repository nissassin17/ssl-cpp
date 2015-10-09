//
//  asn-1cert.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "ASN1cert.hpp"

#include "Util.hpp"

ASN1Cert::ASN1Cert(const vector<uint8_t> &data, size_t offset) {
	uint32_t length = Util::takeData24(data, offset);
	offset += 3;

	this->data = Util::takeData(data, length, offset);

	//NOTE: debug
	//Util::writeToFile("/Users/nissassin17/Desktop/tmp.cert", this->data);
}

vector<uint8_t> ASN1Cert::toData()  const{
	vector<uint8_t> data;
	Util::addData24(data, (uint32_t) this->data.size());
	Util::addData(data, this->data);
	return data;
}

size_t ASN1Cert::size() const{
	return 3 + this->data.size();
}
