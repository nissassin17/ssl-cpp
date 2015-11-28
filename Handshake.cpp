//
//  handshake.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include <iterator>
#include <vector>

#include "Handshake.hpp"

using namespace std;

Handshake::Handshake(HandshakeType type, const void *arg, const void *arg2) :
		type(type) { //default create client hello request
	shared_ptr<const ServerHello> sHello;
	shared_ptr<const Certificate> cert;
	switch (type) {
	case CLIENT_HELLO:
		body.reset(new ClientHello());
		break;

	case CLIENT_KEY_EXCHANGE:
		sHello = static_cast<const Handshake*>(arg)->getServerHello();
		cert = static_cast<const Handshake*>(arg2)->getCertificate();
		//NOTE: skip checking certificate existing here. get the first one
		body.reset(
				new ClientKeyExchange(sHello->getCipherSuite(),
						cert->getCertificateList()[0]));
		break;

	case FINISHED:
		//TODO: implement finished here
		body.reset(new Finished());
		break;

	default:
		break;
	}

}

vector<uint8_t> Handshake::toData() const {
	vector<uint8_t> data;
	data.push_back(this->type);

	vector<uint8_t> bodyData(body->toData());

	uint32_t length = (uint32_t) bodyData.size(); //uint24_t
	Util::addData24(data, length);
	Util::addData(data, bodyData);
	//    cout << "#begin" << endl << Util::readableForm(data) << endl;

	return data;
}

const Handshake::HandshakeType Handshake::getType() const {
	return type;
}

size_t Handshake::size() const {
	return 1 + 3 + body->size();
}

shared_ptr<const ServerHello> Handshake::getServerHello() const {
	return dynamic_pointer_cast<ServerHello>(body);
}

shared_ptr<const Certificate> Handshake::getCertificate() const {
	return dynamic_pointer_cast<Certificate>(body);
}

//need arg (cipher type info from serverhello) incase of making server-key-exchange
Handshake::Handshake(const vector<uint8_t> &data, size_t offset,
		const void *arg) {
	this->type = (HandshakeType) data[offset];
	offset++;

	uint32_t length = Util::takeData24(data, offset);
	offset += 3;

	//check if data is long enough for body
	if (offset + length > data.size())
		throw Err(Err::DECODING);
	//copy to body
	vector<uint8_t> bodyData(data.begin() + offset,
			data.begin() + offset + length);
	//reset offset
	offset = 0;
	switch (this->type) {
	case HELLO_REQUEST:
		break;
	case CLIENT_HELLO:
		break;
	case SERVER_HELLO:
		body.reset(new ServerHello(bodyData, offset));
		break;
	case CERTIFICATE:
		body.reset(new Certificate(bodyData, offset));
		break;
	case SERVER_KEY_EXCHANGE:
		body.reset(
				new ServerKeyExchange(
						(static_cast<const ServerHello*>(arg))->getCipherSuite(),
						bodyData, offset));
		break;
	case CERTIFICATE_REQUEST:
		body.reset(new CertificateRequest(bodyData, offset));
		break;
	case SERVER_HELLO_DONE:
		body.reset(new ServerHelloDone(bodyData, offset));
		break;
	case CERTIFICATE_VERIFY:
		break;
	case CLIENT_KEY_EXCHANGE:
		break;
	case FINISHED:
		body.reset(new Finished(bodyData, offset));
		break;
	default: //NONE://default
		break;
	}
}

shared_ptr<const CertificateRequest> Handshake::getCertificateRequest() const {
	return dynamic_pointer_cast<CertificateRequest>(body);
}

shared_ptr<const ClientHello> Handshake::getClientHello() const {
	return dynamic_pointer_cast<ClientHello>(body);
}

shared_ptr<const ClientKeyExchange> Handshake::getClientKeyExchange() const {
	return dynamic_pointer_cast<ClientKeyExchange>(body);
}

shared_ptr<const Finished> Handshake::getFinished() const {
	return dynamic_pointer_cast<Finished>(body);
}

shared_ptr<const ServerHelloDone> Handshake::getServerHelloDone() const {
	return dynamic_pointer_cast<ServerHelloDone>(body);
}

shared_ptr<const ServerKeyExchange> Handshake::getServerKeyExchange() const {
	return dynamic_pointer_cast<ServerKeyExchange>(body);
}
