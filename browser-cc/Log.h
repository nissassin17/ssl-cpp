/*
 * Log.h
 *
 *  Created on: Nov 14, 2015
 *      Author: nissassin17
 */

#ifndef LOG_H_
#define LOG_H_

namespace rsa {

#include <iostream>

using namespace std;

class Log {
public:
	static const Log warn;
	static const Log info;
	static const Log err;
	Log &operator<<(string const& str) const;
private:
	enum LogType{
		WARNING,
		INFO,
		ERROR
	};
	ostream writer;
	Log(LogType logType);
	LogType logType;

};

} /* namespace rsa */

#endif /* LOG_H_ */
