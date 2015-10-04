//
//  ServerHello.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/4/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "server-hello.hpp"

ServerHello::ServerHello(vector<uint8_t> &data, size_t offset){
    this->protocolVersion = ProtocolVersion(data, offset);
    offset += this->protocolVersion.size();
    
    this->random = Random(data, offset);
    offset += this->random.size();
    
    this->sessionID = SessionID(data, offset);
    offset += this->sessionID.size();
    
    this->cipherSuite = CipherSuite(data, offset);
    offset += this->cipherSuite.size();
    
    this->compressionMethod = CompressionMethod(data, offset);
    offset += this->compressionMethod.size();
    
    if (offset != data.size()){
        this->haveExtension = true;
        uint16_t nExtensions = Util::takeData16(data, offset);
        offset += 2;
        
        while (nExtensions --){
            this->extensions.push_back(Extension(data, offset));
            offset += this->extensions[this->extensions.size() - 1].size();
        }
    }else{
        this->haveExtension = false;
    }
}

size_t ServerHello::size(){
    size_t result(0);
    return result;
}