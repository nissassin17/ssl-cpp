//
//  SslWrapper.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include "SslWrapper.hpp"

#include <iostream>

#include "Connection.hpp"
#include "Handshake.hpp"
#include "Log.h"
#include "Record.hpp"
#include "Util.hpp"

SslWrapper::SslWrapper(Url const& url):
		url(url) {
	this->connection.reset( new Connection(url.getHostname(), url.isUseSsl()));
}

void SslWrapper::sendClientHello() {
	//prepare client hello
	Log::info << "Making a \"client_hello\" handshake message" << endl;
	Record clientHello(Handshake::CLIENT_HELLO);

	//send it
	Log::info << "Send it" << endl;
	sslSend(vector<Record>(1, clientHello));
}

/**
 @return: serverhello and Certificate (from server)
 */
pair<Record, Record> SslWrapper::receiveServerHello() {
	Log::info << "Receive response" << endl;
	vector<uint8_t> data = this->connection->receive();
	Log::info << "Received data's total size: " << data.size() << " bytes"
			<< endl;
	//		cout << "Response:" << endl << Util::readableForm(data) << endl; //this is server hello message

	//this must be a server hello handshake record
	size_t offset(0);
	Log::info << "Make first record from server's response" << endl;
	Record serverHello(data, offset);
	Log::info << "First record's size: " << serverHello.size() << " bytes"
			<< endl;
	offset += serverHello.size();

	if (serverHello.getType() == Record::ALERT) {
		throw("First record was an alert. The alert type: "
				+ serverHello.getAlert()->what());
	} else if (serverHello.getType() == Record::HANDSHAKE) {
		Log::info << "First record was a handshake" << endl;

		vector<Record> records;
		while (offset < data.size()) {
			Record record(data, offset, serverHello.getHandshake().get());
			records.push_back(record);
			offset += record.size();
			Log::info << "One more record was parsed from server's response by "
					<< record.size() << " bytes" << endl;
			//					break; //TLS_RSA_WITH_AES_128_CBC_SHA256
		}
		if (records.empty())
			throw "Did not received Certitficate from server, only server hello was sent";
		if (records.rbegin()->getHandshake()->getType()
				!= Handshake::SERVER_HELLO_DONE)
			Log::warn << "Did not received SERVER_HELLO_DONE from server"
					<< endl;
		return make_pair(serverHello, records[0]);
	}
	throw "First record type was not alert type nor handshake type";
	//while(record->getHandshake()->getType()
	//!= Handshake::SERVER_HELLO_DONE);
}

void SslWrapper::sendClientCertificate(Record serverHello,
		Record serverCertificate) {
	Record clientKeyExchange(Handshake::CLIENT_KEY_EXCHANGE,
			serverHello.getHandshake().get(), serverCertificate.getHandshake().get());
	Log::info
			<< "Make \"change_cipher_spec\" record (just by the sake of manner, actually there is no change need)"
			<< endl;
	Record changeCipherSpec(Record::CHANGE_CIPHER_SPEC);
	Log::info << "Make \"finished\" record" << endl;
	Record finished(Handshake::FINISHED);
	Log::info << "Send these 3 records to server" << endl;
    
    vector<uint8_t> toSend;
    Util::addData(toSend, clientKeyExchange.toData());
    Util::addData(toSend, changeCipherSpec.toData());
    Util::addData(toSend, finished.toData());
    this->connection->send(toSend);
}

vector<uint8_t> SslWrapper::get() {
	if (this->url.isUseSsl()) {
		Log::info << "Start requesting with ssl (it must be hard)" << endl;

        /*
      Client                                               Server

      ClientHello                  ----1---->
                                                      ServerHello
                                                     Certificate*
                                               ServerKeyExchange*
                                              CertificateRequest*
                                   <---2-----      ServerHelloDone
      Certificate*
      ClientKeyExchange
      CertificateVerify*
      [ChangeCipherSpec]
      Finished                     ----3---->
                                               [ChangeCipherSpec]
                                   <---4-----             Finished
      Application Data             <---5---->     Application Data
         */

		//phrase 1
		sendClientHello();

		//phrase 2
		//receive data

		try {
			pair<Record, Record> records = receiveServerHello();
			Record &serverCertificate = records.second;
			Record &serverHello = records.first;
			Log::info << "Make \"client_key_exchange\" record (hard)" << endl;
			//phrase 3
			sendClientCertificate(serverHello, serverCertificate);
            throw string("Deadline is coming. So that I stop here");
            
            //phrase 4: receive finished message
			try{
            receiveServerFinished();
            //phrase 5: send request
            sendData(url.httpGetRequest());
            //phrase 6: receive data
            return receiveData();
            }catch (string const& msg){
            	Log::err << msg << endl;
            }
		} catch (string const& err) {
			Log::err << err << endl;
		}
		Log::warn << "Return empty result because of occurred error" << endl;
		return vector<uint8_t>();
	}
    
	Log::info << "Send request without using ssl" << endl;
	this->connection->send(this->url.httpGetRequest());
	return this->connection->receive();
}

void SslWrapper::receiveServerFinished() {
	vector<uint8_t> data = connection->receive();
	int offset(0);
	Record finished(data, offset);
	offset += finished.size();

	if (finished.getType() == Record::CHANGE_CIPHER_SPEC){
		Log::warn << "Server requires CHANGE_CIPHER_SPEC" << endl;
		if (offset < data.size()){
			Record ff(data, offset);
			if (ff.getType() == Record::HANDSHAKE and ff.getHandshake()->getType() == Handshake::FINISHED){
				Log::info << "But finally still got a finished message" << endl;
			}
		}
		throw "Server require CHANGE_CIPHER_SPEC";
	}else
		if (finished.getType() == Record::HANDSHAKE and finished.getHandshake()->getType() == Handshake::FINISHED)
	{
		Log::info << "Received a FINISHED message from server" << endl;
	}
	throw "Did not receive FINSHED nor CHANGE_CIPHER_SPEC message from server";
}

void SslWrapper::sendData(const vector<uint8_t>& data) {
	Log::info << "Send APPLICATION_DATA" << endl;
	Record appData(Record::APPLICATION_DATA, data);
	sslSend(vector<Record>(1, appData));
}

vector<uint8_t> SslWrapper::receiveData() {
	Log::info << "Get application data" << endl;
	Record appData(connection->receive());
	if (appData.getType() == Record::APPLICATION_DATA){
		return appData.getApplicationData()->getData();
	}
	throw "Did not receive a APPLICATION_DATA record from server";
}

void SslWrapper::sslSend(const vector<Record>& records) {
	vector<uint8_t> tosend;
	for(int i = 0; i < records.size(); i++){
		Log::info << "Record " << i << ": " << records[i].size() << " bytes" << endl;
		Util::addData(tosend, records[i].toData());
	}
	Log::info << "Send total " << tosend.size() << " bytes (" << records.size() << " records)" << endl;
	this->connection->send(tosend);
}
