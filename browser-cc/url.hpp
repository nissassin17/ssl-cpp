//
//  url.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef url_hpp
#define url_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class Url {
public:
	Url(string link);
	string getHostname();
	string getRequest();
	bool getIsSsl();
	vector<uint8_t> httpGetRequest();
private:
	string hostname, request;
	bool isSsl;
};

#endif /* url_hpp */
