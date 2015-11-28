/*
 * Asn1Name.h
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#ifndef ASN1NAME_H_
#define ASN1NAME_H_

#include "ASN1.hpp"
#include "Asn1RelativeDistinguishedName.h"
#include <vector>
using namespace std;
namespace asn1 {
//equal to RDNSequence
class Asn1Name {
public:
	Asn1Name(ASN1 const& asn1);
	const vector<shared_ptr<Asn1RelativeDistinguishedName> >& getRdnSequence() const;

private:
	vector<shared_ptr<Asn1RelativeDistinguishedName> > rdnSequence;
};
}
#endif /* ASN1NAME_H_ */
