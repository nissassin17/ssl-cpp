//
//  certificate.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef certificate_hpp
#define certificate_hpp

#include <cstdint>
#include <vector>

#include "ASN1cert.hpp"
#include "Exportable.hpp"

class Certificate: public Exportable {
public:
	Certificate(const vector<uint8_t> &data, size_t offset = 0);
	virtual size_t size() const; //uint24_t
	const vector<shared_ptr<rsa::Asn1Cert> >& getCertificateList() const;

private:
	vector<shared_ptr<rsa::Asn1Cert> > certificateList;
};
#endif /* certificate_hpp */
