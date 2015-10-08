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
#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>

#include "exportable.hpp"

class CipherSuite;

class ClientDiffieHellmanPublic: public Exportable {

public:
	ClientDiffieHellmanPublic(CipherSuite *cipherSuite);
	~ClientDiffieHellmanPublic();
	vector<uint8_t> toData();
	size_t size();
private:
	CipherSuite *cipherSuite = NULL;
};

#endif /* client_diffie_hellman_public_hpp */
