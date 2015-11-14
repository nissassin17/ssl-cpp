/*
 * Log.h
 *
 *  Created on: Nov 14, 2015
 *      Author: nissassin17
 */

#ifndef LOG_H_
#define LOG_H_

#include <iostream>

using namespace std;



class Log {
public:
    typedef ostream& (*ostream_function)( ostream& );
    
	static const Log warn;
	static const Log info;
	static const Log err;
	static const Log result;

	template <typename T>
	const Log &operator<<(T const& str) const;

	const Log &operator<<(ostream_function el) const;

private:

	enum LogType{
		WARNING,
		INFO,
		ERROR,
		RESULT
	};
	const string prefix;
	Log(LogType logType);
	LogType logType;
    template <typename T>
    void print(T const& str) const;
    void printendl(ostream_function el) const;

};


#endif /* LOG_H_ */
