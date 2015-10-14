//
//  strutil.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include <string>

#include "StrUtil.hpp"
#include "Err.hpp"

using namespace std;

string StrUtil::getLink(int argc, const char * argv[]){

	if (argc == 1)
		throw Err(Err::NoLinkProvided);

	return string(argv[1]);
}
