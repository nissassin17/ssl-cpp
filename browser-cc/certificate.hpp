//
//  certificate.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef certificate_hpp
#define certificate_hpp

#include <stdio.h>
#include "util.hpp"
#include "asn-1cert.hpp"
#include "exportable.hpp"

class Certificate  : public Exportable{
public:
    Certificate(vector<uint8_t> data, size_t offset = 0);
    size_t size();//uint24_t
private:
    vector<ASN1Cert> certificateList;
};
#endif /* certificate_hpp */
