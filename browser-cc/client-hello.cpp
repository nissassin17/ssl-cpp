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
    this->compressionMethods.push_back(Null);
}

vector<uint8_t> ClientHello::toData(){
    vector<uint8_t> data;
    vector<uint8_t> element;
    
    element = this->protocolVersion.toData();
    data.insert(data.end(), element.begin(), element.end());
    
    element = this->random.toData();
    data.insert(data.end(), element.begin(), element.end());
    
    Util::addData(data, (uint16_t)this->cipherSuites.size());
    for(int i = 0; i < this->cipherSuites.size(); i++){
        element = this->cipherSuites[i].toData();
        data.insert(data.end(), element.begin(), element.end());
    }
    
    data.push_back((uint8_t)this->compressionMethods.size());
    for(int i = 0; i < this->compressionMethods.size(); i++)
        data.push_back(this->compressionMethods[i]);
    
    
    
    if (this->haveExtension){
        //get length
        uint16_t length = 0;
        for(int i = 0; i < this->extensions.size(); i++){
            length += this->extensions[i].dataLength();
        }
        Util::addData(data, (uint16_t)length);
        for(int i = 0; i < this->extensions.size(); i++){
            element = this->extensions[i].toData();
            data.insert(data.end(), element.begin(), element.end());
        }
    }else{
        data.push_back((uint8_t)0);
    }
    
    return data;
}