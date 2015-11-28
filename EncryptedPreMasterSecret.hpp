//
//  encrypted-pre-master-secret.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef encrypted_pre_master_secret_hpp
#define encrypted_pre_master_secret_hpp

#include <stdio.h>

#include <cstdint>
#include <vector>

#include "Exportable.hpp"

#include "ASN1Cert.hpp"
#include "CipherSuite.hpp"
#include "PreMasterSecret.hpp"

class EncryptedPreMasterSecret: public Exportable {

public:
	EncryptedPreMasterSecret(shared_ptr<const CipherSuite> cipherSuite,
                             shared_ptr<const rsa::Asn1Cert> asn1Cert );
    virtual size_t size() const;
	virtual vector<uint8_t> toData() const;

private:
	const shared_ptr<const CipherSuite> cipherSuite;
	shared_ptr<PreMasterSecret> preMasterSecret;
	const shared_ptr<const rsa::Asn1Cert> asn1Cert;
	vector<uint8_t> encryptedData;
};
#endif /* encrypted_pre_master_secret_hpp */
