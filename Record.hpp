//
//  record.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef record_hpp
#define record_hpp

#include <stdio.h>

#include <cstdint>
#include <vector>

#include "Exportable.hpp"
#include "Alert.hpp"
#include "ChangeCipherSpec.hpp"
#include "ProtocolVersion.hpp"

using namespace std;

#include "Handshake.hpp"
#include "ApplicationData.h"

class Record: public Exportable {
public:
	enum ContentType {
		CHANGE_CIPHER_SPEC = 20,
		ALERT = 21,
		HANDSHAKE = 22,
		APPLICATION_DATA = 23,
		NONE = 24
	};
	Record(Handshake::HandshakeType type = Handshake::CLIENT_HELLO,
			const void *arg =
			NULL, const void *arg2 = NULL);
	Record(ContentType type, vector<uint8_t> const& appData =
			vector<uint8_t>());
	Record(const vector<uint8_t> &data, size_t offset = 0,
			const void * const arg = NULL);
	virtual vector<uint8_t> toData() const;
	virtual size_t size() const;
	bool isCompressed() const;
	shared_ptr<const Alert> getAlert() const;
	shared_ptr<const ChangeCipherSpec> getChangeCipherSpec() const;
	shared_ptr<const Handshake> getHandshake() const;
	shared_ptr<const ProtocolVersion> getProtocolVersion() const;
	shared_ptr<const ApplicationData> getApplicationData() const;
	ContentType getType() const;

private:

	ContentType type;
	shared_ptr<Exportable> fragment;
	shared_ptr<ProtocolVersion> protocolVersion;
	bool compressed;

	static const int CONTENT_TYPE_LENGTH = 1;
	static const int BODY_LENGTH_LENGTH = 2;

};

#endif /* record_hpp */
