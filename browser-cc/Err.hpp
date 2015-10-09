//
//  err.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef err_hpp
#define err_hpp

#include <iostream>
#include <stdexcept>

using namespace std;

class Err: public runtime_error {

public:
	enum ErrType {
		Success = 0,
		NoLinkProvided,
		UnsupportedSchema,
		NoHostnameProvided,
		CannotCreateSock,
		CannotConnect,
		CannotSend,
		CannotReceive,
		CannotResolveHostname,
		NoConnection,
		DontSendButReceive,
		DECODING
	};

	Err(ErrType errType, ...);

	bool isSuccess() const;

	virtual const char* what() ;

private:
	ErrType errType;
	string description;

};

#endif /* err_hpp */
