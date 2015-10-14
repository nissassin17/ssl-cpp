//
//  encrypted-pre-master-secret.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "EncryptedPreMasterSecret.hpp"
#include "PreMasterSecret.hpp"
#include "Util.hpp"

vector<uint8_t> EncryptedPreMasterSecret::toData() const{
	//return encrypted type as public-key-encrypted
	vector<uint8_t> encryptedData, data;

	//default with https://google.com
//TLS_RSA_WITH_AES_128_CBC_SHA256

	Util::addData(data, (uint16_t) encryptedData.size());
	return data;
}
