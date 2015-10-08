//
//  finished.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef finished_hpp
#define finished_hpp

#include <sys/_types/_size_t.h>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

class Finished {
public:
	enum SenderType {
		CLIENT, SERVER
	};

	Finished(SenderType type);
	size_t size();
	vector<uint8_t> toData();

private:
	SenderType type;
	static const string CLIENT_STRING;
	static const string SERVER_STRING;
};

#endif /* finished_hpp */
