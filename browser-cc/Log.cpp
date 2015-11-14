/*
 * Log.cpp
 *
 *  Created on: Nov 14, 2015
 *      Author: nissassin17
 */

#include "Log.h"

namespace rsa {

const Log Log::err = Log(Log::ERROR);
const Log Log::info = Log(Log::INFO);
const Log Log::warn = Log(Log::WARNING);

} /* namespace rsa */

rsa::Log& rsa::Log::operator<<(const string& str) const {
	writer << str;
	return *this;
}

rsa::Log::Log(LogType logType) {
	this->logType = logType;
	switch (logType){
	case WARNING:
		writer = cout;
		break;
	case ERROR:
		writer = cerr;
		break;
	case INFO:
		writer = cout;
		break;
	}

}
