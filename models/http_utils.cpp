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

std::vector<size_t> http_utils::findHeaderEnds(std::string recieved_buffer) {
    std::vector<size_t> positions; // holds all the positions that sub occurs within str
    size_t pos = recieved_buffer.find(HEADERS_END, 0);
    while(pos != std::string::npos)
    {
        positions.push_back(pos);
        pos = recieved_buffer.find(HEADERS_END,pos+1);
    }
    return positions;
}
