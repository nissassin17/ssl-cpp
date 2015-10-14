//
//  alert.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/4/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef alert_hpp
#define alert_hpp


#include <cstdint>
#include <vector>

#include "Exportable.hpp"

class Alert: public Exportable {
public:

	enum AlertLevel {
		WARNING = 1, FATAL = 2, LEVEL_NONE = 255
	};

	enum AlertDescription {
		CLOSE_NOTIFY = 0,
		UNEXPECTED_MESSAGE = 10,
		BAD_RECORD_MAC = 20,
		DECRYPTION_FAILED_reserved = 21,
		RECORD_OVERFLOW = 22,
		DECOMPRESSION_FAILURE = 30,
		HANDSHAKE_FAILURE = 40,
		NO_CERTIFICATE_reserved = 41,
		BAD_CERTIFICATE = 42,
		UNSUPPORTED_CERTIFICATE = 43,
		CERTIFICATE_REVOKED = 44,
		CERTIFICATE_EXPIRED = 45,
		CERTIFICATE_UNKNOWN = 46,
		ILLEGAL_PARAMETER = 47,
		UNKNOWN_CA = 48,
		ACCESS_DENIED = 49,
		DECODE_ERROR = 50,
		DECRYPT_ERROR = 51,
		EXPORT_RESTRICTION_reserved = 60,
		PROTOCOL_VERSION = 70,
		INSUFFICIENT_SECURITY = 71,
		INTERNAL_ERROR = 80,
		USER_CANCELED = 90,
		NO_RENEGOTIATION = 100,
		UNSUPPORTED_EXTENSION = 110,
		DESCRIPTION_NONE = 255
	};

	virtual size_t size() const;
	Alert(const vector<uint8_t> &data, size_t offset = 0);

private:
	AlertLevel level;
	AlertDescription description;
};

#endif /* alert_hpp */
