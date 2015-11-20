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
    ~Asn1Validity();
Asn1Time* getNotAfter() const;
Asn1Time* getNotBefore() const;

private:
	Asn1Time *notBefore;
	Asn1Time *notAfter;
};

} /* namespace asn1 */

#endif /* ASN1VALIDITY_H_ */
