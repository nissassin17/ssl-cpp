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

class Certificate;
class CertificateRequest;
class ClientHello;
class ClientKeyExchange;
class Finished;
class ServerHello;
class ServerHelloDone;
class ServerKeyExchange;
using namespace std;

class Handshake {
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

	vector<uint8_t> toData();
	Handshake(HandshakeType type, void *arg = NULL, void *arg2 = NULL);
	Handshake(vector<uint8_t> &data, size_t offset = 0, void *arg = NULL);
	size_t size();
	~Handshake();
	ServerHello *getServerHello();
	HandshakeType getType();
	Certificate *getCertificate();

private:

	ClientKeyExchange *clientKeyExchange = NULL;
	HandshakeType type;
	Finished *finished = NULL;
	ClientHello *clientHello = NULL;
	ServerHello *serverHello = NULL;
	Certificate *certificate = NULL;
	ServerKeyExchange *serverKeyExchange = NULL;
	ServerHelloDone *serverHelloDone = NULL;
	CertificateRequest *certificateRequest = NULL;
};

#endif /* handshake_hpp */
