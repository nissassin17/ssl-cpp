//
//  digitally-signed.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include "DigitallySigned.hpp"
#include "ServerDHParams.hpp"
#include "Util.hpp"

DigitallySigned::DigitallySigned(const vector<uint8_t> &data, size_t offset) {

	vector<uint8_t> tmp;
	tmp = Util::takeData(data, 32, offset);
	offset += 32;

	for (int i = 0; i < 32; i++)
		this->clientRandom[i] = tmp[i];

	tmp = Util::takeData(data, 32, offset);
	offset += 32;
	for (int i = 0; i < 32; i++)
		this->serverRandom[i] = tmp[i];

	this->params.reset(new ServerDHParams(data, offset));
	offset += this->params->size();
}

size_t DigitallySigned::size() const {
	return 32 + 32 + this->params->size();
}
