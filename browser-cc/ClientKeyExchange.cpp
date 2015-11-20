//
//  client-key-exchange.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "ClientKeyExchange.hpp"

#include "CipherSuite.hpp"
#include "ClientDiffieHellmanPublic.hpp"
#include "EncryptedPreMasterSecret.hpp"
#include "Log.h"

ClientKeyExchange::ClientKeyExchange(const CipherSuite *cipherSuite,
		const Asn1Cert *asn1Cert) :
		cipherSuite(cipherSuite),
		encryptedPreMasterSecret(NULL),
		clientDiffieHellmanPublic(NULL){

	Log::info << "Now making client_key_exchange. Currently only support RSA" << endl;

	switch (cipherSuite->getKeyExchange()) {
	case CipherSuite::RSA:
		encryptedPreMasterSecret = new EncryptedPreMasterSecret(cipherSuite,
				asn1Cert);
		break;
	case CipherSuite::DHE_DSS:
	case CipherSuite::DHE_RSA:
	case CipherSuite::DH_DSS:
	case CipherSuite::DH_RSA:
	case CipherSuite::DH_anon:
		clientDiffieHellmanPublic = new ClientDiffieHellmanPublic(cipherSuite);
		break;

	default: //none
		break;
	}

}

ClientKeyExchange::~ClientKeyExchange() {
	delete clientDiffieHellmanPublic;
	delete encryptedPreMasterSecret;
}

size_t ClientKeyExchange::size() const{
	switch (cipherSuite->getKeyExchange()) {
	case CipherSuite::RSA:
		return encryptedPreMasterSecret->size();
		break;
	case CipherSuite::DHE_DSS:
	case CipherSuite::DHE_RSA:
	case CipherSuite::DH_DSS:
	case CipherSuite::DH_RSA:
	case CipherSuite::DH_anon:
		return clientDiffieHellmanPublic->size();
		break;

	default: //none
		break;
	}
	return 0;
}

vector<uint8_t> ClientKeyExchange::toData() const{
	switch (cipherSuite->getKeyExchange()) {
	case CipherSuite::RSA:
		return encryptedPreMasterSecret->toData();
		break;
	case CipherSuite::DHE_DSS:
	case CipherSuite::DHE_RSA:
	case CipherSuite::DH_DSS:
	case CipherSuite::DH_RSA:
	case CipherSuite::DH_anon:
		return clientDiffieHellmanPublic->toData();
		break;

	default: //none
		break;
	}
	return vector<uint8_t>();
}
