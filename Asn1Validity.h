/*
 * Asn1Validity.h
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#ifndef ASN1VALIDITY_H_
#define ASN1VALIDITY_H_

#include "ASN1.hpp"
#include "Asn1Time.h"
namespace asn1 {

class Asn1Validity {
public:
	Asn1Validity(ASN1 const& asn1);
	const shared_ptr<Asn1Time>& getNotAfter() const;
	const shared_ptr<Asn1Time>& getNotBefore() const;

private:
	shared_ptr<Asn1Time> notBefore;
	shared_ptr<Asn1Time> notAfter;
};

} /* namespace asn1 */

#endif /* ASN1VALIDITY_H_ */
