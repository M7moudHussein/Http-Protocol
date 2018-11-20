#include "http_utils.h"

std::string http_utils::get_content_type(std::string url) {
    std::string file_extension = url.substr(url.rfind('.') + 1);
    if (file_extension == "txt") {
        return "text/plain";
    } else if (file_extension == "html") {
        return "text/html";
    } else {
        return "image/" + file_extension;
    }

}
