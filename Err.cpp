//
//  err.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include <cstdarg>
#include <string>
#include "Err.hpp"

bool Err::isSuccess() const {
	return this->errType == Success;
}

const char *Err::what() const throw () {
	return this->description.c_str();
}

Err::Err(ErrType errType, ...) :
		runtime_error("Browser error"), errType(errType) {
	va_list args;
	va_start(args, errType);

	switch (errType) {
	case Success:
		this->description = "Success";
		break;

	case NoLinkProvided:
		this->description = "No link provided";
		break;

	case UnsupportedSchema:
		this->description =
				"Unsupported schema (currently only support http and https)";
		break;

	case NoHostnameProvided:
		this->description = "Please provide hostname";
		break;

	case CannotCreateSock:
		this->description = "System error. Cannot create sock";
		break;

	case CannotConnect:
		this->description = "Cannot connect";
		break;

	case CannotSend:
		this->description = "Cannot send request";
		break;

	case CannotReceive:
		this->description = "Cannot receive response";
		break;

	case CannotResolveHostname:
		this->description = "Cannot resolve hostname";
		break;

	case NoConnection:
		this->description = "There is no connection";
		break;

	case DontSendButReceive:
		this->description =
				"Receive response without sending any request (what a weird error lol)";
		break;

	case DECODING:
		this->description = "invalid encoding (cannot decode)";
		break;
	default:
		this->description = "Unknown error";
		break;
	}
	va_end(args);
}

Err::~Err() throw () {
}
