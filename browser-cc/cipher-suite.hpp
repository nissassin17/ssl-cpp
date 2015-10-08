//
//  cipher-suite.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef cipher_suite_hpp
#define cipher_suite_hpp

#include <stdio.h>
#include "exportable.hpp"
#include "cipher.hpp"
#include "mac.hpp"
class CipherSuite {
public:
	CipherSuite(vector<uint8_t> &data, size_t offset = 0);
	size_t size();
	vector<uint8_t> toData();

	enum KeyExchangeType {
		KEY_EXCHANGE_NULL, RSA, DH_DSS, DH_RSA, DHE_DSS, DHE_RSA, DH_anon
	};
	enum HashType {
		NULL_NULL,
		NULL_MD5,
		NULL_SHA,
		NULL_SHA256,
		RC4_128_MD5,
		RC4_128_SHA,
		_3DES_EDE_CBC_SHA,
		AES_128_CBC_SHA,
		AES_256_CBC_SHA,
		AES_128_CBC_SHA256,
		AES_256_CBC_SHA256
	};

	enum CipherSuiteType {
		TLS_NULL_WITH_NULL_NULL = 0x0000,

		TLS_RSA_WITH_NULL_MD5 = 0x0001,
		TLS_RSA_WITH_NULL_SHA = 0x0002,
		TLS_RSA_WITH_NULL_SHA256 = 0x003B,
		TLS_RSA_WITH_RC4_128_MD5 = 0x0004,
		TLS_RSA_WITH_RC4_128_SHA = 0x0005,
		TLS_RSA_WITH_3DES_EDE_CBC_SHA = 0x000A,
		TLS_RSA_WITH_AES_128_CBC_SHA = 0x002F,
		TLS_RSA_WITH_AES_256_CBC_SHA = 0x0035,
		TLS_RSA_WITH_AES_128_CBC_SHA256 = 0x003C,
		TLS_RSA_WITH_AES_256_CBC_SHA256 = 0x003D,

		TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA = 0x000D,
		TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA = 0x0010,
		TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA = 0x0013,
		TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA = 0x0016,
		TLS_DH_DSS_WITH_AES_128_CBC_SHA = 0x0030,
		TLS_DH_RSA_WITH_AES_128_CBC_SHA = 0x0031,
		TLS_DHE_DSS_WITH_AES_128_CBC_SHA = 0x0032,
		TLS_DHE_RSA_WITH_AES_128_CBC_SHA = 0x0033,
		TLS_DH_DSS_WITH_AES_256_CBC_SHA = 0x0036,
		TLS_DH_RSA_WITH_AES_256_CBC_SHA = 0x0037,
		TLS_DHE_DSS_WITH_AES_256_CBC_SHA = 0x0038,
		TLS_DHE_RSA_WITH_AES_256_CBC_SHA = 0x0039,
		TLS_DH_DSS_WITH_AES_128_CBC_SHA256 = 0x003E,
		TLS_DH_RSA_WITH_AES_128_CBC_SHA256 = 0x003F,
		TLS_DHE_DSS_WITH_AES_128_CBC_SHA256 = 0x0040,
		TLS_DHE_RSA_WITH_AES_128_CBC_SHA256 = 0x0067,
		TLS_DH_DSS_WITH_AES_256_CBC_SHA256 = 0x0068,
		TLS_DH_RSA_WITH_AES_256_CBC_SHA256 = 0x0069,
		TLS_DHE_DSS_WITH_AES_256_CBC_SHA256 = 0x006A,
		TLS_DHE_RSA_WITH_AES_256_CBC_SHA256 = 0x006B,

		TLS_DH_anon_WITH_RC4_128_MD5 = 0x0018,
		TLS_DH_anon_WITH_3DES_EDE_CBC_SHA = 0x001B,
		TLS_DH_anon_WITH_AES_128_CBC_SHA = 0x0034,
		TLS_DH_anon_WITH_AES_256_CBC_SHA = 0x003A,
		TLS_DH_anon_WITH_AES_128_CBC_SHA256 = 0x006C,
		TLS_DH_anon_WITH_AES_256_CBC_SHA256 = 0x006D,
	};

	CipherSuite(CipherSuiteType suite = TLS_NULL_WITH_NULL_NULL);
	KeyExchangeType getKeyExchange();
	~CipherSuite();
	MAC *getMac();
	Cipher *getCipher();
private:
	void setType(CipherSuiteType type);
	KeyExchangeType keyExchange;
	Cipher *cipher = NULL;
	MAC *mac = NULL;
	CipherSuiteType suite;
};

#endif /* cipher_suite_hpp */
