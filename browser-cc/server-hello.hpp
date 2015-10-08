//
//  ServerHello.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/4/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef ServerHello_hpp
#define ServerHello_hpp

#include <stdio.h>
#include "util.hpp"
#include "random.hpp"
#include "protocol-version.hpp"
#include "session-id.hpp"
#include "cipher-suite.hpp"
#include "compression-method.hpp"
#include "extension.hpp"
#include "exportable.hpp"

class ServerHello: public Exportable {
public:
	ServerHello(vector<uint8_t> &data, size_t offset = 0);
	size_t size();
	CipherSuite *getCipherSuite();
	~ServerHello();
private:
	ProtocolVersion *protocolVersion;
	Random *random;
	SessionID *sessionID;
	CipherSuite *cipherSuite;
	CompressionMethod *compressionMethod;
	bool haveExtension;
	vector<Extension*> extensions;
};

#endif /* ServerHello_hpp */
