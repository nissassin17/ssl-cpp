//
//  certificate.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "certificate.hpp"

#include "util.hpp"

Certificate::Certificate(vector<uint8_t> &data, size_t offset) {
	uint32_t length = Util::takeData24(data, offset);
	offset += 3;

	while (length > 0) {
		this->certificateList.push_back(new ASN1Cert(data, offset));
		size_t t =
				this->certificateList[this->certificateList.size() - 1]->size();
		length -= t;
		offset += t;
	}
}

vector<ASN1Cert*> Certificate::getCertificateList() {
	return certificateList;
}

size_t Certificate::size() {
	size_t result(3);
	for (int i = 0; i < this->certificateList.size(); i++)
		result += this->certificateList[i]->size();
	return result;
}

Certificate::~Certificate() {
	for (int i = 0; i < certificateList.size(); i++)
		delete certificateList[i];
}
