//
//  record.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef record_hpp
#define record_hpp

#include <stdio.h>
#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>

#include "Exportable.hpp"

using namespace std;

#include "Handshake.hpp"

class Alert;
class ChangeCipherSpec;
class ProtocolVersion;

class Record: public Exportable {
public:
	enum ContentType {
		CHANGE_CIPHER_SPEC = 20,
		ALERT = 21,
		HANDSHAKE = 22,
		APPLICATION_DATA = 23,
		NONE = 24
	};
	Record(Handshake::HandshakeType type = Handshake::CLIENT_HELLO, void *arg =
	NULL, void *arg2 = NULL);
	Record(ContentType type);
	Record(const vector<uint8_t> &data, size_t offset = 0, void *arg = NULL);
	virtual vector<uint8_t> toData() const;
	virtual size_t size() const;
	virtual ~Record();
	const Alert* getAlert() const;
	const ChangeCipherSpec* getChangeCipherSpec() const;
	bool isCompressed() const;
	const Handshake* getHandshake() const;
	const ProtocolVersion* getProtocolVersion() const;
	ContentType getType() const;

private:

	ContentType type;
	Exportable *fragment;
	ProtocolVersion *protocolVersion = NULL;
	bool compressed;

	static const int CONTENT_TYPE_LENGTH = 1;
	static const int BODY_LENGTH_LENGTH = 2;

};

#endif /* record_hpp */
