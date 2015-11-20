//
//  ServerHello.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/4/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef ServerHello_hpp
#define ServerHello_hpp


#include <cstdint>
#include <vector>

#include "Exportable.hpp"
#include "Extension.hpp"

class CipherSuite;
class CompressionMethod;
class ProtocolVersion;
class Random;
class SessionID;

class ServerHello: public Exportable {
public:
	ServerHello(const vector<uint8_t> &data, size_t offset = 0);
	virtual size_t size() const;
	const CipherSuite *getCipherSuite() const;
	virtual ~ServerHello();
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
