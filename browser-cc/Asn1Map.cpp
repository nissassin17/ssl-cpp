/*
 * Asn1SetClass.cpp
 *
 *  Created on: Nov 20, 2015
 *      Author: nissassin17
 */

#include "Asn1Map.h"

namespace asn1 {

Asn1Map::Asn1Map(ASN1 const& asn1) {
	const ASN1::SetType &setVal = asn1.getSetVal();
	//**TODO**: hard copy asn1 value here instead of taking reference because the original asn1 object will be freed after being parsed to this constructor
//    for(ASN1::SetType::const_iterator it = setVal.begin(); it != setVal.end(); it++){
//        ASN1 *val = new ASN1(it->getSequenceVal()[1]);
//        value[it->getSequenceVal()[0]->getObjectIdenfifierVal()] = val;
//        value[it->getSequenceVal()[0]->getObjectIdenfifierVal()] = NULL;
//    }

}

} /* namespace asn1 */
