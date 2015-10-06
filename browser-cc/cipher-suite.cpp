//
//  cipher-suite.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "cipher-suite.hpp"
#include "util.hpp"

CipherSuite::CipherSuite(CipherSuiteType type) : suite(type){
    
}

vector<uint8_t> CipherSuite::toData(){
    uint8_t high(this->suite >> 8);
    uint8_t low(this->suite & ((1 << 8) - 1));
    return vector<uint8_t>({high, low});
}

size_t CipherSuite::size(){
    return 2;
}

CipherSuite::CipherSuite(vector<uint8_t> &data, size_t offset){
    this->suite = (CipherSuiteType)Util::takeData16(data, offset);
}

CipherSuite::EncryptType CipherSuite::encryptType(){
    switch (this->suite){
        case TLS_RSA_WITH_NULL_MD5                 :
            return RSA;
        case TLS_RSA_WITH_NULL_SHA                 :
            return RSA;
        case TLS_RSA_WITH_NULL_SHA256              :
            return RSA;
        case TLS_RSA_WITH_RC4_128_MD5              :
            return RSA;
        case TLS_RSA_WITH_RC4_128_SHA              :
            return RSA;
        case TLS_RSA_WITH_3DES_EDE_CBC_SHA         :
            return RSA;
        case TLS_RSA_WITH_AES_128_CBC_SHA          :
            return RSA;
        case TLS_RSA_WITH_AES_256_CBC_SHA          :
            return RSA;
        case TLS_RSA_WITH_AES_128_CBC_SHA256       :
            return RSA;
        case TLS_RSA_WITH_AES_256_CBC_SHA256       :
            return RSA;
        case TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA      :
            return DH_DSS;
        case TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA      :
            return DH_RSA;
        case TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA     :
            return DHE_DSS;
        case TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA     :
            return DHE_RSA;
        case TLS_DH_DSS_WITH_AES_128_CBC_SHA       :
            return DH_DSS;
        case TLS_DH_RSA_WITH_AES_128_CBC_SHA       :
            return DH_RSA;
        case TLS_DHE_DSS_WITH_AES_128_CBC_SHA      :
            return DHE_DSS;
        case TLS_DHE_RSA_WITH_AES_128_CBC_SHA      :
            return DHE_RSA;
        case TLS_DH_DSS_WITH_AES_256_CBC_SHA       :
            return DH_DSS;
        case TLS_DH_RSA_WITH_AES_256_CBC_SHA       :
            return DH_RSA;
        case TLS_DHE_DSS_WITH_AES_256_CBC_SHA      :
            return DHE_DSS;
        case TLS_DHE_RSA_WITH_AES_256_CBC_SHA      :
            return DHE_RSA;
        case TLS_DH_DSS_WITH_AES_128_CBC_SHA256    :
            return DH_DSS;
        case TLS_DH_RSA_WITH_AES_128_CBC_SHA256    :
            return DH_RSA;
        case TLS_DHE_DSS_WITH_AES_128_CBC_SHA256   :
            return DHE_DSS;
        case TLS_DHE_RSA_WITH_AES_128_CBC_SHA256   :
            return DHE_RSA;
        case TLS_DH_DSS_WITH_AES_256_CBC_SHA256    :
            return DH_DSS;
        case TLS_DH_RSA_WITH_AES_256_CBC_SHA256    :
            return DH_RSA;
        case TLS_DHE_DSS_WITH_AES_256_CBC_SHA256   :
            return DHE_DSS;
        case TLS_DHE_RSA_WITH_AES_256_CBC_SHA256   :
            return DHE_RSA;
        case TLS_DH_anon_WITH_RC4_128_MD5          :
            return DH_ANON;
        case TLS_DH_anon_WITH_3DES_EDE_CBC_SHA     :
            return DH_ANON;
        case TLS_DH_anon_WITH_AES_128_CBC_SHA      :
            return DH_ANON;
        case TLS_DH_anon_WITH_AES_256_CBC_SHA      :
            return DH_ANON;
        case TLS_DH_anon_WITH_AES_128_CBC_SHA256   :
            return DH_ANON;
        case TLS_DH_anon_WITH_AES_256_CBC_SHA256   :
            return DH_ANON;
        default:
            return ENCRYPT_NULL;
    }
}

