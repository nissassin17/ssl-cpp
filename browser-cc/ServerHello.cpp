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
#include "ProcotolVersion.hpp"
#include "Random.hpp"
#include "SessionID.hpp"
#include "Util.hpp"

const CipherSuite *ServerHello::getCipherSuite() const{
	return this->cipherSuite;
}

ServerHello::ServerHello(const vector<uint8_t> &data, size_t offset) {
	this->protocolVersion = new ProtocolVersion(data, offset);
	offset += this->protocolVersion->size();

	this->random = new Random(data, offset);
	offset += this->random->size();

	this->sessionID = new SessionID(data, offset);
	offset += this->sessionID->size();

	this->cipherSuite = new CipherSuite(data, offset);
	offset += this->cipherSuite->size();

	this->compressionMethod = new CompressionMethod(data, offset);
	offset += this->compressionMethod->size();

	if (offset != data.size()) {
		this->haveExtension = true;
		uint16_t nExtensions = Util::takeData16(data, offset);
		offset += 2;

		while (nExtensions--) {
			this->extensions.push_back(new Extension(data, offset));
			offset += this->extensions[this->extensions.size() - 1]->size();
		}
	} else {
		this->haveExtension = false;
	}
}

ServerHello::~ServerHello() {
	delete protocolVersion;
	delete random;
	delete sessionID;
	delete cipherSuite;
	delete compressionMethod;
	for (int i = 0; i < extensions.size(); i++)
		delete extensions[i];
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
