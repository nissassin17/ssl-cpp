//
//  exportable.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef exportable_hpp
#define exportable_hpp

#include <sys/_types/_size_t.h>
#include <cstdint>
#include <vector>

using namespace std;

class Exportable {
public:
	virtual vector<uint8_t> toData() const;
	virtual size_t size() const;
	virtual ~Exportable();
};

#endif /* exportable_hpp */
