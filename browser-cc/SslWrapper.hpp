//
//  SslWrapper.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef SslWrapper_hpp
#define SslWrapper_hpp

#include <cstdint>
#include <vector>

#include "Url.hpp"

class Connection;

using namespace std;

class SslWrapper {
private:
	const Url * const url;
	Connection *connection;
public:
	SslWrapper(const Url* const url);
	vector<uint8_t> get();
	virtual ~SslWrapper();
//    vector<uint8_t> post();
};

#endif /* SslWrapper_hpp */
