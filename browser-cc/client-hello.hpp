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

class ClientHello : Exportable{
private:
    ProtocolVersion protocolVersion;
    Random random;
    SessionID sessionID;
    vector<CipherSuite> cihperSuites;
    vector<CompressionMethod> compressionMethods;
    vector<Extension> extensions;
public:

    
};

#endif /* client_hello_hpp */
