//
//  record.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include <iterator>

#include "Record.hpp"

#include "Alert.hpp"
#include "ChangeCipherSpec.hpp"
#include "Err.hpp"
#include "ProtocolVersion.hpp"
#include "Util.hpp"

Record::Record(ContentType type, vector<uint8_t> const& appData) :
		type(type), compressed(false), protocolVersion(new ProtocolVersion()) {
	switch (type) {
	case CHANGE_CIPHER_SPEC:
		fragment.reset(new ChangeCipherSpec());
		break;
	case APPLICATION_DATA:
		fragment.reset(new ApplicationData(appData));
		//TODO: implement application data here
//		fragment .reset( new ApplicationData());
		break;
	default:
		break;
	}
}

Record::Record(Handshake::HandshakeType handshakeType, const void *arg,
		const void *arg2) :
		compressed(false), protocolVersion(new ProtocolVersion()) { //default: create client hello handshake
	type = HANDSHAKE;
	switch (handshakeType) {
	case Handshake::CLIENT_KEY_EXCHANGE:
		//make client-key-exchange require serverhello (cipher type) and server's certificate (key info)
		fragment.reset(new Handshake(handshakeType, arg, arg2));
		break;
	case Handshake::CLIENT_HELLO:
		fragment.reset(new Handshake(Handshake::CLIENT_HELLO));
		break;
	case Handshake::FINISHED:
		fragment.reset(new Handshake(Handshake::FINISHED));
		break;
	default:
		break;
	}
}

vector<uint8_t> Record::toData() const {
	vector<uint8_t> bodyData(fragment->toData());
	vector<uint8_t> data;

	Util::addData(data, (uint8_t) this->type);
	Util::addData(data, this->protocolVersion->toData());

	uint16_t length = bodyData.size();
	Util::addData(data, length);
	Util::addData(data, bodyData);

	return data;
}

Record::Record(const vector<uint8_t> &data, size_t offset,
		const void * const arg) :
		compressed(false), fragment(NULL) {
	this->type = (ContentType) data[offset];
	offset += CONTENT_TYPE_LENGTH;

	this->protocolVersion.reset(new ProtocolVersion(data, offset));
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
		fragment.reset(new Handshake(fragmentData, offset, arg));
		break;

	case ALERT:
		fragment.reset(new Alert(fragmentData, offset));
		break;

	default:
		break;
	}
	offset += fragment->size();
}

size_t Record::size() const {
	return CONTENT_TYPE_LENGTH + this->protocolVersion->size()
			+ BODY_LENGTH_LENGTH + fragment->size();
}

shared_ptr<const Alert> Record::getAlert() const {
	return dynamic_pointer_cast<Alert>(fragment);
}

shared_ptr<const ChangeCipherSpec> Record::getChangeCipherSpec() const {
	return dynamic_pointer_cast<ChangeCipherSpec>(fragment);
}

bool Record::isCompressed() const {
	return compressed;
}

shared_ptr<const Handshake> Record::getHandshake() const {
	return dynamic_pointer_cast<Handshake>(fragment);
}

shared_ptr<const ProtocolVersion> Record::getProtocolVersion() const {
	return protocolVersion;
}

shared_ptr<const ApplicationData> Record::getApplicationData() const {
	return dynamic_pointer_cast<ApplicationData>(fragment);
}

Record::ContentType Record::getType() const {
	return type;
}
