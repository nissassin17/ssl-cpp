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

class Handshake : public Exportable {
public:
    enum HandshakeType{
        HELLO_REQUEST = 0,
        CLIENT_HELLO = 1,
        SERVER_HELLO = 2,
        CERTIFICATE = 11,
        SERVER_KEY_EXCHANGE = 12,
        CERTIFICATE_REQUEST = 13,
        SERVER_HELO_DONE = 14,
        CERTIFICATE_VERIFY = 15,
        CLIENT_KEY_EXCHANGE = 16,
        FINISHED = 20,
        NONE = 255
    };

    vector<uint8_t> toData();
    ~Handshake();
    Handshake();
    Handshake(vector<uint8_t> data, size_t offset = 0);
    size_t size();
    
private:
    HandshakeType type;
    ClientHello *clientHello;
    ServerHello *serverHello;
};

#endif /* handshake_hpp */
