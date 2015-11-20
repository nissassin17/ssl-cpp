//
//  client-hello.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef client_hello_hpp
#define client_hello_hpp


#include <cstdint>
#include <vector>

#include "CipherSuite.hpp"
#include "CompressionMethod.hpp"
#include "Exportable.hpp"
#include "Extension.hpp"

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
