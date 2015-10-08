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
#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>

#include "exportable.hpp"

class ProtocolVersion;

class PreMasterSecret: public Exportable {
public:
	PreMasterSecret();
	~PreMasterSecret();
	vector<uint8_t> toData();
	size_t size();
private:
	static const int RANDOM_LENGTH = 46;
	ProtocolVersion *clientVersion = NULL;
	uint8_t random[RANDOM_LENGTH];
};
#endif /* pre_master_secret_hpp */
