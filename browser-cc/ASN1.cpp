/*
 * ASN1.cpp
 *
 *  Created on: Oct 9, 2015
 *      Author: nissassin17
 */

#include "ASN1.hpp"
#include "BitUtil.hpp"

vector<uint8_t> ASN1::toData() {
	vector<uint8_t> data;
	return data;
}

size_t ASN1::size() {
	return psize;
}

ASN1::~ASN1() {
	for (vector<ASN1*>::iterator it = sequenceVal.begin();
			it != sequenceVal.end(); it++)
		delete *it;
	for (set<ASN1*>::iterator it = setVal.begin(); it != setVal.end(); it++)
		delete *it;
}

void ASN1::parseTagNumber(const vector<uint8_t>& data, size_t& offset) {
	//define tag number
	if (BitUtil::isAllOne(data[offset], 5)) {
		//high tag number
		offset++;
		tagNumber = 0ll;
		while (true) {
			tagNumber = BitUtil::append(tagNumber,
					BitUtil::filter(data[offset], 7), 7);
			if (BitUtil::isBitOff(data[offset], 7))
				break;

			offset++;
		}
		offset++;
	} else {
		//low tag number
		tagNumber = BitUtil::filter(data[offset], 5);
		offset++;
	}
}

long long ASN1::parseContentLength(const vector<uint8_t>& data,
		size_t& offset) {
	//define length
	long long contentLength = 0ll;
	if (BitUtil::isBitOn(data[offset], 7)) {
		//short form definitive
		definitive = true;
		contentLength = data[offset];
		offset++;
	} else {
		//long form: definitive or indefinitive
		if (BitUtil::isAllZero(data[offset], 7)) {
			//definitive
			definitive = false;
			//number of octets for length octet
			int nlengthOctets = BitUtil::filterByte(data[offset]);
			while (offset++, nlengthOctets--) {
				contentLength = BitUtil::append(contentLength, data[offset], 8);
			}
			offset++;
		} else {
			//indefinitive form
			definitive = true;
			contentLength = -1;
			offset++;
		}
	}

	return contentLength;
}

void ASN1::parseBoolContent(const vector<uint8_t>& data, size_t& offset) {
	//primitive
	boolVal = data[offset] == 0;
	offset++;
}

void ASN1::parserIntegerContent(const vector<uint8_t>& data, size_t& offset,
		long long contentLength) {
	//primitive
	intVal = 0ll;
	bool isNegative = BitUtil::isBitOn(data[offset], 7);
	for (int i = 0; i < contentLength; i++) {
		intVal = BitUtil::append(intVal, data[offset], 8);
		offset++;
	}
	if (isNegative) {
		intVal -= (1 << (contentLength - 1));
	}
}

void ASN1::parseRealContent(const vector<uint8_t>& data, size_t& offset,
		long long contentLength) {
	throw logic_error("ASN1 REAL type is unimplemented");
	if (BitUtil::isBitOn(data[offset], 7)) {
		//normal real number
		//get sign bit
		int sign = BitUtil::isBitOn(data[offset], 6);
		//get base
		int BASE;
		switch (BitUtil::filter(data[offset], 2, 4)) {
		case 00:
			BASE = 2;
			break;
		case 01:
			BASE = 8;
			break;
		case 10:
			BASE = 16;
			break;
		default: //11 -> reserved
			break;
		}
		//get scale factor
		int scaleFactor = BitUtil::filter(data[offset], 2, 2);
		//get encoding
		switch (BitUtil::filter(data[offset], 2, 0)) {
		case 00:
			/**
			 *if bits 2 to 1 are 00, then the second contents octet encodes the value of
			 *if  the exponent as a two's
			 *				complement binary number;
			 */
			break;
		case 01:
			/**
			 * if bits 2 to 1 are 01, then the second and third contents octets encode the value of
			 * the exponent as a two's complement binary number;
			 */
			break;
		case 10:
			/**
			 * if bits 2 to 1 are 10, then the second, third and fourth contents octets encode the
			 *  value of the exponent as a two's complement binary number;
			 */
			break;
		default:
			/**
			 * if bits 2 to 1 are 11, then the second contents octet encodes the number of octets,
			 *  X say, (as an unsigned binary number) used to encode the value of the exponent,
			 *  and the third up to the (X plus 3)th (inclusive) contents octets encode the value
			 *  of the exponent as a two's complement binary number; the value of X shall be at least one;
			 *  the first nine bits of the transmitted exponent shall not be all zeros or all ones.
			 */
			break;
		}
		offset++;
		long long intVal = 0;
		for (int i = 1; i < contentLength; i++) {
			intVal = BitUtil::append(intVal, data[offset], 8);
			offset++;
		}
	} else if (BitUtil::isBitOn(data[offset], 6)) {
		//SpecialRealValue
	} else {
	}
}

