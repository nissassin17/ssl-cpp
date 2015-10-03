//
//  SslWrapper.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "SslWrapper.hpp"
#include "record.hpp"
#include "util.hpp"

SslWrapper::SslWrapper(Url url){
    this->url = new Url(url);
    this->connection = new Connection(url.getHostname(), url.getIsSsl());
}

vector<uint8_t> SslWrapper::get(){
    if (this->url->getIsSsl()){
        Record record;
        
        vector<uint8_t> tosend(record.toData());
        this->connection->send(tosend);
        cout << "Request:" << endl << Util::readableForm(tosend) << endl;
        
        vector<uint8_t> data = this->connection->receive();
        cout << "Response:" << endl << Util::readableForm(data) << endl;

        return vector<uint8_t>();
    }
    this->connection->send(this->url->httpGetRequest());
    return this->connection->receive();
}

SslWrapper::~SslWrapper(){
    delete this->url;
    delete this->connection;
}