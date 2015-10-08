//
//  SslWrapper.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef SslWrapper_hpp
#define SslWrapper_hpp

#include <stdio.h>
#include <vector>
#include "url.hpp"
#include "connection.hpp"

using namespace std;

class SslWrapper {
private:
	Url *url;
	Connection *connection;
public:
	SslWrapper(Url url);
	vector<uint8_t> get();
	~SslWrapper();
//    vector<uint8_t> post();
};

#endif /* SslWrapper_hpp */
