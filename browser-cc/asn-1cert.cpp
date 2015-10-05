//
//  asn-1cert.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "asn-1cert.hpp"

ASN1Cert::ASN1Cert(vector<uint8_t> data, size_t offset){
    uint32_t length = Util::takeData24(data, offset);
    offset += 3;
    
    this->data = Util::takeData(data, length, offset);
}

size_t ASN1Cert::size(){
    return 3 + this->data.size();
}