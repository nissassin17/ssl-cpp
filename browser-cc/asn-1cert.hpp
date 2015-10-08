//
//  asn-1cert.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef asn_1cert_hpp
#define asn_1cert_hpp

#include <stdio.h>
#include "util.hpp"

class ASN1Cert {
public:
	ASN1Cert(vector<uint8_t> &vector, size_t offset = 0);
	size_t size();
	vector<uint8_t> toData();

private:
	vector<uint8_t> data;
};

#endif /* asn_1cert_hpp */
