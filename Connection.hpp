//
//  connection.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef connection_hpp
#define connection_hpp

#include <cstdint>
#include <iostream>
#include <vector>

#include "SubConnection.hpp"

using namespace std;

class Connection {
private:
	vector<shared_ptr<SubConnection> > subConnections;
	static vector<string> ipListFromHostname(const string &hostname);
	shared_ptr<SubConnection> activatingConnection;
	/* did this connection send first request. Because there are many sub connection (with 1 ip) insde. First request will check for avaibility and first successful sub connection will be assign to activatingConnection */
	bool isConnecting;
public:
	Connection(const string& hostname, bool isSsl);
	void send(const vector<uint8_t> &request);
	vector<uint8_t> receive() const;
};

#endif /* connection_hpp */
