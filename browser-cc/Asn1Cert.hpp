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
#include "ASN1.hpp"
#include "Asn1TBSCertificate.h"
#include "Asn1AlgorithmIdentifier.h"

using namespace std;
using namespace asn1;
class Asn1Cert : Exportable {
public:
	Asn1Cert(const vector<uint8_t> &vector, size_t offset = 0);
	virtual size_t size() const;
	virtual vector<uint8_t> toData() const;
	int getExponent() const;
	const vector<uint8_t>& getRSAModulus() const;
	~Asn1Cert();

private:
	vector<uint8_t> data;
	Asn1TBSCertificate *tbsCertificate;
	Asn1AlgorithmIdentifier *signatureAlgorithm;
	ASN1::BitStringType signatureValue;
};

#endif /* asn_1cert_hpp */
