//
//  handshake.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "handshake.hpp"
#include <iostream>
#include "util.hpp"
#include "err.hpp"
using namespace std;

Handshake::Handshake(HandshakeType type, void *arg, void *arg2) :
		type(type) { //default create client hello request
	ServerHello *sHello;
	Certificate *cert;
	switch (type) {
	case CLIENT_HELLO:
		clientHello = new ClientHello();
		break;

	case CLIENT_KEY_EXCHANGE:
		sHello = ((Handshake*) arg)->getServerHello();
		cert = ((Handshake*) arg2)->getCertificate();
		//NOTE: skip checking certificate existing here. get the first one
		clientKeyExchange = new ClientKeyExchange(sHello->getCipherSuite(),
				cert->getCertificateList()[0]);
		break;

	default:
		break;
	}

}

vector<uint8_t> Handshake::toData() {
	vector<uint8_t> data;
	data.push_back(this->type);

	vector<uint8_t> body;
	switch (this->type) {
	case HELLO_REQUEST:
		break;
	case CLIENT_HELLO:
		body = clientHello->toData();
		break;
	case SERVER_HELLO:
		body = serverHello->toData();
		break;
	case CERTIFICATE:
		body = certificate->toData();
		break;
	case SERVER_KEY_EXCHANGE:
		body = serverKeyExchange->toData();
		break;
	case CERTIFICATE_REQUEST:
		body = certificateRequest->toData();
		break;
	case SERVER_HELLO_DONE:
		body = serverHelloDone->toData();
		break;
	case CERTIFICATE_VERIFY:
		break;
	case CLIENT_KEY_EXCHANGE:
		body = clientKeyExchange->toData();
		break;
	case FINISHED:
		body = finished->toData();
		break;
	default: //none
		break;
	}

	uint32_t length = (uint32_t) body.size(); //uint24_t
	Util::addData24(data, length);
	Util::addData(data, body);
	//    cout << "#begin" << endl << Util::readableForm(data) << endl;

	return data;
}

Handshake::HandshakeType Handshake::getType() {
	return type;
}

size_t Handshake::size() {
	size_t size = 0;

	switch (this->type) {
	case HELLO_REQUEST:
		break;
	case CLIENT_HELLO:
		size = clientHello->size();
		break;
	case SERVER_HELLO:
		size = serverHello->size();
		break;
	case CERTIFICATE:
		size = certificate->size();
		break;
	case SERVER_KEY_EXCHANGE:
		size = serverKeyExchange->size();
		break;
	case CERTIFICATE_REQUEST:
		size = certificateRequest->size();
		break;
	case SERVER_HELLO_DONE:
		size = serverHelloDone->size();
		break;
	case CERTIFICATE_VERIFY:
		break;
	case CLIENT_KEY_EXCHANGE:
		size = clientKeyExchange->size();
		break;
	case FINISHED:
		size = finished->size();

		break;
	default: //none
		break;
	}

	return 1 + 3 + size;
}

Handshake::~Handshake() {
	delete clientHello;
	delete certificateRequest;
	delete serverHello;
	delete certificate;
	delete serverKeyExchange;
	delete serverHelloDone;
	delete clientKeyExchange;
	delete finished;
}

ServerHello *Handshake::getServerHello() {
	return serverHello;
}

Certificate *Handshake::getCertificate() {
	return certificate;
}

Handshake::Handshake(vector<uint8_t> &data, size_t offset, void *arg) {
	this->type = (HandshakeType) data[offset];
	offset++;

	uint32_t length = Util::takeData24(data, offset);
	offset += 3;
	data.resize(offset + length);

	//check if data is long enough for body
	if (offset + length > data.size())
		throw Err(Err::DECODING);
	//copy to body
	vector<uint8_t> body(data.begin() + offset, data.begin() + offset + length);
	//reset offset
	offset = 0;
	switch (this->type) {
	case HELLO_REQUEST:
		break;
	case CLIENT_HELLO:
		break;
	case SERVER_HELLO:
		this->serverHello = new ServerHello(body, offset);
		break;
	case CERTIFICATE:
		this->certificate = new Certificate(body, offset);
		break;
	case SERVER_KEY_EXCHANGE:
		this->serverKeyExchange = new ServerKeyExchange(
				((ServerHello*) arg)->getCipherSuite(), body, offset);
		break;
	case CERTIFICATE_REQUEST:
		certificateRequest = new CertificateRequest(body, offset);
		break;
	case SERVER_HELLO_DONE:
		this->serverHelloDone = new ServerHelloDone(body, offset);
		break;
	case CERTIFICATE_VERIFY:
		break;
	case CLIENT_KEY_EXCHANGE:
		break;
	case FINISHED:
		finished = new Finished(Finished::CLIENT);
		break;
	default: //NONE://default
		break;
	}
}
