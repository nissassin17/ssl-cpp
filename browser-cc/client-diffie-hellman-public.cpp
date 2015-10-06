//
//  client-diffie-hellman-public.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "client-diffie-hellman-public.hpp"

ClientDiffieHellmanPublic::ClientDiffieHellmanPublic(CipherSuite *cipherSuite) : cipherSuite(cipherSuite){
}

ClientDiffieHellmanPublic::~ClientDiffieHellmanPublic(){
    
}

size_t ClientDiffieHellmanPublic::size(){
    return 0;
}

vector<uint8_t> ClientDiffieHellmanPublic::toData(){
    vector<uint8_t> data;
    return data;
}