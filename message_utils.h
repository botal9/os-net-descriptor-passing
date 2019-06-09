//
// Created by vitalya on 09.06.19.
//

#ifndef OS_NET_DESCRIPTOR_PASSING_MESSAGE_UTILS_H
#define OS_NET_DESCRIPTOR_PASSING_MESSAGE_UTILS_H

#include <stdexcept>
#include <string>
#include <zconf.h>

void write_message(int fd, std::string message) {
    message += '\0';
    size_t ptr = 0;
    while (ptr < message.size()) {
        int len = write(fd, message.c_str() + ptr, message.size() - ptr);
        if (len == -1) {
            throw std::runtime_error("Unable to write data to file descriptor");
        }
        ptr += len;
    }
}

std::string read_message(int fd) {
    size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE + 1];

    std::string result;
    while (true) {
        int len = read(fd, buffer, BUFFER_SIZE);
        if (len == -1) {
            throw std::runtime_error("Unable to read data from file descriptor");
        }
        buffer[BUFFER_SIZE] = 0;
        if (!len)
            continue;
        result.append(buffer, len);
        if (buffer[len - 1] == 0) {
            result.pop_back();
            break;
        }
    }
    return result;
}

#endif //OS_NET_DESCRIPTOR_PASSING_MESSAGE_UTILS_H
