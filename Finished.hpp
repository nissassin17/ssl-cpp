//
//  finished.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef finished_hpp
#define finished_hpp

#include <cstdint>
#include <iostream>
#include <vector>

#include "Exportable.hpp"
using namespace std;

class Finished: public Exportable {
public:
	enum SenderType {
		CLIENT, SERVER
	};
//TODO: implement finished server and client
	Finished();
	Finished(vector<uint8_t> const& data, size_t offset = 0);
	virtual size_t size() const;
	virtual vector<uint8_t> toData() const;

private:
	SenderType type;
	static const string CLIENT_STRING;
	static const string SERVER_STRING;
};

#endif /* finished_hpp */
