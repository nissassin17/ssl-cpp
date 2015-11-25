//
//  server-key-exchange.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef server_key_exchange_hpp
#define server_key_exchange_hpp

#include <stdio.h>

#include <cstdint>
#include <vector>

#include "Exportable.hpp"

#include "CipherSuite.hpp"
#include "DigitallySigned.hpp"
#include "ServerDHParams.hpp"

class ServerKeyExchange: public Exportable {
public:
	ServerKeyExchange(shared_ptr<const CipherSuite> cipherSuite,const vector<uint8_t> &data,
			size_t offset = 0);
	virtual size_t size() const;

private:
	const shared_ptr<const CipherSuite> cipherSuite;
	shared_ptr<ServerDHParams> params;
	shared_ptr<DigitallySigned> signedParams;
};

#endif /* server_key_exchange_hpp */
