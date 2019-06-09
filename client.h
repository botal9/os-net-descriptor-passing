//
// Created by vitalya on 19.05.19.
//

#ifndef OS_NET_CLIENT_H
#define OS_NET_CLIENT_H

#include "socket_wrapper.h"

#include <string>

class client {
public:
    client(char* socket_name);
    ~client() = default;

    void start();

private:
    std::string server_address;
    socket_wrapper client_socket;
};

#endif //OS_NET_CLIENT_H
