/*
 * Asn1Time.h
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#ifndef ASN1TIME_H_
#define ASN1TIME_H_

#include "ASN1.hpp"
namespace asn1 {

class Asn1Time {
public:
	Asn1Time(ASN1 const& asn1);
private:
	ASN1::TimeType time; //UTCTime or GenerailizedTime
};

} /* namespace asn1 */

#endif /* ASN1TIME_H_ */
