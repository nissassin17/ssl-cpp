//
//  pre-master-secret.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "pre-master-secret.hpp"

#include <sys/_types/_time_t.h>
#include <cstdlib>
#include <ctime>

#include "protocol-version.hpp"
#include "util.hpp"

PreMasterSecret::PreMasterSecret() :
		clientVersion(new ProtocolVersion()) {
	time_t t;
	srand((unsigned int) time(&t));
	for (int i = 0; i < RANDOM_LENGTH; i++)
		random[i] = (uint8_t) rand();
}
PreMasterSecret::~PreMasterSecret() {
	delete clientVersion;
}

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
