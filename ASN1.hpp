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
		VISIBLE_STRING,
		ISO646String = 0x1a,
		GENERAL_STRING = 0x1b,
		UNIVERSAL_STRING = 0x1c,
		CHARACTER_STRING = 0x1d,
		BMP_STRING = 0x1e
	};

	enum TagClass {
		UNIVERSAL = 0b00,
		APPLICATION = 0b01,
		CONTEXT_SPECIFIC = 0b10,
		PRIVATE = 0b11
	};
	typedef vector<uint8_t> IntType;
	typedef bool BoolType;
	typedef set<shared_ptr<ASN1> > SetType;
	typedef vector<long long> ObjectIdentifierType;
//	typedef vector<bool> BitStringType;
	typedef vector<uint8_t> BitStringType;
	typedef vector<uint8_t> OctetStringType;
	typedef vector<shared_ptr<ASN1> > SequenceType;
	typedef OctetStringType TimeType;

	ASN1(const vector<uint8_t> &data, size_t offset = 0);

	virtual vector<uint8_t> toData();
	virtual size_t size();
	const BitStringType& getBitStringVal() const;
	BoolType isBoolVal() const;
	bool isDefinitive() const;
	IntType getIntVal() const;
	const ObjectIdentifierType& getObjectIdentifierVal() const;
	const OctetStringType& getOctetStringVal() const;
	bool isPrimitive() const;
	size_t getPsize() const;
	const SequenceType& getSequenceVal() const;
	const SetType& getSetVal() const;

private:
	TypeTag typeTag;
	TagClass tagClass;
	bool primitive;
	bool definitive;
	long long tagNumber;

	vector<uint8_t> content;
	size_t psize;

	BoolType boolVal;
	IntType intVal;
	SequenceType sequenceVal;
	SetType setVal;
	ObjectIdentifierType objectIdentifierVal;
	BitStringType bitStringVal;
	OctetStringType octetStringVal;
	shared_ptr<ASN1> wrappedData;

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
