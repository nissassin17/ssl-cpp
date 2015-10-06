//
//  client-key-exchange.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "client-key-exchange.hpp"

ClientKeyExchange::ClientKeyExchange(CipherSuite *cipherSuite) : cipherSuite(cipherSuite) {

    switch (cipherSuite->encryptType()) {
        case CipherSuite::RSA:
            encryptedPreMasterSecret = new EncryptedPreMasterSecret(cipherSuite);
            break;
        case CipherSuite::DHE_DSS:
        case CipherSuite::DHE_RSA:
        case CipherSuite::DH_DSS:
        case CipherSuite::DH_RSA:
        case CipherSuite::DH_ANON:
            clientDiffieHellmanPublic = new ClientDiffieHellmanPublic(cipherSuite);
            break;
            
        default://none
            break;
    }

}

ClientKeyExchange::~ClientKeyExchange(){
    delete clientDiffieHellmanPublic;
    delete encryptedPreMasterSecret;
}

size_t ClientKeyExchange::size(){
    switch (cipherSuite->encryptType()) {
        case CipherSuite::RSA:
            return encryptedPreMasterSecret->size();
            break;
        case CipherSuite::DHE_DSS:
        case CipherSuite::DHE_RSA:
        case CipherSuite::DH_DSS:
        case CipherSuite::DH_RSA:
        case CipherSuite::DH_ANON:
            return clientDiffieHellmanPublic->size();
            break;
            
        default://none
            break;
    }
    return 0;
}

vector<uint8_t> ClientKeyExchange::toData(){
    switch (cipherSuite->encryptType()){
        case CipherSuite::RSA:
            return encryptedPreMasterSecret->toData();
            break;
        case CipherSuite::DHE_DSS:
        case CipherSuite::DHE_RSA:
        case CipherSuite::DH_DSS:
        case CipherSuite::DH_RSA:
        case CipherSuite::DH_ANON:
            return clientDiffieHellmanPublic->toData();
            break;
            
        default://none
            break;
    }
    return vector<uint8_t>();
}