//
//  server-key-exchange.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef server_key_exchange_hpp
#define server_key_exchange_hpp

#include <stdio.h>
#include "exportable.hpp"
#include "util.hpp"
#include "server-dh-params.hpp"
#include "digitally-signed.hpp"
#include "cipher-suite.hpp"

class ServerKeyExchange : public Exportable{
public:
    ServerKeyExchange(CipherSuite::EncryptType algorithm, vector<uint8_t> data, size_t offset = 0);
    size_t size();
    ~ServerKeyExchange();
    
    
private:
    CipherSuite::EncryptType encryptType;
    ServerDHParams *params;
    DigitallySigned *signedParams;
};

#endif /* server_key_exchange_hpp */
