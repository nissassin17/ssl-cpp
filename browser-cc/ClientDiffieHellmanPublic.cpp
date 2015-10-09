//
//  client-diffie-hellman-public.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "ClientDiffieHellmanPublic.hpp"

ClientDiffieHellmanPublic::ClientDiffieHellmanPublic(CipherSuite *cipherSuite) :
		cipherSuite(cipherSuite) {
}

ClientDiffieHellmanPublic::~ClientDiffieHellmanPublic() {

}

size_t ClientDiffieHellmanPublic::size() const{
	return 0;
}

vector<uint8_t> ClientDiffieHellmanPublic::toData() const{
	vector<uint8_t> data;
	return data;
}
