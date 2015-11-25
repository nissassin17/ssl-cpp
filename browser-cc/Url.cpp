//
//  url.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//


#include <algorithm>
#include <cctype>
#include <iterator>
#include <string>
#include <iostream>
using namespace std;

#include "Url.hpp"
#include "Err.hpp"
#include "Log.h"

vector<uint8_t> Url::httpGetRequest() const {
	string fullRequest(
			"GET " + this->request + " HTTP/1.1\r\nHost: " + this->hostname
					+ "\r\nConnection: keep-alive\r\nPragma: no-cache\r\nCache-Control: no-cache\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n\r\n");
	vector<uint8_t> result;
	for (int i = 0; i < fullRequest.length(); i++)
		result.push_back((uint8_t) fullRequest[i]);
	Log::info << "Full http request to be sent:" << endl;
	Log::info << fullRequest << endl;
	return result;
}

Url::Url(const string& link) {
	const string HTTP("HTTP://");
	const string HTTPS("HTTPS://");

	//detect ssl
	string schema = link.substr(0, HTTPS.length());
	//toupper
	transform(schema.begin(), schema.end(), schema.begin(), ::toupper);
	if (schema == HTTPS)
		this->useSsl = true;
	else {
		this->useSsl = false;
		schema = link.substr(0, HTTP.length());
		transform(schema.begin(), schema.end(), schema.begin(), ::toupper);
		if (schema != HTTP)
			throw Err(Err::UnsupportedSchema);
	}

	//get hostname
	size_t hostStart = this->useSsl ? HTTPS.length() : HTTP.length();
	size_t found = link.find('/', hostStart);
	if (found == string::npos) {
		this->request = "/";
		this->hostname = link.substr(hostStart);
	} else {
		this->hostname = link.substr(hostStart, found - hostStart);
		this->request = link.substr(found);
	}

	if (this->hostname == "")
		throw Err(Err::NoHostnameProvided);

}

const string &Url::getHostname() const {
	return this->hostname;
}

const string &Url::getRequest() const{
	return this->request;
}

bool Url::isUseSsl() const {
	return useSsl;
}
