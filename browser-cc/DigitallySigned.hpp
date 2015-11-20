//
//  digitally-signed.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/5/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef digitally_signed_hpp
#define digitally_signed_hpp


#include <cstdint>
#include <vector>

#include "Exportable.hpp"
using namespace std;
class ServerDHParams;

class DigitallySigned  : Exportable{
public:
	DigitallySigned(const vector<uint8_t> &data, size_t offset = 0);
	virtual size_t size() const;
	virtual ~DigitallySigned();
private:
	uint8_t clientRandom[32];
	uint8_t serverRandom[32];
	ServerDHParams *params;
};

#endif /* digitally_signed_hpp */
