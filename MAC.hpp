//
//  mac.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef mac_hpp
#define mac_hpp

class MAC {
public:
	enum MACType {
		MAC_NULL, MD5, SHA, SHA256
	};
	enum Algorithm {
		ALGORITHM_NONE, HMAC_MD5, HMAC_SHA1, HMAC_SHA256
	};
	MAC(MACType type);

	int getMacLength() const;
	int getMacKeyLength() const;
	Algorithm getAlgorithm() const;
private:
	void setType(MACType type);
	MACType type;
	int macLength;
	int macKeyLength;
	Algorithm algorithm;
};

#endif /* mac_hpp */
