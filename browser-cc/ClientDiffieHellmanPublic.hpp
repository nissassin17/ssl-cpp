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

#include "Exportable.hpp"

class CipherSuite;

class ClientDiffieHellmanPublic: public Exportable {

public:
	ClientDiffieHellmanPublic(CipherSuite *cipherSuite);
	~ClientDiffieHellmanPublic();
	virtual vector<uint8_t> toData()const;
	virtual size_t size()const;
private:
	CipherSuite *cipherSuite;
};

#endif /* client_diffie_hellman_public_hpp */
