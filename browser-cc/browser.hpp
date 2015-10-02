//
//  browser.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef browser_hpp
#define browser_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "strutil.hpp"
#include "err.hpp"
#include "url.hpp"

using namespace std;

class Browser{
public:
    void run(int argc, const char * argv []);
};

#endif /* browser_hpp */
