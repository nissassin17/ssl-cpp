//
//  server-key-exchange.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "server-key-exchange.hpp"

ServerKeyExchange::ServerKeyExchange(CipherSuite::EncryptType algorithm, vector<uint8_t> data, size_t offset)
: encryptType(algorithm){
    switch (algorithm){
        case CipherSuite::DH_ANON:
            this->params = new ServerDHParams(data, offset);
            offset += this->params->size();
            break;
            
        case CipherSuite::DHE_RSA:
        case CipherSuite::DHE_DSS:
            this->params = new ServerDHParams(data, offset);
            this->signedParams = new DigitallySigned(data, offset);
            offset += this->params->size();
            break;
            
        case CipherSuite::RSA:
        case CipherSuite::DH_RSA:
        case CipherSuite::DH_DSS:
            break;
        default: //case NONE:
            break;
    }
}

ServerKeyExchange::~ServerKeyExchange(){
    switch (encryptType){
        case CipherSuite::DH_ANON:
            delete this->params;
            break;
            
        case CipherSuite::DHE_RSA:
        case CipherSuite::DHE_DSS:
            delete this->params;
            delete this->signedParams;
            break;
            
        case CipherSuite::RSA:
        case CipherSuite::DH_RSA:
        case CipherSuite::DH_DSS:
            break;
        default: //case NONE:
            break;
    }
}

size_t ServerKeyExchange::size(){
    size_t result(0);
    return result;
}