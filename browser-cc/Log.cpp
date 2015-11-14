/*
 * Log.cpp
 *
 *  Created on: Nov 14, 2015
 *      Author: nissassin17
 */

#include "Log.h"

const Log Log::warn = Log(Log::WARNING);
const Log Log::err = Log(Log::ERROR);
const Log Log::info = Log(Log::INFO);

template<typename T>
const Log& Log::operator<<(T const& str) const {
    print(str);
	return *this;
}

Log::Log(LogType logType) {
	this->logType = logType;
}

const Log &Log::operator<<(ostream_function el)const {
    printendl(el);
	return *this;
}

template<typename T>
void Log::print(T const& str) const{
    switch (logType){
        case WARNING:
            cout << str;
            break;
        case ERROR:
            cerr << str;
            break;
        case INFO:
            cout << str;
            break;
        case RESULT:
            cout << str;
            break;
        default://do nothing
            break;
    }
}

void Log::printendl(ostream_function el) const{
    switch (logType){
        case WARNING:
            cout << el;
            break;
        case ERROR:
            cerr << el;
            break;
        case INFO:
            cout << el;
            break;
        case RESULT:
            cout << el;
            break;
        default://do nothing
            break;
    }
    
}