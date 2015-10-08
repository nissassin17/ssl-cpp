//
//  finished.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "finished.hpp"

const string Finished::CLIENT_STRING = "client finished";
const string Finished::SERVER_STRING = "server finished";

size_t Finished::size() {
	return 0;
}

vector<uint8_t> Finished::toData() {
	vector<uint8_t> data;
	return data;
}

Finished::Finished(SenderType type) :
		type(type) {

}
