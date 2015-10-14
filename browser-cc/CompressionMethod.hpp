//
//  compression-method.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/4/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef compression_method_hpp
#define compression_method_hpp


#include <cstdint>
#include <vector>

#include "Exportable.hpp"

using namespace std;

class CompressionMethod : public Exportable{
public:
	enum Method {
		Null = 0, NONE = 255
	};
	virtual vector<uint8_t> toData() const;
	CompressionMethod(Method type = Null);
	virtual size_t size() const;
	CompressionMethod(const vector<uint8_t> &data, size_t offset = 0);
private:
	Method type;
};
#endif /* compression_method_hpp */
