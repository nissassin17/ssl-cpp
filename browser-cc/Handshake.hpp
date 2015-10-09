//
//  handshake.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef handshake_hpp
#define handshake_hpp

#include <stdio.h>
#include <sys/_types/_size_t.h>
#include <cstdint>

#include "Certificate.hpp"
#include "Exportable.hpp"

class Certificate;
class CertificateRequest;
class ClientHello;
class ClientKeyExchange;
class Finished;
class ServerHello;
class ServerHelloDone;
class ServerKeyExchange;
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
	Handshake(HandshakeType type, void *arg = NULL, void *arg2 = NULL);
	Handshake(const vector<uint8_t> &data, size_t offset = 0, void *arg = NULL);
	size_t size() const;
	~Handshake();
	const ServerHello* getServerHello()const;
	const HandshakeType getType() const;
	const Certificate* getCertificate() const;
	const CertificateRequest* getCertificateRequest() const;
	const ClientHello* getClientHello() const;
	const ClientKeyExchange* getClientKeyExchange() const;
	const Finished* getFinished() const;
	const ServerHelloDone* getServerHelloDone() const;
	const ServerKeyExchange* getServerKeyExchange() const;

private:


	HandshakeType type;
	Exportable *body;
};

#endif /* handshake_hpp */
