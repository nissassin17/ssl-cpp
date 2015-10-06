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
#include "exportable.hpp"
#include "client-hello.hpp"
#include "server-hello.hpp"
#include "certificate.hpp"
#include "server-key-exchange.hpp"
#include "server-hello-done.hpp"
#include "certificate-request.hpp"
#include "finished.hpp"
#include "client-key-exchange.hpp"

class Handshake : public Exportable {
public:
    enum HandshakeType{
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
    Handshake(HandshakeType type, void *arg = NULL);
    Handshake(vector<uint8_t> data, size_t offset = 0, void *arg = NULL);
    size_t size();
    ~Handshake();
    ServerHello *getServerHello();
    HandshakeType getType();
    
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
