//
//  cipher.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "cipher.hpp"
Cipher::Format Cipher::getFormat() {
	return format;
}
int Cipher::getKeyMaterial() {
	return keyMaterial;
}
size_t Cipher::getIVSize() {
	return ivSize;
}
;
size_t Cipher::getBlockSize() {
	return blockSize;
}

Cipher::Cipher(CipherType type) {
	setType(type);
}
;

void Cipher::setType(CipherType type) {
	this->type = type;
	switch (type) {
	case CIPHER_NULL:
		format = STREAM;
		keyMaterial = 0;
		ivSize = 0;
		blockSize = -1;
		break;
	case RC4_128:
		format = STREAM;
		keyMaterial = 16;
		ivSize = 0;
		break;

	case _3DES_EDE_CBC:
		format = BLOCK;
		keyMaterial = 24;
		ivSize = 8;
		blockSize = 8;
		break;

	case AES_128_CBC:
		format = BLOCK;
		keyMaterial = 16;
		ivSize = 16;
		blockSize = 16;
		break;

	case AES_256_CBC:
		format = BLOCK;
		keyMaterial = 32;
		ivSize = 16;
		blockSize = 16;
		break;

	default:
		break;
	}
}
