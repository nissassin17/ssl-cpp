//
//  change-cipher-spec.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef change_cipher_spec_hpp
#define change_cipher_spec_hpp

#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>

#include "Exportable.hpp"

class ChangeCipherSpec: public Exportable {
public:
	ChangeCipherSpec();
	~ChangeCipherSpec();
	virtual size_t size() const;
	virtual vector<uint8_t> toData() const;
private:
	enum ChangeCipherSpecType {
		CHANGE_CIPHER_SPEC = 1, NONE = 255
	};
	ChangeCipherSpecType type;
};

#endif /* change_cipher_spec_hpp */
