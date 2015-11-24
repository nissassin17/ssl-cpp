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

#include "ProtocolVersion.hpp"
#include "Random.hpp"
#include "SessionID.hpp"

class ClientHello : public Exportable {
public:
private:
	shared_ptr<ProtocolVersion> protocolVersion;
	shared_ptr<Random> random;
	shared_ptr<SessionID> sessionID;
	vector<shared_ptr<CipherSuite> > cipherSuites;
	vector<shared_ptr<CompressionMethod> > compressionMethods;
	vector<shared_ptr<Extension> > extensions;
	bool haveExtension;

public:
	virtual vector<uint8_t> toData() const;
	ClientHello();
	virtual size_t size()const;

};

#endif /* client_hello_hpp */
