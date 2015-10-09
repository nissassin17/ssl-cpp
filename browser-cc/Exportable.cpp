//
//  exportable.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include <stdexcept>
#include "Exportable.hpp"

size_t Exportable::size() const {
	throw std::logic_error("Cannot call Exportable::size()");
}

vector<uint8_t> Exportable::toData() const{
	throw std::logic_error("Cannot call Exportable::toData()");
}

