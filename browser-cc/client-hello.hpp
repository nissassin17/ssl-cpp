//
//  client-hello.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef client_hello_hpp
#define client_hello_hpp

#include <stdio.h>
#include "exportable.hpp"
#include "protocol-version.hpp"
#include "random.hpp"
#include "session-id.hpp"
#include "cipher-suite.hpp"
#include "compression-method.hpp"
#include "extension.hpp"

class ClientHello : public Exportable{
public:

private:
    ProtocolVersion protocolVersion;
    Random random;
    SessionID sessionID;
    vector<CipherSuite> cipherSuites;
    vector<CompressionMethod> compressionMethods;
    vector<Extension> extensions;
    bool haveExtension;

public:
    vector<uint8_t> toData();
    ClientHello();
    size_t size();
    
};

#endif /* client_hello_hpp */
