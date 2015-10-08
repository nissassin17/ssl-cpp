//
//  connection.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef connection_hpp
#define connection_hpp

#include "SubConnection.hpp"
#include <vector>
using namespace std;

class Connection {
private:
	vector<SubConnection*> subConnections;
	static vector<string> ipListFromHostname(string hostname);
	SubConnection *activatingConnection;
	/* did this connection send first request. Because there are many sub connection (with 1 ip) insde. First request will check for avaibility and first successful sub connection will be assign to activatingConnection */
	bool isConnecting;
public:
	Connection(string hostname, bool isSsl);
	~Connection();
	void send(vector<uint8_t> request);
	vector<uint8_t> receive();
};

#endif /* connection_hpp */
