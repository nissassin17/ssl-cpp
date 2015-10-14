//
//  change-cipher-spec.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "ChangeCipherSpec.hpp"

ChangeCipherSpec::ChangeCipherSpec() :
type(NONE){
	}

ChangeCipherSpec::~ChangeCipherSpec() {

}

size_t ChangeCipherSpec::size()  const{
	return 1;
}

vector<uint8_t> ChangeCipherSpec::toData() const{
	vector<uint8_t> data;
	data.push_back( (uint8_t) type );
	return data;
}