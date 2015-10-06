//
//  client-diffie-hellman-public.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef client_diffie_hellman_public_hpp
#define client_diffie_hellman_public_hpp

#include <stdio.h>
#include "util.hpp"
#include "exportable.hpp"
#include "cipher-suite.hpp"

class ClientDiffieHellmanPublic : public Exportable{
    
public:
    ClientDiffieHellmanPublic(CipherSuite *cipherSuite);
    ~ClientDiffieHellmanPublic();
    vector<uint8_t> toData();
    size_t size();
private:
    CipherSuite *cipherSuite = NULL;
};

#endif /* client_diffie_hellman_public_hpp */
