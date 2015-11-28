/*
 * Asn1RelativeDistinguishedName.h
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#ifndef ASN1RELATIVEDISTINGUISHEDNAME_H_
#define ASN1RELATIVEDISTINGUISHEDNAME_H_

#include <set>

#include "Asn1Map.h"
#include "ASN1.hpp"
using namespace std;
namespace asn1 {

class Asn1RelativeDistinguishedName: public Asn1Map {
public:
	Asn1RelativeDistinguishedName(ASN1 const& asn1);
};

} /* namespace asn1 */

#endif /* ASN1RELATIVEDISTINGUISHEDNAME_H_ */
