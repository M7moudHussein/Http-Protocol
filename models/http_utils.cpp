#include <asm/ioctls.h>
#include <sys/ioctl.h>
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

std::vector<size_t> http_utils::findHeaderEnds(std::string received_buffer) {
    std::vector<size_t> positions; // holds all the positions that sub occurs within str
    size_t pos = received_buffer.find(HEADERS_END);
    while (pos != std::string::npos) {
        positions.push_back(pos);
        pos = received_buffer.find(HEADERS_END, pos + 1);
    }
    return positions;
}

bool http_utils::is_closed(int socket_fd) {
    int n = 0;
    ioctl(socket_fd, FIONREAD, &n);
    return n == 0;
}