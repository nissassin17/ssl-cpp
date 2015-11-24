//
//  server-key-exchange.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include "ServerKeyExchange.hpp"

#include "CipherSuite.hpp"
#include "DigitallySigned.hpp"
#include "ServerDHParams.hpp"

ServerKeyExchange::ServerKeyExchange(shared_ptr<const CipherSuite> cipherSuite,
		const vector<uint8_t> &data, size_t offset) :
		cipherSuite(cipherSuite) {
	switch (cipherSuite->getKeyExchange()) {
	case CipherSuite::DH_anon:
		this->params.reset(new ServerDHParams(data, offset));
		offset += this->params->size();
		break;

	case CipherSuite::DHE_RSA:
	case CipherSuite::DHE_DSS:
		this->params.reset(new ServerDHParams(data, offset));
		this->signedParams.reset(new DigitallySigned(data, offset));
		offset += this->params->size();
		break;

	case CipherSuite::RSA:
	case CipherSuite::DH_RSA:
	case CipherSuite::DH_DSS:
		break;
	default: //case NONE:
		break;
	}
}

size_t ServerKeyExchange::size() const{
	size_t result(0);
	return result;
}

