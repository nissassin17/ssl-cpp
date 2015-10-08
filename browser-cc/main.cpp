//
//  main.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/1/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include <cstdlib>
#include <iostream>

#include "browser.hpp"
#include "err.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
	try {
		Browser *browser = new Browser();
		browser->run(argc, argv);
		delete browser;
		return EXIT_SUCCESS;
	} catch (Err &err) {
		cerr << err.what();
		if (err.isSuccess())
			return EXIT_SUCCESS;
		return EXIT_FAILURE;
	}
}