CipherSuite::HashType CipherSuite::hashType(){
    switch (this->suite){
        case TLS_RSA_WITH_NULL_MD5                 :
            return NULL_MD5                 ;
        case TLS_RSA_WITH_NULL_SHA                 :
            return NULL_SHA                 ;
        case TLS_RSA_WITH_NULL_SHA256              :
            return NULL_SHA256              ;
        case TLS_RSA_WITH_RC4_128_MD5              :
            return RC4_128_MD5              ;
        case TLS_RSA_WITH_RC4_128_SHA              :
            return RC4_128_SHA              ;
        case TLS_RSA_WITH_3DES_EDE_CBC_SHA         :
            return _3DES_EDE_CBC_SHA         ;
        case TLS_RSA_WITH_AES_128_CBC_SHA          :
            return AES_128_CBC_SHA          ;
        case TLS_RSA_WITH_AES_256_CBC_SHA          :
            return AES_256_CBC_SHA          ;
        case TLS_RSA_WITH_AES_128_CBC_SHA256       :
            return AES_128_CBC_SHA256       ;
        case TLS_RSA_WITH_AES_256_CBC_SHA256       :
            return AES_256_CBC_SHA256       ;
        case TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA      :
            return _3DES_EDE_CBC_SHA      ;
        case TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA      :
            return _3DES_EDE_CBC_SHA      ;
        case TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA     :
            return _3DES_EDE_CBC_SHA     ;
        case TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA     :
            return _3DES_EDE_CBC_SHA     ;
        case TLS_DH_DSS_WITH_AES_128_CBC_SHA       :
            return AES_128_CBC_SHA       ;
        case TLS_DH_RSA_WITH_AES_128_CBC_SHA       :
            return AES_128_CBC_SHA       ;
        case TLS_DHE_DSS_WITH_AES_128_CBC_SHA      :
            return AES_128_CBC_SHA      ;
        case TLS_DHE_RSA_WITH_AES_128_CBC_SHA      :
            return AES_128_CBC_SHA      ;
        case TLS_DH_DSS_WITH_AES_256_CBC_SHA       :
            return AES_256_CBC_SHA       ;
        case TLS_DH_RSA_WITH_AES_256_CBC_SHA       :
            return AES_256_CBC_SHA       ;
        case TLS_DHE_DSS_WITH_AES_256_CBC_SHA      :
            return AES_256_CBC_SHA      ;
        case TLS_DHE_RSA_WITH_AES_256_CBC_SHA      :
            return AES_256_CBC_SHA      ;
        case TLS_DH_DSS_WITH_AES_128_CBC_SHA256    :
            return AES_128_CBC_SHA256    ;
        case TLS_DH_RSA_WITH_AES_128_CBC_SHA256    :
            return AES_128_CBC_SHA256    ;
        case TLS_DHE_DSS_WITH_AES_128_CBC_SHA256   :
            return AES_128_CBC_SHA256   ;
        case TLS_DHE_RSA_WITH_AES_128_CBC_SHA256   :
            return AES_128_CBC_SHA256   ;
        case TLS_DH_DSS_WITH_AES_256_CBC_SHA256    :
            return AES_256_CBC_SHA256    ;
        case TLS_DH_RSA_WITH_AES_256_CBC_SHA256    :
            return AES_256_CBC_SHA256    ;
        case TLS_DHE_DSS_WITH_AES_256_CBC_SHA256   :
            return AES_256_CBC_SHA256   ;
        case TLS_DHE_RSA_WITH_AES_256_CBC_SHA256   :
            return AES_256_CBC_SHA256   ;
        case TLS_DH_anon_WITH_RC4_128_MD5          :
            return RC4_128_MD5          ;
        case TLS_DH_anon_WITH_3DES_EDE_CBC_SHA     :
            return _3DES_EDE_CBC_SHA     ;
        case TLS_DH_anon_WITH_AES_128_CBC_SHA      :
            return AES_128_CBC_SHA      ;
        case TLS_DH_anon_WITH_AES_256_CBC_SHA      :
            return AES_256_CBC_SHA      ;
        case TLS_DH_anon_WITH_AES_128_CBC_SHA256   :
            return AES_128_CBC_SHA256   ;
        case TLS_DH_anon_WITH_AES_256_CBC_SHA256   :
            return AES_256_CBC_SHA256   ;
        default:
            return NULL_NULL;
            
    }
}
