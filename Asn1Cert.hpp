//
//  asn-1cert.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef asn_1cert_hpp
#define asn_1cert_hpp

#include <cstdint>
#include <vector>

#include "Exportable.hpp"
#include "ASN1.hpp"
#include "Asn1TBSCertificate.h"
#include "Asn1AlgorithmIdentifier.h"
#include "RSAPublicKey.h"

using namespace std;
using namespace asn1;
namespace rsa {
class Asn1Cert: Exportable {
public:
	Asn1Cert(const vector<uint8_t> &vector, size_t offset = 0);
	virtual size_t size() const;
	virtual vector<uint8_t> toData() const;
	const shared_ptr<RSAPublicKey>& getRsaPublicKey() const;

private:
	vector<uint8_t> data;
	shared_ptr<Asn1TBSCertificate> tbsCertificate;
	shared_ptr<Asn1AlgorithmIdentifier> signatureAlgorithm;
	ASN1::BitStringType signatureValue;
	shared_ptr<RSAPublicKey> rsaPublicKey;
};
}

#endif /* asn_1cert_hpp */
