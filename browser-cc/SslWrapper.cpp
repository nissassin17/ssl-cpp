//
//  SslWrapper.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "SslWrapper.hpp"


#include <iostream>

#include "Connection.hpp"
#include "Handshake.hpp"
#include "Record.hpp"
#include "Util.hpp"
#include "Log.h"

SslWrapper::SslWrapper(const Url* url) :
url(url){
	this->connection = new Connection(url->getHostname(), url->isUseSsl());
}

vector<uint8_t> SslWrapper::get() {
	if (this->url->isUseSsl()) {
		Log::info << "Start requesting with ssl (it must be hard)" << endl;

		//prepare client hello
		Log::info << "Making a \"client_hello\" handshake message" << endl;
		Record *clientHello = new Record(Handshake::CLIENT_HELLO);

		//send it
		Log::info << "Send it (" << clientHello->size() << " bytes)" << endl;
		vector<uint8_t> tosend(clientHello->toData());
		this->connection->send(tosend);
//		cout << "Request:" << endl << Util::readableForm(tosend) << endl;


		//receive data
		Log::info << "Receive response" << endl;
		vector<uint8_t> data = this->connection->receive();
		Log::info << "Received data's total size: " << data.size() << " bytes" << endl;
//		cout << "Response:" << endl << Util::readableForm(data) << endl; //this is server hello message

		//this must be a server hello handshake record
		size_t offset(0);
		Log::info << "Make first record from server's response" << endl;
		Record *serverHello = new Record(data, offset);
		Log::info << "First record's size: " << serverHello->size() << " bytes" << endl;
		offset += serverHello->size();

		if (serverHello->getType() == Record::ALERT) {
			Log::err << "First record was an alert. The alert type: " << serverHello->getAlert()->what() << endl;
		} else if (serverHello->getType() == Record::HANDSHAKE) {
			Log::info << "First record was a handshake" << endl;

			vector<Record*> records;
			while (offset < data.size()) {
				Record *record = new Record(data, offset, serverHello->getHandshake());
				records.push_back(record);
				offset += record->size();
				Log::info << "One more record was parsed from server's response by " << record->size() << " bytes" << endl;
//					break; //TLS_RSA_WITH_AES_128_CBC_SHA256
            }
			//while(record->getHandshake()->getType()
                    //!= Handshake::SERVER_HELLO_DONE);
			if (records.size() == 2) {
				//one certificate and one hellodone

				vector<Record*> toSend;
				Log::info << "Make \"client_key_exchange\" record (hard)" << endl;
				toSend.push_back(
						new Record(Handshake::CLIENT_KEY_EXCHANGE,
								serverHello->getHandshake(),
								records[0]->getHandshake())
				);
				Log::info << "Make \"change_cipher_spec\" record (just by the sake of manner, actually there is no change need)"<<endl;
				toSend.push_back(new Record(Record::CHANGE_CIPHER_SPEC));
				Log::info << "Make \"finished\" record" << endl;
				toSend.push_back(new Record(Handshake::FINISHED));

				Log::info << "Send these 3 records to server" << endl;

			}else{
				Log::err << "Expect receiving 2 records (one certificate and one hellodone) from server, but did not" << endl;
			}
			for (int i = 0; i < records.size(); i++)
				delete records[i];

		} else
			Log::err << "Unexpected response from server" << endl;

		delete clientHello;
		delete serverHello;

		//prepare finished message
//        Record finished(data.)
		Log::warn << "Return empty result because of occurred error" << endl;

		return vector<uint8_t>();
	}
	Log::info << "Send request without using ssl" << endl;
	this->connection->send(this->url->httpGetRequest());
	return this->connection->receive();
}

SslWrapper::~SslWrapper() {
	delete this->connection;
}
