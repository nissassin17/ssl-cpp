/*
 * Log.h
 *
 *  Created on: Nov 14, 2015
 *      Author: nissassin17
 */

#ifndef LOG_H_
#define LOG_H_

#include <iostream>

#define log_print(str) switch (logType){\
        case WARNING:\
           cerr << (str);\
           break;\
       case ERROR:\
           cerr << (str);\
           break;\
       case INFO:\
           cout << (str);\
           break;\
       case RESULT:\
           cout << (str);\
           break;\
       default:\
           break;\
   };\
	return *this;

using namespace std;



class Log {
public:

	static const Log warn;
	static const Log info;
	static const Log err;
	static const Log result;

    const Log& operator<<(basic_ostream<char>& (*const __pf)(basic_ostream<char>&)) const;
    const Log& operator<<(basic_ios<char>&
                              (* const  __pf)(basic_ios<char>&)) const;
	const Log& operator<<(string const& __s) const;
	const Log& operator<<(const char * const __s) const;
    const Log& operator<<(ios_base& (* const __pf)(ios_base&)) const;
    const Log& operator<<(const bool __n) const;
    const Log& operator<<(const short __n) const;
    const Log& operator<<(const unsigned short __n) const;
    const Log& operator<<(const int __n) const;
    const Log& operator<<(const unsigned int __n) const;
    const Log& operator<<(const long __n) const;
    const Log& operator<<(const unsigned long __n) const;
    const Log& operator<<(const long long __n) const;
    const Log& operator<<(const unsigned long long __n) const;
    const Log& operator<<(const float __f) const;
    const Log& operator<<(const double __f) const;
    const Log& operator<<(const long double __f) const;
    const Log& operator<<(const void* const __p) const;
    const Log& operator<<(basic_streambuf<char> * const __sb) const;
private:

	enum LogType{
		WARNING,
		INFO,
		ERROR,
		RESULT
	};
	Log(LogType logType);
	LogType logType;
};


#endif /* LOG_H_ */
