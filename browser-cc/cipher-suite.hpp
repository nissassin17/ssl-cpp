//
//  cipher-suite.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef cipher_suite_hpp
#define cipher_suite_hpp

#include <stdio.h>
#include "exportable.hpp"
class CipherSuite{
public:
    CipherSuite(uint16_t suite);
    vector<uint8_t> toData();
    static const uint16_t TLS_NULL_WITH_NULL_NULL               = 0x0000;
    static const uint16_t TLS_RSA_WITH_NULL_MD5                 = 0x0001;
    static const uint16_t TLS_RSA_WITH_NULL_SHA                 = 0x0002;
    static const uint16_t TLS_RSA_WITH_NULL_SHA256              = 0x003B;
    static const uint16_t TLS_RSA_WITH_RC4_128_MD5              = 0x0004;
    static const uint16_t TLS_RSA_WITH_RC4_128_SHA              = 0x0005;
    static const uint16_t TLS_RSA_WITH_3DES_EDE_CBC_SHA         = 0x000A;
    static const uint16_t TLS_RSA_WITH_AES_128_CBC_SHA          = 0x002F;
    static const uint16_t TLS_RSA_WITH_AES_256_CBC_SHA          = 0x0035;
    static const uint16_t TLS_RSA_WITH_AES_128_CBC_SHA256       = 0x003C;
    static const uint16_t TLS_RSA_WITH_AES_256_CBC_SHA256       = 0x003D;
    static const uint16_t TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA      = 0x000D;
    static const uint16_t TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA      = 0x0010;
    static const uint16_t TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA     = 0x0013;
    static const uint16_t TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA     = 0x0016;
    static const uint16_t TLS_DH_DSS_WITH_AES_128_CBC_SHA       = 0x0030;
    static const uint16_t TLS_DH_RSA_WITH_AES_128_CBC_SHA       = 0x0031;
    static const uint16_t TLS_DHE_DSS_WITH_AES_128_CBC_SHA      = 0x0032;
    static const uint16_t TLS_DHE_RSA_WITH_AES_128_CBC_SHA      = 0x0033;
    static const uint16_t TLS_DH_DSS_WITH_AES_256_CBC_SHA       = 0x0036;
    static const uint16_t TLS_DH_RSA_WITH_AES_256_CBC_SHA       = 0x0037;
    static const uint16_t TLS_DHE_DSS_WITH_AES_256_CBC_SHA      = 0x0038;
    static const uint16_t TLS_DHE_RSA_WITH_AES_256_CBC_SHA      = 0x0039;
    static const uint16_t TLS_DH_DSS_WITH_AES_128_CBC_SHA256    = 0x003E;
    static const uint16_t TLS_DH_RSA_WITH_AES_128_CBC_SHA256    = 0x003F;
    static const uint16_t TLS_DHE_DSS_WITH_AES_128_CBC_SHA256   = 0x0040;
    static const uint16_t TLS_DHE_RSA_WITH_AES_128_CBC_SHA256   = 0x0067;
    static const uint16_t TLS_DH_DSS_WITH_AES_256_CBC_SHA256    = 0x0068;
    static const uint16_t TLS_DH_RSA_WITH_AES_256_CBC_SHA256    = 0x0069;
    static const uint16_t TLS_DHE_DSS_WITH_AES_256_CBC_SHA256   = 0x006A;
    static const uint16_t TLS_DHE_RSA_WITH_AES_256_CBC_SHA256   = 0x006B;
    static const uint16_t TLS_DH_anon_WITH_RC4_128_MD5          = 0x0018;
    static const uint16_t TLS_DH_anon_WITH_3DES_EDE_CBC_SHA     = 0x001B;
    static const uint16_t TLS_DH_anon_WITH_AES_128_CBC_SHA      = 0x0034;
    static const uint16_t TLS_DH_anon_WITH_AES_256_CBC_SHA      = 0x003A;
    static const uint16_t TLS_DH_anon_WITH_AES_128_CBC_SHA256   = 0x006C;
    static const uint16_t TLS_DH_anon_WITH_AES_256_CBC_SHA256   = 0x006D;
private:
    uint16_t suite;
};

#endif /* cipher_suite_hpp */
