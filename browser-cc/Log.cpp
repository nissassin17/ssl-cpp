/*
 * Log.cpp
 *
 *  Created on: Nov 14, 2015
 *      Author: nissassin17
 */

#include "Log.h"

Log::Log(LogType logType):
logType(logType){
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
const void Log::operator<<(EofObject const& eofObject) const{
    ofile->close();
}

const Log& Log::operator<<(vector<uint8_t> const& __v)const{
    if (this->logType == FILE){
        for (int i = 0; i < __v.size(); i++)
            (*ofile) << __v[i];
        return *this;
    }
    string str;
    for (int i = 0; i < __v.size(); i++) {
        if (i and i % 16 == 0)
            str += "\n";
        else if (i and i % 8 == 0)
            str += " | ";
        char a[3];
        sprintf(a, "%02x", (uint8_t) __v[i]);
        str += " ";
        str += a;
        
    }
    return (*this) << str;
}

const Log Log::warn = Log(Log::WARNING);
const Log Log::err = Log(Log::ERROR);
const Log Log::info = Log(Log::INFO);
const Log Log::result = Log(Log::RESULT);
const Log::EofObject Log::eof = Log::EofObject();

Log Log::file(string const& filename){
    return Log(filename);
}

Log::Log(string const& filename):
logType(FILE), filename(filename),
ofile(new ofstream(filename, ios::out bitor ios::binary)){
}
