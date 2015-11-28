//
//  certificate.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include "Certificate.hpp"
#include "Util.hpp"

Certificate::Certificate(const vector<uint8_t> &data, size_t offset) {
	uint32_t length = Util::takeData24(data, offset);
	offset += 3;

	while (length > 0) {
		this->certificateList.push_back(
				shared_ptr<rsa::Asn1Cert>(new rsa::Asn1Cert(data, offset)));
		size_t t = (*certificateList.rbegin())->size();
		length -= t;
		offset += t;
	}
}

size_t Certificate::size() const {
	size_t result(3);
	for (int i = 0; i < this->certificateList.size(); i++)
		result += this->certificateList[i]->size();
	return result;
}

const vector<shared_ptr<rsa::Asn1Cert> >& Certificate::getCertificateList() const {
	return certificateList;
}
