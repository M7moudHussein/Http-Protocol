//
// Created by mahmoud on 11/5/18.
//

#ifndef HTTP_PROTOCOL_RESPONSE_SENDER_H
#define HTTP_PROTOCOL_RESPONSE_SENDER_H

#include "../models/response.h"

class response_sender {
public:
    response_sender(int socket_no);

    void send_response(response *res);

private:
    int socket_no;

};


#endif //HTTP_PROTOCOL_RESPONSE_SENDER_H
