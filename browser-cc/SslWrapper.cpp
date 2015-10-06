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
        //prepare client hello
        Record *clientHello = new Record();
        
        vector<uint8_t> tosend(clientHello->toData());
        this->connection->send(tosend);
        cout << "Request:" << endl << Util::readableForm(tosend) << endl;
        
        vector<uint8_t> data = this->connection->receive();
        cout << "Response:" << endl << Util::readableForm(data) << endl;//this is server hello message
        
        //this must be a server hello handshake record
        size_t offset(0);
        Record *serverHello = new Record(data, offset);
        offset += serverHello->size();
        
        //certificate
        Record *certificate = new Record(data, offset);
        offset += certificate->size();
        
        //server key exchange
        Record *serverKeyExchange = new Record(data, offset, serverHello->getFragment());
        offset += serverKeyExchange->size();
        
        //server hello done
        Record *serverHelloDone = new Record(data, offset);
        
        delete clientHello;
        delete serverHello;
        delete certificate;
        delete serverKeyExchange;
        delete serverHelloDone;
        
        //prepare finished message
//        Record finished(data.)

        return vector<uint8_t>();
    }
    this->connection->send(this->url->httpGetRequest());
    return this->connection->receive();
}

SslWrapper::~SslWrapper(){
    delete this->url;
    delete this->connection;
}