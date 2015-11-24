//
//  certificate-request.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef certificate_request_hpp
#define certificate_request_hpp


#include <cstdint>
#include <vector>

#include "Exportable.hpp"

class CertificateRequest: public Exportable {
public:
	CertificateRequest(const vector<uint8_t> &data, size_t offset = 0);
	virtual size_t size() const;
private:
//    vector<uint8_t>
//    
//    ClientCertificateType certificate_types<1..2^8-1>;
//    DistinguishedName certificate_authorities<0..2^16-1>;
//    
//    
//    ClientCertificateType certificate_types<1..2^8-1>;
//    SignatureAndHashAlgorithm
//    supported_signature_algorithms<2^16-1>;
//    DistinguishedName certificate_authorities<0..2^16-1>;
};

#endif /* certificate_request_hpp */
