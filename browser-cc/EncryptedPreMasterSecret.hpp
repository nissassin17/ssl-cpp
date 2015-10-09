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
	EncryptedPreMasterSecret(const CipherSuite *cipherSuite, const ASN1Cert *asn1Cert);
	virtual size_t size() const;
	virtual vector<uint8_t> toData()const;
	~EncryptedPreMasterSecret();
private:
	const CipherSuite *cipherSuite;
	PreMasterSecret *preMasterSecret;
	const ASN1Cert *asn1Cert;
};

#endif /* encrypted_pre_master_secret_hpp */
