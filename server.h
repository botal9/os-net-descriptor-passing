//
// Created by vitalya on 19.05.19.
//

#ifndef OS_NET_SERVER_H
#define OS_NET_SERVER_H

#include "pipe.h"
#include "socket_wrapper.h"

#include <deque>
#include <string>
#include <sys/un.h>


class server {
public:
    server(char* socket_name);
    ~server();

    server(const server& other) = delete;
    server& operator=(const server& other) = delete;

    void start();

private:
    std::string server_address;
    socket_wrapper server_socket;

    class pipe pipe_in;
    class pipe pipe_out;
};


#endif //OS_NET_SERVER_H
