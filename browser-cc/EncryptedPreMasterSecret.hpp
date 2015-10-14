//
//  encrypted-pre-master-secret.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef encrypted_pre_master_secret_hpp
#define encrypted_pre_master_secret_hpp

#include <stdio.h>

#include <cstdint>
#include <vector>

#include "Exportable.hpp"

class ASN1Cert;
class CipherSuite;
class PreMasterSecret;

class EncryptedPreMasterSecret: public Exportable {

public:
	EncryptedPreMasterSecret(const CipherSuite* cipherSuite,
			const ASN1Cert* asn1Cert) :
			cipherSuite(cipherSuite), asn1Cert(asn1Cert), preMasterSecret(
					new PreMasterSecret()) {
		//    std::cout << "======ASN1Cert BEGIN=====" << endl;
		//    std::cout << Util::readableForm(asn1Cert->toData()) << endl;
		//    std::cout << "======ASN1Cert END=======" << endl;
		//calculate here
		vector<uint8_t> modulus(asn1Cert->getRSAModulus());
		int exponent = asn1Cert->getExponent();
		vector<uint8_t> dataToEncrypt(preMasterSecret->toData());
		//start encrypting

	}
	virtual size_t size() const {
		//return size after encrypted data in premastersecret
		return 2; //2 stand for data length. result should be plused by encrypted data
	}
	virtual vector<uint8_t> toData()const;
	~EncryptedPreMasterSecret() {
		delete preMasterSecret;
	}
private:
	const CipherSuite * const cipherSuite;
	PreMasterSecret *preMasterSecret;
	const ASN1Cert * const asn1Cert;
	vector<uint8_t> encryptedData;
};
#endif /* encrypted_pre_master_secret_hpp */
