//
//  url.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "url.hpp"
#include <algorithm>
#include "err.hpp"

vector<uint8_t> Url::httpGetRequest(){
    string fullRequest("GET " + this->request +" HTTP/1.1\r\nHost: " + this->hostname + "\r\nConnection: keep-alive\r\nPragma: no-cache\r\nCache-Control: no-cache\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n\r\n");
    vector<uint8_t> result;
    for(int i = 0; i < fullRequest.length(); i++)
        result.push_back((uint8_t)fullRequest[i]);
    return result;
}

Url::Url(string link){
    const string HTTP("HTTP://");
    const string HTTPS("HTTPS://");
    
    //detect ssl
    string schema = link.substr(0, HTTPS.length());
    //toupper
    transform(schema.begin(), schema.end(), schema.begin(), ::toupper);
    if (schema == HTTPS)
        this->isSsl = true;
    else{
        this->isSsl = false;
        schema = link.substr(0, HTTP.length());
        transform(schema.begin(), schema.end(), schema.begin(), ::toupper);
        if (schema != HTTP)
            throw Err(Err::UnsupportedSchema);
    }
    
    //get hostname
    size_t hostStart = this->isSsl ? HTTPS.length() : HTTP.length();
    size_t found = link.find('/', hostStart);
    this->hostname = link.substr(hostStart, found);
    
    if (this->hostname == "")
        throw Err(Err::NoHostnameProvided);
    
    if (found == string::npos)//there is no / after schema
        this->request = "/";
    else
        this->request = link.substr(hostStart + this->hostname.length());
}

string Url::getHostname(){
    return this->hostname;
}

string Url::getRequest(){
    return this->request;
}

bool Url::getIsSsl(){
    return this->isSsl;
}