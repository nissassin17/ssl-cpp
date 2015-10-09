//
//  asn-1cert.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef asn_1cert_hpp
#define asn_1cert_hpp


#include <cstdint>
#include <vector>

#include "Exportable.hpp"

using namespace std;
class ASN1Cert : Exportable {
public:
	ASN1Cert(const vector<uint8_t> &vector, size_t offset = 0);
	virtual size_t size() const;
	virtual vector<uint8_t> toData() const;

private:
	vector<uint8_t> data;
};

#endif /* asn_1cert_hpp */
