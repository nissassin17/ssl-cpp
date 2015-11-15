/*
 * Log.cpp
 *
 *  Created on: Nov 14, 2015
 *      Author: nissassin17
 */

#include "Log.h"

Log::Log(LogType logType) {
	this->logType = logType;
}

const Log& Log::operator<<(basic_ostream<char>& (* const __pf)(basic_ostream<char>&)) const{
	log_print(__pf);
}
const Log& Log::operator<<(basic_ios<char>&
                              (* const __pf)(basic_ios<char>&)) const{
	log_print(__pf);
}
const Log& Log::operator<<(ios_base& (* const __pf)(ios_base&)) const{
	log_print(__pf);
}
const Log& Log::operator<<(string const& __s) const{
	log_print(__s);
}
const Log& Log::operator<<(const bool __n) const{
	log_print(__n);
}
const Log& Log::operator<<(const short __n) const{
	log_print(__n);
}
const Log& Log::operator<<(const unsigned short __n) const{
	log_print(__n);
}
const Log& Log::operator<<(const int __n) const{
	log_print(__n);
}
const Log& Log::operator<<(const unsigned int __n) const{
	log_print(__n);
}
const Log& Log::operator<<(const long __n) const{
	log_print(__n);
}
const Log& Log::operator<<(const unsigned long __n) const{
	log_print(__n);
}
const Log& Log::operator<<(const long long __n) const{
	log_print(__n);
}
const Log& Log::operator<<(const unsigned long long __n) const{
	log_print(__n);
}
const Log& Log::operator<<(const float __f) const{
	log_print(__f);
}
const Log& Log::operator<<(const double __f) const{
	log_print(__f);
}
const Log& Log::operator<<(const long double __f) const{
	log_print(__f);
}
const Log& Log::operator<<(const void* const __p) const{
	log_print(__p);
}
const Log& Log::operator<<(basic_streambuf<char>* const  __sb) const{
	log_print(__sb);
}
const Log& Log::operator<<(const char * const __s) const{
	log_print(__s);
}

const Log Log::warn = Log(Log::WARNING);
const Log Log::err = Log(Log::ERROR);
const Log Log::info = Log(Log::INFO);
const Log Log::result = Log(Log::RESULT);
