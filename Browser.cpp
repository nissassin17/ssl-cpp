//
//  browser.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "Browser.hpp"

#include "Log.h"
#include "SslWrapper.hpp"
#include "StrUtil.hpp"
#include "Url.hpp"
#include "BigNum.h"

using namespace std;

void Browser::run(int argc, const char * argv[]) {
//        Log::info << (BigNum(2).exponent(32, 100)).toVector() << endl;
//    return;
	Log::info << "Browser started." << endl;

	/* Read link from command */
	string link = StrUtil::getLink(argc, argv);
	Log::info << "Link to get: " << link << endl;

	/* Extract hostname and request */
	Url url = Url(link);
	Log::info << "Host name: " << url.getHostname() << endl;
	Log::info << "Request to send: " << url.getRequest() << endl;
	Log::info << "Is ssl used: " << (url.isUseSsl() ? "yes" : "no") << endl;

	SslWrapper ssl(url);

	Log::info << "Start fetch data" << endl;
	vector<uint8_t> getData = ssl.get();
	string result;
	for (int i = 0; i < getData.size(); i++)
		result += (char) getData[i];
	Log::info << "Result:" << endl;
	Log::result << result << endl;
	Log::info << "Browser ended" << endl;
}
