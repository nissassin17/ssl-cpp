//
//  SslWrapper.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef SslWrapper_hpp
#define SslWrapper_hpp

#include <cstdint>
#include <vector>

#include "Url.hpp"
#include "Record.hpp"
#include "Connection.hpp"

using namespace std;

class SslWrapper {
private:
	const Url &url;
	unique_ptr<Connection> connection;
	void sendClientHello();
	pair<Record, Record> receiveServerHello();
	void sendClientCertificate(Record serverHello, Record serverCertificate);

	void receiveServerFinished();
	void sendData(vector<uint8_t> const& data);
	vector<uint8_t> receiveData();
	void sslSend(vector<Record> const& records);

public:
	SslWrapper(Url const& url);
	vector<uint8_t> get();
//    vector<uint8_t> post();
};

#endif /* SslWrapper_hpp */
