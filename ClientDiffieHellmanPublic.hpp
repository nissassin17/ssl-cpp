//
//  client-diffie-hellman-public.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef client_diffie_hellman_public_hpp
#define client_diffie_hellman_public_hpp

#include <stdio.h>

#include <cstdint>
#include <vector>

#include "Exportable.hpp"

#include "CipherSuite.hpp"

class ClientDiffieHellmanPublic: public Exportable {

public:
	ClientDiffieHellmanPublic(shared_ptr<const CipherSuite> cipherSuite);
	virtual vector<uint8_t> toData() const;
	virtual size_t size() const;
private:
	const shared_ptr<const CipherSuite> cipherSuite;
};

#endif /* client_diffie_hellman_public_hpp */
