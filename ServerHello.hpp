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

#include "CipherSuite.hpp"
#include "CompressionMethod.hpp"
#include "ProtocolVersion.hpp"
#include "Random.hpp"
#include "SessionID.hpp"

class ServerHello: public Exportable {
public:
	ServerHello(const vector<uint8_t> &data, size_t offset = 0);
	virtual size_t size() const;
	const shared_ptr<CipherSuite>& getCipherSuite() const;

private:
	shared_ptr<ProtocolVersion> protocolVersion;
	shared_ptr<Random> random;
	shared_ptr<SessionID> sessionID;
	shared_ptr<CipherSuite> cipherSuite;
	shared_ptr<CompressionMethod> compressionMethod;
	bool haveExtension;
	vector<shared_ptr<Extension> > extensions;
};

#endif /* ServerHello_hpp */
