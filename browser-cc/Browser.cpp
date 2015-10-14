//
//  browser.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "Browser.hpp"
#include "SslWrapper.hpp"
#include "StrUtil.hpp"
#include "Url.hpp"

using namespace std;

void Browser::run(int argc, const char * argv[]) {

	/* Read link from command */
	string link = StrUtil::getLink(argc, argv);

	/* Extract hostname and request */
	Url url = Url(link);

	SslWrapper ssl = SslWrapper(&url);

	vector<uint8_t> getData = ssl.get();
	string result;
	for (int i = 0; i < getData.size(); i++)
		result += (char) getData[i];
	cout << result;
}
