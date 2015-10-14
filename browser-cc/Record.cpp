//
//  record.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include <iterator>

#include "Record.hpp"

#include "Alert.hpp"
#include "ChangeCipherSpec.hpp"
#include "Err.hpp"
#include "ProcotolVersion.hpp"
#include "Util.hpp"

Record::Record(ContentType type) :
		type(type), compressed(false),
protocolVersion(new ProtocolVersion()){
	switch (type) {
	case CHANGE_CIPHER_SPEC:
		fragment = new ChangeCipherSpec();
		break;
	default:
		break;
	}
}

Record::Record(Handshake::HandshakeType handshakeType, const void *arg, const void *arg2) :
		compressed(false), protocolVersion(new ProtocolVersion()) { //default: create client hello handshake
	type = HANDSHAKE;
	switch (handshakeType) {
	case Handshake::CLIENT_KEY_EXCHANGE:
		fragment = new Handshake(handshakeType, arg, arg2);
		break;
	case Handshake::CLIENT_HELLO:
		fragment = new Handshake(Handshake::CLIENT_HELLO);
		break;
	case Handshake::FINISHED:
		fragment = new Handshake(Handshake::FINISHED);
		break;
	default:
		break;
	}
}


Record::~Record() {
	delete this->protocolVersion;
	delete fragment;
}

vector<uint8_t> Record::toData() const{
	vector<uint8_t> bodyData(fragment->toData());
	vector<uint8_t> data;

	Util::addData(data, (uint8_t) this->type);
	Util::addData(data, this->protocolVersion->toData());

	uint16_t length = bodyData.size();
	Util::addData(data, length);
	Util::addData(data, bodyData);

	return data;
}

Record::Record(const vector<uint8_t> &data, size_t offset, const void *arg) :
		compressed(false),
		fragment(NULL){
	this->type = (ContentType) data[offset];
	offset += CONTENT_TYPE_LENGTH;

	this->protocolVersion = new ProtocolVersion(data, offset);
	offset += this->protocolVersion->size();

	uint16_t bodyLength = Util::takeData16(data, offset);
	offset += BODY_LENGTH_LENGTH;

	//through error if not enough data
	if (offset + bodyLength > data.size())
		throw Err(Err::DECODING);
	//copy the fragment part
	vector<uint8_t> fragmentData(data.begin() + offset,
			data.begin() + offset + bodyLength);
	//reset offset
	offset = 0;
//    data.resize(offset + bodyLength);

	switch (this->type) {
	case HANDSHAKE:
		fragment = new Handshake(fragmentData, offset, arg);
		break;

	case ALERT:
		fragment = new Alert(fragmentData, offset);
		break;

	default:
		break;
	}
	offset += fragment->size();
}

size_t Record::size() const {
	return CONTENT_TYPE_LENGTH + this->protocolVersion->size() + BODY_LENGTH_LENGTH + fragment->size();
}

const Alert *Record::getAlert() const{
	return dynamic_cast<Alert*>(fragment);
}

const ChangeCipherSpec* Record::getChangeCipherSpec() const {
	return dynamic_cast<ChangeCipherSpec*>(fragment);
}

bool Record::isCompressed() const{
	return compressed;
}

const Handshake* Record::getHandshake() const {
	return dynamic_cast<Handshake*>(fragment);
}

const ProtocolVersion* Record::getProtocolVersion() const {
	return protocolVersion;
}

Record::ContentType Record::getType() const {
	return type;
}
