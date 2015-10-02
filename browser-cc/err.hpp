//
//  err.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef err_hpp
#define err_hpp

#include <stdio.h>
#include <string>

using namespace std;

class Err : runtime_error {
    
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
        DontSendButReceive
    };

    Err(ErrType errType, ...);
    
    bool isSuccess();
    
    string getDescription();
    
private:
    ErrType errType;
    string description;

};

#endif /* err_hpp */
