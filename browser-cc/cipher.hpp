//
//  cipher.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef cipher_hpp
#define cipher_hpp

#include <stdio.h>

class Cipher {
public:
	enum CipherType {
		CIPHER_NULL, RC4_128, _3DES_EDE_CBC, AES_128_CBC, AES_256_CBC
	};

	enum Format {
		STREAM, BLOCK
	};

	Format getFormat();
	int getKeyMaterial();
	size_t getIVSize();
	size_t getBlockSize();
	Cipher(CipherType type);

private:
	void setType(CipherType type);
	CipherType type;
	Format format;
	int keyMaterial;
	size_t ivSize;
	size_t blockSize;
};

#endif /* cipher_hpp */
