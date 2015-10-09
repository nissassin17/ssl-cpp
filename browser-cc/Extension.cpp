//
//  extension.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "Extension.hpp"
#include "Util.hpp"

vector<uint8_t> Extension::toData()  const{
	vector<uint8_t> data;
	Util::addData(data, (uint16_t) this->type);
	Util::addData(data, (uint16_t) this->data.size());
	Util::addData(data, this->data);
	return data;
}
size_t Extension::size() const {
	return 2 + 2 + this->data.size();
}

Extension::Extension(ExtensionType type) :
		type(type) {

}

Extension::Extension(const vector<uint8_t> &data, size_t offset) {
	this->type = (ExtensionType) Util::takeData16(data, offset);
	//preserve 2 bytes for length
	uint16_t length = Util::takeData16(data, offset + 2);
	this->data = Util::takeData(data, length, offset + 4);
}
