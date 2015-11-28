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
#include <map>
using namespace std;
namespace asn1 {

class Asn1Map {
public:
	Asn1Map(ASN1 const& asn1);
	const map<ASN1::ObjectIdentifierType, shared_ptr<ASN1> >& getData() const;

private:
	map<ASN1::ObjectIdentifierType, shared_ptr<ASN1> > data;
};

} /* namespace asn1 */

#endif /* ASN1SET_H_ */
