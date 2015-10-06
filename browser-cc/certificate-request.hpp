//
//  certificate-request.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef certificate_request_hpp
#define certificate_request_hpp

#include <stdio.h>
#include "util.hpp"
#include "exportable.hpp"

class CertificateRequest : public Exportable{
public:
    CertificateRequest(vector<uint8_t> data, size_t offset = 0);
    size_t size();
    ~CertificateRequest();
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
