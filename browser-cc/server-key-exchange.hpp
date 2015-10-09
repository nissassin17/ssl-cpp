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
#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>

#include "exportable.hpp"

class CipherSuite;
class DigitallySigned;
class ServerDHParams;

class ServerKeyExchange: public Exportable {
public:
	ServerKeyExchange(const CipherSuite *cipherSuite,const vector<uint8_t> &data,
			size_t offset = 0);
	virtual size_t size() const;
	virtual ~ServerKeyExchange();

private:
	CipherSuite *cipherSuite;
	ServerDHParams *params;
	DigitallySigned *signedParams;
};

#endif /* server_key_exchange_hpp */
