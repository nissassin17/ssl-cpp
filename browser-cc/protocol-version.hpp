//
//  protocol-version.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef protocol_version_hpp
#define protocol_version_hpp

#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>

#define SSL_VERSION_MAJOR 3
#define SSL_VERSION_MINOR 3

using namespace std;

class ProtocolVersion {
public:
	ProtocolVersion(uint8_t major = SSL_VERSION_MAJOR, uint8_t minor =
	SSL_VERSION_MINOR);
	ProtocolVersion(vector<uint8_t> &data, size_t offset = 0);
	vector<uint8_t> toData();
	size_t size();
private:
	uint8_t major, minor;
};

#endif /* protocol_version_hpp */
