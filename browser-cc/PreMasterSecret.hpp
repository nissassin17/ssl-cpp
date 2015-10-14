//
//  pre-master-secret.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef pre_master_secret_hpp
#define pre_master_secret_hpp

#include <stdio.h>

#include <cstdint>
#include <vector>

#include "Exportable.hpp"

class ProtocolVersion;

class PreMasterSecret: public Exportable {
public:
	PreMasterSecret() :
			clientVersion(new ProtocolVersion()) {
		time_t t;
		srand((unsigned int) (time(&t)));
		for (int i = 0; i < RANDOM_LENGTH; i++)
			random[i] = (uint8_t) (rand());
	}
	~PreMasterSecret() {
		delete clientVersion;
	}
	virtual vector<uint8_t> toData()const;
	virtual size_t size() const;
private:
	static const int RANDOM_LENGTH = 46;
	ProtocolVersion *clientVersion;
	uint8_t random[RANDOM_LENGTH];
};
#endif /* pre_master_secret_hpp */
