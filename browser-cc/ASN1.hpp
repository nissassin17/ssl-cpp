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
		INTEGER = 0x02,
		BIT_STRING = 0x03,
		OCTET_STRING = 0x04,
		ASN1_NULL = 0x05,
		OBJECT_IDENTIFIER = 0x06,
		SEQUENCE = 0x10,
		SET = 0x11,
		PRINTABLE_STRING = 0x13,
		T61_STRING = 0x14,
		IA5_STRING = 0x16,
		UTCTIME = 0x17,
		BOOLEAN,
		REAL,
		ENUMERATE
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
