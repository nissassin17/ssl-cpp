//
//  main.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/1/15.
//  Copyright (c) 2015 Nissassin Seventeen. All rights reserved.
//

#include <cstdlib>
#include <iostream>

#include "Browser.hpp"
#include "Err.hpp"
#include "Log.h"

using namespace std;

/**
 * Usage: ./browser <full link to get>
 * Example (no ssl): ./browser http://stackoverflow.com/questions
 * Or (use ssl): ./browser https://google.com
 */
int main(int argc, const char * argv[]) {
	try {
		Browser browser;
		browser.run(argc, argv);
		return EXIT_SUCCESS;
	} catch (Err &err) {
		Log::err << err.what();
		if (err.isSuccess()) {
			return EXIT_SUCCESS;
		}
		return EXIT_FAILURE;
	}
}
