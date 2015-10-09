//
//  client-hello.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef client_hello_hpp
#define client_hello_hpp

#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>

#include "cipher-suite.hpp"
#include "compression-method.hpp"
#include "extension.hpp"
#include "exportable.hpp"

class ProtocolVersion;
class Random;
class SessionID;

class ClientHello : public Exportable {
public:

private:
	ProtocolVersion *protocolVersion;
	Random *random;
	SessionID *sessionID;
	vector<CipherSuite*> cipherSuites;
	vector<CompressionMethod*> compressionMethods;
	vector<Extension*> extensions;
	bool haveExtension;

public:
	virtual vector<uint8_t> toData() const;
	ClientHello();
	virtual size_t size()const;
	~ClientHello();

};

#endif /* client_hello_hpp */
