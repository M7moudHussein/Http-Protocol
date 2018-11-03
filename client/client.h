//
// Created by salma on 11/3/18.
//

#ifndef HTTP_PROTOCOL_CLIENT_H
#define HTTP_PROTOCOL_CLIENT_H


class client {
public:
    bool establish_connection();

    void send_request();

    void recieve_data();

    void send_data();
};


#endif //HTTP_PROTOCOL_CLIENT_H
