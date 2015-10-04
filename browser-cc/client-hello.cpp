//
//  client-hello.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "client-hello.hpp"
#include "util.hpp"

ClientHello::ClientHello(): random(), sessionID(), haveExtension(false){
    this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_NULL_WITH_NULL_NULL));
    this->cipherSuites.push_back(CipherSuite(CipherSuite::TLS_RSA_WITH_NULL_MD5));
    this->compressionMethods.push_back(CompressionMethod(CompressionMethod::Null));
}

size_t ClientHello::size(){
    size_t result(0);
    
    result += this->protocolVersion.size()
    + this->random.size()
    + 2;
    
    for(int i = 0; i < this->cipherSuites.size(); i++)
        result += this->cipherSuites[i].size();
    
    result += 1;
    for(int i = 0; i < this->compressionMethods.size(); i++)
        result += this->compressionMethods[i].size();
    
    if (this->haveExtension){
        result += 2;
        for(int i = 0; i < this->extensions.size(); i++)
            result += this->extensions[i].size();
    }else{
        result ++;
    }
    return result;
}

vector<uint8_t> ClientHello::toData(){
    vector<uint8_t> data;
    
    Util::addData(data, this->protocolVersion.toData());
    
    Util::addData(data, this->random.toData());
    
    Util::addData(data, (uint16_t)this->cipherSuites.size());
    for(int i = 0; i < this->cipherSuites.size(); i++)
        Util::addData(data, this->cipherSuites[i].toData());
    
    data.push_back((uint8_t)this->compressionMethods.size());
    for(int i = 0; i < this->compressionMethods.size(); i++)
        Util::addData(data, this->compressionMethods[i].toData());
    
    
    
    if (this->haveExtension){
        //get length
        uint16_t length = 0;
        for(int i = 0; i < this->extensions.size(); i++){
            length += this->extensions[i].size();
        }
        Util::addData(data, (uint16_t)length);
        for(int i = 0; i < this->extensions.size(); i++)
            Util::addData(data, this->extensions[i].toData());
    }else{
        data.push_back((uint8_t)0);
    }
    
    return data;
}