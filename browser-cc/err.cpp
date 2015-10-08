//
//  err.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "err.hpp"

#include <cstdarg>
#include <string>

bool Err::isSuccess() {
	return this->errType == Success;
}

string Err::what() {
	return this->description;
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

	default:
		this->description = "Unknown";
		break;
	}
	va_end(args);
}
