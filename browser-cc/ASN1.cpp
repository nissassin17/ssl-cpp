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
    delete wrappedData;
}

void ASN1::parseTagNumber(const vector<uint8_t>& data, size_t& offset) {
	//define tag number
	if (BitUtil::isAllOne(data[offset], 5)) {
		//high tag number
		offset++;
		tagNumber = 0ll;
		do {
			tagNumber = BitUtil::append(tagNumber,
					BitUtil::filter(data[offset], 7), 7);
			

			offset++;
        }while(BitUtil::isBitOn(data[offset - 1], 7));
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
	if (BitUtil::isBitOff(data[offset], 7)) {
		//short form definitive
		definitive = true;
        contentLength = BitUtil::filter(data[offset], 7);
		offset++;
	} else {
		//long form: definitive or indefinitive
		if (not BitUtil::isAllZero(data[offset], 7)) {
			//definitive
			definitive = false;
			//number of octets for length octet
			int nlengthOctets = (int)BitUtil::filter(data[offset], 7);
			while (offset++, nlengthOctets--) {
				contentLength = BitUtil::append(contentLength, data[offset], 8);
			}

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
	intVal = vector<uint8_t>();
	bool isNegative = BitUtil::isBitOn(data[offset], 7);
	for (int i = 0; i < contentLength; i++) {
		intVal.push_back(data[offset]);
//		intVal = BitUtil::append(intVal, data[offset], 8);
		offset++;
	}
    // BIG NOTE HERE: do 2-complement in case of negative
//	if (isNegative) {
//		intVal -= (1 << (contentLength - 1));
//	}
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
	while ((contentLength >= 0 and contentLength + oldOffset > offset) or (contentLength == -1 and offset < data.size())) {
		sequenceVal.push_back(new ASN1(data, offset));
		offset += (*sequenceVal.rbegin())->size();
	}
}

void ASN1::parseSet(const vector<uint8_t>& data, size_t& offset,
		long long contentLength) {
	size_t oldOffset(offset);
	while ((contentLength >= 0 and contentLength + oldOffset > offset) or (contentLength == -1 and offset < data.size())) {
		ASN1* val = new ASN1(data, offset);
		setVal.insert(val);
		offset += val->size();
	}
}

void ASN1::parseObjectIdentifier(const vector<uint8_t>& data, size_t& offset,
		long long contentLength) {
	size_t oldOffset(offset);
	while ((contentLength >= 0 and contentLength + oldOffset > offset) or (contentLength == -1 and offset < data.size())){
		long long subid(0ll);
		do {
			subid = BitUtil::append(subid, data[offset], 7);
			offset++;
        }while(BitUtil::isBitOn(data[offset - 1], 7));
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

		//NOTE: take bitstring as array of bytes (not bool)
//		for (int j = 0; j < 8 - t; j++)
//			bitStringVal.push_back(BitUtil::isBitOn(data[offset], 7 - j));
		bitStringVal.push_back(data[offset]);
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
	case ENUMERATED:
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
        case UTF8_STRING:
//		parseOctetString(data, offset, contentLength);
//		break;

	case IA5_STRING:
//		parseOctetString(data, offset, contentLength);
//		break;

	case PRINTABLE_STRING:
//		parseOctetString(data, offset, contentLength);
//		break;

	case UTC_TIME:
		parseOctetString(data, offset, contentLength);
		break;

	default:
		throw logic_error("unimplemented asn1 type");
		break;
	}
}

ASN1::ASN1(const vector<uint8_t> &data, size_t offset) :
		typeTag(ASN1_NULL), tagClass(UNIVERSAL), primitive(false), tagNumber(0), definitive(
				true), psize(0), wrappedData(NULL) {
	size_t oldOffset(offset);

	//find tag type
	tagClass = (TagClass)BitUtil::filter(data[offset], 2, 6);

	//primitive or constructed
	primitive = BitUtil::isBitOff(data[offset], 5);

	//define tag number
	parseTagNumber(data, offset);

	//define length
	long long contentLength = parseContentLength(data, offset);

	if (tagClass == CONTEXT_SPECIFIC){
		vector<uint8_t> wrapper(data.begin() + offset, data.begin() + offset + contentLength);
        offset += contentLength;
		wrappedData = new ASN1(wrapper, 0);

	}else
		//parse content
		parseContent(data, offset, contentLength);

	psize = offset - oldOffset;
}

const ASN1::BitStringType& ASN1::getBitStringVal() const {
	return bitStringVal;
}

ASN1::BoolType ASN1::isBoolVal() const {
	return boolVal;
}

bool ASN1::isDefinitive() const {
	return definitive;
}

ASN1::IntType ASN1::getIntVal() const {
	return intVal;
}

const ASN1::ObjectIdentifierType& ASN1::getObjectIdentifierVal() const {
	return objectIdentifierVal;
}

const ASN1::OctetStringType& ASN1::getOctetStringVal() const {
	return octetStringVal;
}

bool ASN1::isPrimitive() const {
	return primitive;
}

size_t ASN1::getPsize() const {
	return psize;
}

const ASN1::SequenceType& ASN1::getSequenceVal() const {
	return sequenceVal;
}

const ASN1::SetType& ASN1::getSetVal() const {
	return setVal;
}
