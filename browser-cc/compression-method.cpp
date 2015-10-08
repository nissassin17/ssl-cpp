//
//  compression-method.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/4/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "compression-method.hpp"

vector<uint8_t> CompressionMethod::toData() {
	return vector<uint8_t>( { (uint8_t) this->type });
}

CompressionMethod::CompressionMethod(Method type) :
		type(type) {

}

size_t CompressionMethod::size() {
	return 1;
}

CompressionMethod::CompressionMethod(vector<uint8_t> &data, size_t offset) {
	this->type = (Method) data[offset];
}
