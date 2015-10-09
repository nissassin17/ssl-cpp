//
//  alert.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/4/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "alert.hpp"

size_t Alert::size() const{
	return 2;
}

Alert::Alert(const vector<uint8_t> &data, size_t offset) {
	this->level = (AlertLevel) data[offset];
	offset++;
	this->description = (AlertDescription) data[offset];
	offset++;
}
