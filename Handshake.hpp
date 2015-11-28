//
//  handshake.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef handshake_hpp
#define handshake_hpp

#include <stdio.h>

#include <cstdint>

#include "Certificate.hpp"
#include "Exportable.hpp"

#include "Certificate.hpp"
#include "CertificateRequest.hpp"
#include "ClientHello.hpp"
#include "ClientKeyExchange.hpp"
#include "Err.hpp"
#include "Finished.hpp"
#include "ServerHello.hpp"
#include "ServerHelloDone.hpp"
#include "ServerKeyExchange.hpp"
#include "Util.hpp"
using namespace std;

class Handshake : public Exportable {
public:
	enum HandshakeType {
		HELLO_REQUEST = 0,
		CLIENT_HELLO = 1,
		SERVER_HELLO = 2,
		CERTIFICATE = 11,
		SERVER_KEY_EXCHANGE = 12,
		CERTIFICATE_REQUEST = 13,
		SERVER_HELLO_DONE = 14,
		CERTIFICATE_VERIFY = 15,
		CLIENT_KEY_EXCHANGE = 16,
		FINISHED = 20,
		NONE = 255
	};

	virtual vector<uint8_t> toData() const;
	Handshake(HandshakeType type, const void *arg = NULL, const void *arg2 = NULL);
	Handshake(const vector<uint8_t> &data, size_t offset = 0, const void *arg = NULL);
	size_t size() const;
	shared_ptr<const ServerHello> getServerHello()const;
	const HandshakeType getType() const;
	shared_ptr<const Certificate> getCertificate() const;
	shared_ptr<const CertificateRequest> getCertificateRequest() const;
	shared_ptr<const ClientHello> getClientHello() const;
	shared_ptr<const ClientKeyExchange> getClientKeyExchange() const;
	shared_ptr<const Finished> getFinished() const;
	shared_ptr<const ServerHelloDone> getServerHelloDone() const;
	shared_ptr<const ServerKeyExchange> getServerKeyExchange() const;

private:


	HandshakeType type;
	shared_ptr<Exportable> body;
};

#endif /* handshake_hpp */
