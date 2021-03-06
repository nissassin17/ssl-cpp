//
//  ServerHello.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/4/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include "ServerHello.hpp"

#include "CipherSuite.hpp"
#include "CompressionMethod.hpp"
#include "ProtocolVersion.hpp"
#include "Random.hpp"
#include "SessionID.hpp"
#include "Util.hpp"

ServerHello::ServerHello(const vector<uint8_t> &data, size_t offset) {
	this->protocolVersion.reset(new ProtocolVersion(data, offset));
	offset += this->protocolVersion->size();

	this->random.reset(new Random(data, offset));
	offset += this->random->size();

	this->sessionID.reset(new SessionID(data, offset));
	offset += this->sessionID->size();

	this->cipherSuite.reset(new CipherSuite(data, offset));
	offset += this->cipherSuite->size();

	this->compressionMethod.reset(new CompressionMethod(data, offset));
	offset += this->compressionMethod->size();

	if (offset != data.size()) {
		this->haveExtension = true;
		uint16_t nExtensions = Util::takeData16(data, offset);
		offset += 2;

		while (nExtensions--) {
			this->extensions.push_back(
					shared_ptr<Extension>(new Extension(data, offset)));
			offset += this->extensions[this->extensions.size() - 1]->size();
		}
	} else {
		this->haveExtension = false;
	}
}

size_t ServerHello::size() const {
	size_t result(0);
	result = protocolVersion->size() + random->size() + sessionID->size()
			+ cipherSuite->size() + compressionMethod->size();
	if (haveExtension) {
		result += 2;
		for (int i = 0; i < extensions.size(); i++)
			result += extensions[i]->size();
	}
	return result;
}

const shared_ptr<CipherSuite>& ServerHello::getCipherSuite() const {
	return cipherSuite;
}
