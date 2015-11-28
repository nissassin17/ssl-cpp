//
//  alert.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/4/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include "Alert.hpp"
#include <string>
using namespace std;

size_t Alert::size() const {
	return 2;
}

Alert::Alert(const vector<uint8_t> &data, size_t offset) {
	this->level = (AlertLevel) data[offset];
	offset++;
	this->description = (AlertDescription) data[offset];
	offset++;
}

string Alert::what() const {
	switch (description) {
	case CLOSE_NOTIFY:
		return "CLOSE_NOTIFY";
	case UNEXPECTED_MESSAGE:
		return "UNEXPECTED_MESSAGE";
	case BAD_RECORD_MAC:
		return "BAD_RECORD_MAC";
	case DECRYPTION_FAILED_reserved:
		return "DECRYPTION_FAILED_reserved";
	case RECORD_OVERFLOW:
		return "RECORD_OVERFLOW";
	case DECOMPRESSION_FAILURE:
		return "DECOMPRESSION_FAILURE";
	case HANDSHAKE_FAILURE:
		return "HANDSHAKE_FAILURE";
	case NO_CERTIFICATE_reserved:
		return "NO_CERTIFICATE_reserved";
	case BAD_CERTIFICATE:
		return "BAD_CERTIFICATE";
	case UNSUPPORTED_CERTIFICATE:
		return "UNSUPPORTED_CERTIFICATE";
	case CERTIFICATE_REVOKED:
		return "CERTIFICATE_REVOKED";
	case CERTIFICATE_EXPIRED:
		return "CERTIFICATE_EXPIRED";
	case CERTIFICATE_UNKNOWN:
		return "CERTIFICATE_UNKNOWN";
	case ILLEGAL_PARAMETER:
		return "ILLEGAL_PARAMETER";
	case UNKNOWN_CA:
		return "UNKNOWN_CA";
	case ACCESS_DENIED:
		return "ACCESS_DENIED";
	case DECODE_ERROR:
		return "DECODE_ERROR";
	case DECRYPT_ERROR:
		return "DECRYPT_ERROR";
	case EXPORT_RESTRICTION_reserved:
		return "EXPORT_RESTRICTION_reserved";
	case PROTOCOL_VERSION:
		return "PROTOCOL_VERSION";
	case INSUFFICIENT_SECURITY:
		return "INSUFFICIENT_SECURITY";
	case INTERNAL_ERROR:
		return "INTERNAL_ERROR";
	case USER_CANCELED:
		return "USER_CANCELED";
	case NO_RENEGOTIATION:
		return "NO_RENEGOTIATION";
	case UNSUPPORTED_EXTENSION:
		return "UNSUPPORTED_EXTENSION";
	case DESCRIPTION_NONE:
		return "DESCRIPTION_NONE";
	default:
		return "unknown";
	}
}
