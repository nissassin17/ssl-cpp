//
//  extension.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef extension_hpp
#define extension_hpp

#include <cstdint>
#include <vector>

#include "Exportable.hpp"
using namespace std;

class Extension: Exportable {
public:
	enum ExtensionType {
		SIGNATURE_ALGORITHMS = 13, NONE = 65535
	};
	virtual vector<uint8_t> toData() const;
	virtual size_t size() const;
	Extension(const vector<uint8_t> &data, size_t offset = 0);
	Extension(ExtensionType type = NONE);

private:
	ExtensionType type;
	vector<uint8_t> data;
};

#endif /* extension_hpp */
