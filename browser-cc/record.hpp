//
//  record.hpp
//  browser-cc
//
//  Created by Nissassin Seventeen on 10/2/15.
//  Copyright © 2015 Nissassin Seventeen. All rights reserved.
//

#ifndef record_hpp
#define record_hpp

#include "protocol-version.hpp"
#include "handshake.hpp"

#include <stdio.h>

class Record : public Exportable{
public:
    enum ContentType {
        CHANGE_CIPHER_SPEC = 20,
        ALERT = 21,
        HANDSHAKE = 22,
        APPLICATION_DATA = 23,
        NONE = 24
    };
    Record();
    Record(vector<uint8_t> data, size_t offset = 0);
    vector<uint8_t> toData();
    size_t size();
    ~Record();

private:
    ContentType type;
    ProtocolVersion protocolVersion;
    Handshake *handshake;
    bool isCompress;
    
    static const int CONTENT_TYPE_LENGTH = 1;
    static const int BODY_LENGTH_LENGTH = 2;

};

#endif /* record_hpp */
