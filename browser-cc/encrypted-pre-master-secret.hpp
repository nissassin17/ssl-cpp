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
#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>

#include "exportable.hpp"

class ASN1Cert;
class CipherSuite;
class PreMasterSecret;

class EncryptedPreMasterSecret: public Exportable {

public:
	EncryptedPreMasterSecret(CipherSuite *cipherSuite, ASN1Cert *asn1Cert);
	size_t size();
	vector<uint8_t> toData();
	~EncryptedPreMasterSecret();
private:
	CipherSuite *cipherSuite = NULL;
	PreMasterSecret *preMasterSecret = NULL;
	ASN1Cert *asn1Cert = NULL;
};

#endif /* encrypted_pre_master_secret_hpp */
