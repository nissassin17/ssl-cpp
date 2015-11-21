/*
 * Log.h
 *
 *  Created on: Nov 14, 2015
 *      Author: nissassin17
 */

#ifndef LOG_H_
#define LOG_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#define log_print(val)\
        ostringstream ss;\
    switch (logType){\
        case WARNING:\
           cerr << (val);\
           break;\
       case ERROR:\
           cerr << (val);\
           break;\
       case INFO:\
           cout << (val);\
           break;\
       case RESULT:\
           cout << (val);\
           break;\
        case FILE:\
            ss << (val);\
            (*ofile) << ss.str();\
            break;\
       default:\
           break;\
   };\
	return *this;

using namespace std;



class Log {
public:
    class EofObject{
    public:
        EofObject(){}
    };

    
	static const Log warn;
	static const Log info;
	static const Log err;
	static const Log result;
    static const EofObject eof;
    static Log file(string const& filename);
    

    const void operator<<(EofObject const& eofObject) const;
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
    const Log& operator<<(vector<uint8_t> const& __v) const;
    ~Log();
    
private:

	enum LogType{
		WARNING,
		INFO,
		ERROR,
		RESULT,
        FILE
	};
	Log(LogType logType);
    Log(string const& filename);//file type
    ofstream *ofile;
	LogType logType;
    string filename;
};


#endif /* LOG_H_ */
