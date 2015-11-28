//
//  encrypted-pre-master-secret.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

/* Note
 Implementation note: Public-key-encrypted data is represented as an
 opaque vector <0..2^16-1> (see Section 4.7).  Thus, the RSA-encrypted
 PreMasterSecret in a ClientKeyExchange is preceded by two length
 bytes.  These bytes are redundant in the case of RSA because the
 EncryptedPreMasterSecret is the only data in the ClientKeyExchange
 and its length can therefore be unambiguously determined.  The SSLv3
 specification was not clear about the encoding of public-key-
 encrypted data, and therefore many SSLv3 implementations do not
 include the length bytes -- they encode the RSA-encrypted data
 directly in the ClientKeyExchange message.
 
 This specification requires correct encoding of the
 EncryptedPreMasterSecret complete with length bytes.  The resulting
 PDU is incompatible with many SSLv3 implementations.  Implementors
 upgrading from SSLv3 MUST modify their implementations to generate
 and accept the correct encoding.  Implementors who wish to be
 compatible with both SSLv3 and TLS should make their implementation's
 behavior dependent on the protocol version.
 */

#include "EncryptedPreMasterSecret.hpp"
#include "PreMasterSecret.hpp"
#include "Util.hpp"
#include "CipherCore.hpp"

vector<uint8_t> EncryptedPreMasterSecret::toData() const {
	//return encrypted type as public-key-encrypted
	vector<uint8_t> data;

	//default with https://google.com
//TLS_RSA_WITH_AES_128_CBC_SHA256

	Util::addData(data, (uint16_t) encryptedData.size());
	Util::addData(data, encryptedData);
	return data;
}

EncryptedPreMasterSecret::EncryptedPreMasterSecret(
		shared_ptr<const CipherSuite> cipherSuite,
		shared_ptr<const rsa::Asn1Cert> asn1Cert) :
		cipherSuite(cipherSuite), asn1Cert(asn1Cert), preMasterSecret(
				new PreMasterSecret()) {
	//    std::cout << "======ASN1Cert BEGIN=====" << endl;
	//    std::cout << Util::readableForm(asn1Cert->toData()) << endl;
	//    std::cout << "======ASN1Cert END=======" << endl;
	//start encrypting
	encryptedData = CipherCore::rsaep(*(asn1Cert->getRsaPublicKey()),
			preMasterSecret->toData());

}
size_t EncryptedPreMasterSecret::size() const {
	//return size after encrypted data in premastersecret
	return 2 + encryptedData.size(); //2 stand for data length. result should be plused by encrypted data
}
