//
//  compression-method.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/4/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef compression_method_hpp
#define compression_method_hpp

#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>

using namespace std;

class CompressionMethod {
public:
	enum Method {
		Null = 0, NONE = 255
	};
	vector<uint8_t> toData();
	CompressionMethod(Method type = Null);
	size_t size();
	CompressionMethod(vector<uint8_t> &data, size_t offset = 0);
private:
	Method type;
};
#endif /* compression_method_hpp */
