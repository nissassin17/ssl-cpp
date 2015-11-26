//
//  finished.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/6/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include "Finished.hpp"
using namespace std;

const string Finished::CLIENT_STRING = "client finished";
const string Finished::SERVER_STRING = "server finished";

size_t Finished::size() const{
	return 0;
}

vector<uint8_t> Finished::toData() const{
	vector<uint8_t> data;
	return data;
}

Finished::Finished() :
		type(CLIENT) {

}

Finished::Finished(const vector<uint8_t>& data, size_t offset):
	type(SERVER){
}
