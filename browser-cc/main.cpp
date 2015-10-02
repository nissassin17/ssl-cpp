//
//  main.cpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/1/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#include <iostream>
#include "browser.hpp"
#include "err.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    try{
    Browser browser;
        browser.run(argc, argv);
        return EXIT_SUCCESS;
    }catch (Err err){
        cerr << err.getDescription();
        if (err.isSuccess())
            return EXIT_SUCCESS;
        return EXIT_FAILURE;
    }
}
