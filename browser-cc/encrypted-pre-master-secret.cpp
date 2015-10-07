//
//  encrypted-pre-master-secret.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "encrypted-pre-master-secret.hpp"
#include <iostream>

EncryptedPreMasterSecret::EncryptedPreMasterSecret(CipherSuite *cipherSuite, ASN1Cert *asn1Cert) : cipherSuite(cipherSuite), asn1Cert(asn1Cert){
    

//    std::cout << "======ASN1Cert BEGIN=====" << endl;
//    std::cout << Util::readableForm(asn1Cert->toData()) << endl;
//    std::cout << "======ASN1Cert END=======" << endl;
    
    preMasterSecret = new PreMasterSecret();
}

EncryptedPreMasterSecret::~EncryptedPreMasterSecret(){
    delete preMasterSecret;
}

size_t EncryptedPreMasterSecret::size(){
    //return size after encrypted data in premastersecret
 
    return 2;//2 stand for data length. result should be plused by encrypted data
}

vector<uint8_t> EncryptedPreMasterSecret::toData(){
    //return encrypted type as public-key-encrypted
    vector<uint8_t> encryptedData, data;
    
    //default with https://google.com
//TLS_RSA_WITH_AES_128_CBC_SHA256
    
    Util::addData(data, (uint16_t) encryptedData.size());
    return data;
}