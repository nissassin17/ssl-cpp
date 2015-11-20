/*
 * Asn1SetClass.h
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#ifndef ASN1SET_H_
#define ASN1SET_H_
#include "ASN1.hpp"
#include <set>
using namespace std;
namespace asn1 {

class Asn1Set {
public:
	Asn1Set(ASN1 const& asn1);
private:
	set<ASN1::ObjectIdentifierType, ASN1*> value;
};

} /* namespace asn1 */

#endif /* ASN1SET_H_ */
