#ifndef HTTP_PROTOCOL_RESPONSE_H
#define HTTP_PROTOCOL_RESPONSE_H


#include <string>

enum Status_code {
    CODE_404,
    CODE_200
};

class response {
public:
    static response RESPONSE_200;
    static response RESPONSE_404;

    void set_status(Status_code code);

    Status_code get_status();

    char *to_string();

    void build(std::string res_msg);

    size_t get_length();

    void set_body(char *body, int body_length);

    char *get_body();

    int get_body_length();

    void set_http_version(std::string http_version);

    std::string get_http_version();

private:
    static const char CARRIAGE_RETURN = '\r';
    static const char NEW_LINE = '\n';

    Status_code status_code;
    char *response_body;
    int body_length;
    std::string http_version;
};


#endif
