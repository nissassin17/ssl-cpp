//
//  strutil.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include "strutil.hpp"

#include <string>

#include "err.hpp"

using namespace std;

string StrUtil::getLink(int argc, const char * argv[]) const {

	if (argc == 1)
		throw Err(Err::NoLinkProvided);

	return string(argv[1]);
}
