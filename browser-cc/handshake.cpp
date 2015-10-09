//
//  handshake.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "handshake.hpp"

#include <iterator>
#include <vector>

#include "certificate.hpp"
#include "certificate-request.hpp"
#include "client-hello.hpp"
#include "client-key-exchange.hpp"
#include "err.hpp"
#include "finished.hpp"
#include "server-hello.hpp"
#include "server-hello-done.hpp"
#include "server-key-exchange.hpp"
#include "util.hpp"

using namespace std;

Handshake::Handshake(HandshakeType type, void *arg, void *arg2) :
		type(type) { //default create client hello request
	ServerHello *sHello;
	Certificate *cert;
	switch (type) {
	case CLIENT_HELLO:
		body = new ClientHello();
		break;

	case CLIENT_KEY_EXCHANGE:
		sHello = ((Handshake*) arg)->getServerHello();
		cert = ((Handshake*) arg2)->getCertificate();
		//NOTE: skip checking certificate existing here. get the first one
		body = new ClientKeyExchange(sHello->getCipherSuite(),
				cert->getCertificateList()[0]);
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

const Handshake::HandshakeType Handshake::getType() const{
	return type;
}

size_t Handshake::size()const {
	return 1 + 3 + body->size();
}

Handshake::~Handshake() {
	delete body;
}

const ServerHello* Handshake::getServerHello() const {
	return dynamic_cast<ServerHello*>(body);
}

const Certificate* Handshake::getCertificate() const{
	return dynamic_cast<Certificate*>(body);
}

Handshake::Handshake(const vector<uint8_t> &data, size_t offset, void *arg) {
	this->type = (HandshakeType) data[offset];
	offset++;

	uint32_t length = Util::takeData24(data, offset);
	offset += 3;

	//check if data is long enough for body
	if (offset + length > data.size())
		throw Err(Err::DECODING);
	//copy to body
	vector<uint8_t> bodyData(data.begin() + offset, data.begin() + offset + length);
	//reset offset
	offset = 0;
	switch (this->type) {
	case HELLO_REQUEST:
		break;
	case CLIENT_HELLO:
		break;
	case SERVER_HELLO:
		body = new ServerHello(bodyData, offset);
		break;
	case CERTIFICATE:
		body = new Certificate(bodyData, offset);
		break;
	case SERVER_KEY_EXCHANGE:
		body = new ServerKeyExchange(
				((ServerHello*) arg)->getCipherSuite(), bodyData, offset);
		break;
	case CERTIFICATE_REQUEST:
		body = new CertificateRequest(bodyData, offset);
		break;
	case SERVER_HELLO_DONE:
		body = new ServerHelloDone(bodyData, offset);
		break;
	case CERTIFICATE_VERIFY:
		break;
	case CLIENT_KEY_EXCHANGE:
		break;
	case FINISHED:
		body = new Finished(Finished::CLIENT);
		break;
	default: //NONE://default
		break;
	}
}

const CertificateRequest* Handshake::getCertificateRequest() const {
	return dynamic_cast<CertificateRequest*> (body);
}

const ClientHello* Handshake::getClientHello() const {
	return dynamic_cast<ClientHello*>(body);
}

const ClientKeyExchange* Handshake::getClientKeyExchange() const {
	return dynamic_cast<ClientKeyExchange*>(body);
}

const Finished* Handshake::getFinished() const {
	return dynamic_cast<Finished*>(body);
}

const ServerHelloDone* Handshake::getServerHelloDone() const {
	return dynamic_cast<ServerHelloDone*>(body);
}

const ServerKeyExchange* Handshake::getServerKeyExchange() const {
	return dynamic_cast<ServerKeyExchange*>(body);
}
