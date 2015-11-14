//
//  encrypted-pre-master-secret.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "EncryptedPreMasterSecret.hpp"
#include "PreMasterSecret.hpp"
#include "Util.hpp"

vector<uint8_t> EncryptedPreMasterSecret::toData() const{
	//return encrypted type as public-key-encrypted
	vector<uint8_t> encryptedData, data;

	//default with https://google.com
//TLS_RSA_WITH_AES_128_CBC_SHA256

	Util::addData(data, (uint16_t) encryptedData.size());
	return data;
}

EncryptedPreMasterSecret::EncryptedPreMasterSecret(const CipherSuite* cipherSuite,
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
size_t EncryptedPreMasterSecret::size() const {
    //return size after encrypted data in premastersecret
    return 2; //2 stand for data length. result should be plused by encrypted data
}
EncryptedPreMasterSecret::~EncryptedPreMasterSecret() {
    delete preMasterSecret;
}