void ASN1::parseSequence(const vector<uint8_t>& data, size_t& offset,
		long long contentLength) {
	size_t oldOffset(offset);
	while (contentLength + oldOffset < offset) {
		sequenceVal.push_back(new ASN1(data, offset));
		offset += (*sequenceVal.rbegin())->size();
	}
}

void ASN1::parseSet(const vector<uint8_t>& data, size_t& offset,
		long long contentLength) {
	size_t oldOffset(offset);
	while (oldOffset + contentLength < offset) {
		ASN1* val = new ASN1(data, offset);
		setVal.insert(val);
		offset += val->size();
	}
}

void ASN1::parseObjectIdentifier(const vector<uint8_t>& data, size_t& offset,
		long long contentLength) {
	size_t oldOffset(offset);
	while (oldOffset + contentLength < offset) {
		long long subid(0ll);
		while (true) {
			subid = BitUtil::append(subid, data[offset], 7);
			offset++;
			if (BitUtil::isBitOff(data[offset], 7))
				break;
		}
		objectIdentifierVal.push_back(subid);
	}
}

void ASN1::parseBitString(const vector<uint8_t>& data, size_t& offset,
		long long contentLength) {
	int nUnused = data[offset];
	offset++;
	for (int i = 1; i < contentLength; i++) {
		int t;
		if (i == contentLength - 1)
			t = nUnused;
		else
			t = 0;

		for (int j = 0; j < 8 - t; j++)
			bitStringVal.push_back(BitUtil::isBitOn(data[offset], 7 - j));
		offset++;
	}
}

void ASN1::parseOctetString(const vector<uint8_t>& data, size_t& offset,
		long long contentLength) {
	for (int i = 0; i < contentLength; i++) {
		octetStringVal.push_back(data[offset]);
		offset++;
	}
}

void ASN1::parseContent(const vector<uint8_t>& data, size_t& offset,
		long long contentLength) {
	switch (tagNumber) {
	case BOOLEAN:
		//primitive
		parseBoolContent(data, offset);
		break;
	case INTEGER:
	case ENUMERATE:
		//primitive
		parserIntegerContent(data, offset, contentLength);
		break;
	case REAL:
		parseRealContent(data, offset, contentLength);
		break;
	case BIT_STRING:
		parseBitString(data, offset, contentLength);
		break;
	case ASN1_NULL:
		//do nothing
		break;
	case SEQUENCE: //constructed
		parseSequence(data, offset, contentLength);
		break;

	case SET:
		parseSet(data, offset, contentLength);
		break;

	case OBJECT_IDENTIFIER:
		parseObjectIdentifier(data, offset, contentLength);
		break;

	case OCTET_STRING:
		parseOctetString(data, offset, contentLength);
		break;

	case IA5_STRING:
		parseOctetString(data, offset, contentLength);
		break;

	case PRINTABLE_STRING:
		parseOctetString(data, offset, contentLength);
		break;

	case UTCTIME:
		parseOctetString(data, offset, contentLength);
		break;

	default:
		throw logic_error("unimplemented asn1 type");
		break;
	}
}

ASN1::ASN1(const vector<uint8_t> &data, size_t offset) :
		typeTag(ASN1_NULL), tagClass(UNIVERSAL), primitive(false), tagNumber(0), definitive(
				true), psize(0) {
	size_t oldOffset(offset);

	//find tag type
	typeTag = BitUtil::filter(data[offset], 2, 6);

	//primitive or constructed
	primitive = BitUtil::isBitOff(data[offset], 5);

	//define tag number
	long long contentLength = parseTagNumber(data, offset);

	//define length
	parseContentLength(data, offset);

	//parse content
	parseContent(data, offset, contentLength);

	psize = offset - oldOffset;
}
