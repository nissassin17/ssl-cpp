//
//  SslWrapper.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "SslWrapper.hpp"

SslWrapper::SslWrapper(Url url){
    this->url = new Url(url);
    this->connection = new Connection(url.getHostname());
}

vector<uint8_t> SslWrapper::get(){
    if (this->url->getIsSsl()){
        return vector<uint8_t>();
    }
    this->connection->send(this->url->httpGetRequest());
    return this->connection->receive();
}

SslWrapper::~SslWrapper(){
    delete this->url;
    delete this->connection;
}