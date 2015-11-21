//
//  cipher-suite.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include "CipherSuite.hpp"

#include "Cipher.hpp"
#include "MAC.hpp"
#include "Util.hpp"
#include "BitUtil.hpp"

CipherSuite::CipherSuite(CipherSuiteType type) :
suite(TLS_NULL_WITH_NULL_NULL),
cipher(NULL),
keyExchange(KEY_EXCHANGE_NULL),
mac(NULL)
{
	setType(type);
}

void CipherSuite::setType(CipherSuiteType type) {
	this->suite = type;
	switch (this->suite) {
	case TLS_NULL_WITH_NULL_NULL:
		keyExchange = KEY_EXCHANGE_NULL;
		cipher = new Cipher(Cipher::CIPHER_NULL);
		mac = new MAC(MAC::MAC_NULL);
		break;

	case TLS_RSA_WITH_NULL_MD5:
		keyExchange = RSA;
		cipher = new Cipher(Cipher::CIPHER_NULL);
		mac = new MAC(MAC::MD5);
		break;
	case TLS_RSA_WITH_NULL_SHA:
		keyExchange = RSA;
		cipher = new Cipher(Cipher::CIPHER_NULL);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_RSA_WITH_NULL_SHA256:
		keyExchange = RSA;
		cipher = new Cipher(Cipher::CIPHER_NULL);
		mac = new MAC(MAC::SHA256);
		break;
	case TLS_RSA_WITH_RC4_128_MD5:
		keyExchange = RSA;
		cipher = new Cipher(Cipher::RC4_128);
		mac = new MAC(MAC::MD5);
		break;
	case TLS_RSA_WITH_RC4_128_SHA:
		keyExchange = RSA;
		cipher = new Cipher(Cipher::RC4_128);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_RSA_WITH_3DES_EDE_CBC_SHA:
		keyExchange = RSA;
		cipher = new Cipher(Cipher::_3DES_EDE_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_RSA_WITH_AES_128_CBC_SHA:
		keyExchange = RSA;
		cipher = new Cipher(Cipher::AES_128_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_RSA_WITH_AES_256_CBC_SHA:
		keyExchange = RSA;
		cipher = new Cipher(Cipher::AES_256_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_RSA_WITH_AES_128_CBC_SHA256:
		keyExchange = RSA;
		cipher = new Cipher(Cipher::AES_128_CBC);
		mac = new MAC(MAC::SHA256);
		break;
	case TLS_RSA_WITH_AES_256_CBC_SHA256:
		keyExchange = RSA;
		cipher = new Cipher(Cipher::AES_256_CBC);
		mac = new MAC(MAC::SHA256);
		break;
	case TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA:
		keyExchange = DH_DSS;
		cipher = new Cipher(Cipher::_3DES_EDE_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA:
		keyExchange = DH_RSA;
		cipher = new Cipher(Cipher::_3DES_EDE_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA:
		keyExchange = DHE_DSS;
		cipher = new Cipher(Cipher::_3DES_EDE_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA:
		keyExchange = DHE_RSA;
		cipher = new Cipher(Cipher::_3DES_EDE_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DH_anon_WITH_RC4_128_MD5:
		keyExchange = DH_anon;
		cipher = new Cipher(Cipher::RC4_128);
		mac = new MAC(MAC::MD5);
		break;
	case TLS_DH_anon_WITH_3DES_EDE_CBC_SHA:
		keyExchange = DH_anon;
		cipher = new Cipher(Cipher::_3DES_EDE_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DH_DSS_WITH_AES_128_CBC_SHA:
		keyExchange = DH_DSS;
		cipher = new Cipher(Cipher::AES_128_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DH_RSA_WITH_AES_128_CBC_SHA:
		keyExchange = DH_RSA;
		cipher = new Cipher(Cipher::AES_128_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DHE_DSS_WITH_AES_128_CBC_SHA:
		keyExchange = DHE_DSS;
		cipher = new Cipher(Cipher::AES_128_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DHE_RSA_WITH_AES_128_CBC_SHA:
		keyExchange = DHE_RSA;
		cipher = new Cipher(Cipher::AES_128_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DH_anon_WITH_AES_128_CBC_SHA:
		keyExchange = DH_anon;
		cipher = new Cipher(Cipher::AES_128_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DH_DSS_WITH_AES_256_CBC_SHA:
		keyExchange = DH_DSS;
		cipher = new Cipher(Cipher::AES_256_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DH_RSA_WITH_AES_256_CBC_SHA:
		keyExchange = DH_RSA;
		cipher = new Cipher(Cipher::AES_256_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DHE_DSS_WITH_AES_256_CBC_SHA:
		keyExchange = DHE_DSS;
		cipher = new Cipher(Cipher::AES_256_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DHE_RSA_WITH_AES_256_CBC_SHA:
		keyExchange = DHE_RSA;
		cipher = new Cipher(Cipher::AES_256_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DH_anon_WITH_AES_256_CBC_SHA:
		keyExchange = DH_anon;
		cipher = new Cipher(Cipher::AES_256_CBC);
		mac = new MAC(MAC::SHA);
		break;
	case TLS_DH_DSS_WITH_AES_128_CBC_SHA256:
		keyExchange = DH_DSS;
		cipher = new Cipher(Cipher::AES_128_CBC);
		mac = new MAC(MAC::SHA256);
		break;
	case TLS_DH_RSA_WITH_AES_128_CBC_SHA256:
		keyExchange = DH_RSA;
		cipher = new Cipher(Cipher::AES_128_CBC);
		mac = new MAC(MAC::SHA256);
		break;
	case TLS_DHE_DSS_WITH_AES_128_CBC_SHA256:
		keyExchange = DHE_DSS;
		cipher = new Cipher(Cipher::AES_128_CBC);
		mac = new MAC(MAC::SHA256);
		break;
	case TLS_DHE_RSA_WITH_AES_128_CBC_SHA256:
		keyExchange = DHE_RSA;
		cipher = new Cipher(Cipher::AES_128_CBC);
		mac = new MAC(MAC::SHA256);
		break;
	case TLS_DH_anon_WITH_AES_128_CBC_SHA256:
		keyExchange = DH_anon;
		cipher = new Cipher(Cipher::AES_128_CBC);
		mac = new MAC(MAC::SHA256);
		break;
	case TLS_DH_DSS_WITH_AES_256_CBC_SHA256:
		keyExchange = DH_DSS;
		cipher = new Cipher(Cipher::AES_256_CBC);
		mac = new MAC(MAC::SHA256);
		break;
	case TLS_DH_RSA_WITH_AES_256_CBC_SHA256:
		keyExchange = DH_RSA;
		cipher = new Cipher(Cipher::AES_256_CBC);
		mac = new MAC(MAC::SHA256);
		break;
	case TLS_DHE_DSS_WITH_AES_256_CBC_SHA256:
		keyExchange = DHE_DSS;
		cipher = new Cipher(Cipher::AES_256_CBC);
		mac = new MAC(MAC::SHA256);
		break;
	case TLS_DHE_RSA_WITH_AES_256_CBC_SHA256:
		keyExchange = DHE_RSA;
		cipher = new Cipher(Cipher::AES_256_CBC);
		mac = new MAC(MAC::SHA256);
		break;
	case TLS_DH_anon_WITH_AES_256_CBC_SHA256:
		keyExchange = DH_anon;
		cipher = new Cipher(Cipher::AES_256_CBC);
		mac = new MAC(MAC::SHA256);
		break;
	default:
		break;
	}

}

vector<uint8_t> CipherSuite::toData()  const{
	uint8_t high(BitUtil::filterByte(this->suite, 8));
	uint8_t low(BitUtil::filterByte(this->suite));
	vector<uint8_t> data;
	data.push_back(high);
	data.push_back(low);
	return data;
}

size_t CipherSuite::size() const{
	return 2;
}

CipherSuite::KeyExchangeType CipherSuite::getKeyExchange() const{
	return keyExchange;
}
const Cipher *CipherSuite::getCipher() const{
	return cipher;
}
const MAC *CipherSuite::getMac() const{
	return mac;
}

CipherSuite::CipherSuite(const vector<uint8_t> &data, size_t offset) {
	setType((CipherSuiteType) Util::takeData16(data, offset));
}

CipherSuite::~CipherSuite() {
	delete cipher;
	delete mac;
}

CipherSuite::CipherSuite(const CipherSuite& cipherSuite):
	keyExchange(cipherSuite.keyExchange),
	cipher(NULL),
	mac(NULL),
	suite(cipherSuite.suite){
	if (cipherSuite.cipher != NULL)
		cipher = new Cipher(*(cipherSuite.cipher));
	if (cipherSuite.mac != NULL)
		mac = new MAC(*(cipherSuite.mac));
}
