//
//  server-dh-params.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef server_dh_params_hpp
#define server_dh_params_hpp

#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>
#include "exportable.hpp"
using namespace std;

class ServerDHParams : Exportable{
public:
	ServerDHParams(const vector<uint8_t> &data, size_t offset = 0);
	virtual size_t size() const;

private:
	vector<uint8_t> dhP; //1->2^16 - 1
	vector<uint8_t> dhG;
	vector<uint8_t> dhYs;
};

#endif /* server_dh_params_hpp */
