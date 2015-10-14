//
//  url.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef url_hpp
#define url_hpp

#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Url {
public:
	Url(const string& link);
	const string &getHostname() const;
	const string &getRequest() const;

	vector<uint8_t> httpGetRequest() const;
	bool isUseSsl() const;

private:
	string hostname, request;
	bool useSsl;
};

#endif /* url_hpp */
