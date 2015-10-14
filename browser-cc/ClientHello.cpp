//
//  client-hello.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "ClientHello.hpp"
#include "ProcotolVersion.hpp"
#include "Random.hpp"
#include "SessionID.hpp"
#include "Util.hpp"

ClientHello::~ClientHello() {
	delete protocolVersion;
	delete random;
	delete sessionID;
	for (int i = 0; i < cipherSuites.size(); i++)
		delete cipherSuites[i];
	for (int i = 0; i < compressionMethods.size(); i++)
		delete compressionMethods[i];
	for (int i = 0; i < extensions.size(); i++)
		delete extensions[i];
}
ClientHello::ClientHello() :
		random(new Random()), sessionID(new SessionID()), haveExtension(false), protocolVersion(
				new ProtocolVersion()) {
	this->cipherSuites.push_back(
			new CipherSuite(CipherSuite::TLS_NULL_WITH_NULL_NULL));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_RSA_WITH_NULL_MD5                 ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_RSA_WITH_NULL_SHA                 ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_RSA_WITH_NULL_SHA256              ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_RSA_WITH_RC4_128_MD5              ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_RSA_WITH_RC4_128_SHA              ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_RSA_WITH_3DES_EDE_CBC_SHA         ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_RSA_WITH_AES_128_CBC_SHA          ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_RSA_WITH_AES_256_CBC_SHA          ));
	this->cipherSuites.push_back(
			new CipherSuite(CipherSuite::TLS_RSA_WITH_AES_128_CBC_SHA256));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_RSA_WITH_AES_256_CBC_SHA256       ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA      ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA      ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA     ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA     ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_DSS_WITH_AES_128_CBC_SHA       ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_RSA_WITH_AES_128_CBC_SHA       ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DHE_DSS_WITH_AES_128_CBC_SHA      ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DHE_RSA_WITH_AES_128_CBC_SHA      ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_DSS_WITH_AES_256_CBC_SHA       ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_RSA_WITH_AES_256_CBC_SHA       ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DHE_DSS_WITH_AES_256_CBC_SHA      ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DHE_RSA_WITH_AES_256_CBC_SHA      ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_DSS_WITH_AES_128_CBC_SHA256    ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_RSA_WITH_AES_128_CBC_SHA256    ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DHE_DSS_WITH_AES_128_CBC_SHA256   ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DHE_RSA_WITH_AES_128_CBC_SHA256   ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_DSS_WITH_AES_256_CBC_SHA256    ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_RSA_WITH_AES_256_CBC_SHA256    ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DHE_DSS_WITH_AES_256_CBC_SHA256   ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DHE_RSA_WITH_AES_256_CBC_SHA256   ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_anon_WITH_RC4_128_MD5          ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_anon_WITH_3DES_EDE_CBC_SHA     ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_anon_WITH_AES_128_CBC_SHA      ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_anon_WITH_AES_256_CBC_SHA      ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_anon_WITH_AES_128_CBC_SHA256   ));
//	this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_DH_anon_WITH_AES_256_CBC_SHA256   ));

	this->compressionMethods.push_back(
			new CompressionMethod(CompressionMethod::Null));
}

size_t ClientHello::size() const{
	size_t result(0);

	result += this->protocolVersion->size() + this->random->size() + 2;

	for (int i = 0; i < this->cipherSuites.size(); i++)
		result += this->cipherSuites[i]->size();

	result += 1;
	for (int i = 0; i < this->compressionMethods.size(); i++)
		result += this->compressionMethods[i]->size();

	if (this->haveExtension) {
		result += 2;
		for (int i = 0; i < this->extensions.size(); i++)
			result += this->extensions[i]->size();
	} else {
		result += 2;
	}
	return result;
}

vector<uint8_t> ClientHello::toData() const{
	vector<uint8_t> data;

	Util::addData(data, this->protocolVersion->toData());

	Util::addData(data, this->random->toData());

	Util::addData(data, this->sessionID->toData());

	size_t length(0);
	for (int i = 0; i < this->cipherSuites.size(); i++) {
		length += this->cipherSuites[i]->size();
	}
	Util::addData(data, (uint16_t) length);
	for (int i = 0; i < this->cipherSuites.size(); i++)
		Util::addData(data, this->cipherSuites[i]->toData());

	length = 0;
	for (int i = 0; i < this->compressionMethods.size(); i++)
		length += this->compressionMethods[i]->size();
	data.push_back((uint8_t) length);
	for (int i = 0; i < this->compressionMethods.size(); i++)
		Util::addData(data, this->compressionMethods[i]->toData());

	if (this->haveExtension) {
		//get length
		uint16_t length = 0;
		for (int i = 0; i < this->extensions.size(); i++) {
			length += this->extensions[i]->size();
		}
		Util::addData(data, (uint16_t) length);
		for (int i = 0; i < this->extensions.size(); i++)
			Util::addData(data, this->extensions[i]->toData());
	} else {
		Util::addData(data, (uint16_t) 0);
	}

	return data;
}
