//
//  pre-master-secret.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//


#include <stddef.h>
#include <cstdlib>
#include <ctime>

#include "PreMasterSecret.hpp"
#include "ProcotolVersion.hpp"
#include "Util.hpp"

size_t PreMasterSecret::size() const{
	return clientVersion->size() + RANDOM_LENGTH;
}

vector<uint8_t> PreMasterSecret::toData() const{
	vector<uint8_t> data;
	Util::addData(data, clientVersion->toData());
	for (int i = 0; i < RANDOM_LENGTH; i++)
		data.push_back(random[i]);
	return data;
}
