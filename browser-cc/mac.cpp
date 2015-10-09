//
//  mac.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "mac.hpp"

int MAC::getMacLength() const{
	return macLength;
}
int MAC::getMacKeyLength() const{
	return macKeyLength;
}
;
MAC::Algorithm MAC::getAlgorithm() const{
	return algorithm;
}

MAC::MAC(MACType type) {
	setType(type);

}

void MAC::setType(MACType type) {
	this->type = type;
	switch (type) {
	case MAC_NULL:
		algorithm = ALGORITHM_NONE;
		macLength = 0;
		macKeyLength = 0;
		break;
	case MD5:
		algorithm = HMAC_MD5;
		macLength = 16;
		macKeyLength = 16;
		break;
	case SHA:
		algorithm = HMAC_SHA1;
		macKeyLength = 20;
		macLength = 20;
		break;
	case SHA256:
		algorithm = HMAC_SHA256;
		macLength = 32;
		macKeyLength = 32;
		break;

	default:
		break;
	}
}
