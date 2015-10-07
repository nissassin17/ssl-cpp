//
//  client-key-exchange.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef client_key_exchange_hpp
#define client_key_exchange_hpp

#include <stdio.h>
#include "util.hpp"
#include "exportable.hpp"
#include "cipher-suite.hpp"
#include "encrypted-pre-master-secret.hpp"
#include "client-diffie-hellman-public.hpp"

class ClientKeyExchange : public Exportable{
public:
    ClientKeyExchange(CipherSuite *cipherSuite, ASN1Cert *asn1Cert);
    vector<uint8_t> toData();
    size_t size();
    ~ClientKeyExchange();
private:
    CipherSuite *cipherSuite = NULL;
    EncryptedPreMasterSecret *encryptedPreMasterSecret = NULL;
    ClientDiffieHellmanPublic *clientDiffieHellmanPublic = NULL;
};

#endif /* client_key_exchange_hpp */
