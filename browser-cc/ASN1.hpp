/*
 * ASN1.h
 *
 *  Created on: Oct 9, 2015
 *      Author: nissassin17
 */

#ifndef ASN1_HPP_
#define ASN1_HPP_

#include "Exportable.hpp"
#include <set>

class ASN1: public Exportable {
public:
    enum TypeTag {
        RESERVED = 0x0,
        BOOLEAN = 0x1,
        INTEGER = 0x02,
        BIT_STRING = 0x03,
        OCTET_STRING = 0x04,
        ASN1_NULL = 0x05,
        OBJECT_IDENTIFIER = 0x06,
        OBJECT_DESCRIPTOR = 0x07,
        EXTERNAL = 0x8, //OR instance of
        REAL = 0x9,
        ENUMERATED = 0xA,
        EMBEDDED_PDV = 0xB,
        UTF8_STRING = 0xC,
        RELATIVE_OID = 0xD,
        //lack 0xe
        //lack 0xf
        SEQUENCE = 0x10,
        SET = 0x11, //or SET OF
        NUMERIC_STRING = 0x12,
        PRINTABLE_STRING = 0x13,
        TELETEX_STRING = 0x14, //OR T61String
        VIDEOTEX_STRINg = 0x15,
        IA5_STRING = 0x16,
        UTC_TIME = 0x17,
        GENERALIZED_TIME = 0x18,
        GRAPHIC_STRING = 0x19,
        VISIBLE_STRING, ISO646String = 0x1a,
        GENERAL_STRING = 0x1b,
        UNIVERSAL_STRING = 0x1c,
        CHARACTER_STRING = 0x1d,
        BMP_STRING = 0x1e
    };
    
    enum TagClass{
        UNIVERSAL = 0x00,
        APPLICATION = 0x01,
        CONTEXT_SPECIFIC = 0x10,
        PRIVATE = 0x11
    };
    
    ASN1(const vector<uint8_t> &data, size_t offset = 0);
    
    virtual vector<uint8_t> toData();
    virtual size_t size();
    virtual ~ASN1();
    
private:
    TypeTag typeTag;
    TagClass tagClass;
    bool primitive;
    bool definitive;
    long long tagNumber;
    
    vector<uint8_t> content;
    size_t psize;
    
    bool boolVal;
    long long intVal;
    vector<ASN1*> sequenceVal;
    set<ASN1*> setVal;
    vector<long long> objectIdentifierVal;
    vector<bool> bitStringVal;
    vector<uint8_t> octetStringVal;
    
    void parseTagNumber(const vector<uint8_t>& data, size_t& offset);
    long long parseContentLength(const vector<uint8_t>& data, size_t& offset);
    void parseContent(const vector<uint8_t>& data, size_t& offset,
                      long long contentLength);
    void parseBoolContent(const vector<uint8_t>& data, size_t& offset);
    void parserIntegerContent(const vector<uint8_t>& data, size_t& offset,
                              long long contentLength);
    void parseRealContent(const vector<uint8_t>& data, size_t& offset,
                          long long contentLength);
    void parseSequence(const vector<uint8_t>& data, size_t& offset,
                       long long contentLength);
    void parseSet(const vector<uint8_t>& data, size_t& offset,
                  long long contentLength);
    void parseObjectIdentifier(const vector<uint8_t>& data, size_t& offset,
                               long long contentLength);
    void parseBitString(const vector<uint8_t>& data, size_t& offset,
                        long long contentLength);
    void parseOctetString(const vector<uint8_t>& data, size_t& offset,
                          long long contentLength);
};

#endif /* ASN1_HPP_ */
