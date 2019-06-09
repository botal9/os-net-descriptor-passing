//
// Created by vitalya on 19.05.19.
//

#include "message_utils.h"
#include "server.h"

#include <cstring>
#include <iostream>

server::server(char* socket_name)
    : server_address(socket_name)
    , server_socket()
{
    struct sockaddr_un address;
    memset(&address, 0, sizeof(sockaddr_un));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, socket_name, sizeof(address.sun_path) - 1);

    server_socket.bind(address);
    server_socket.listen();
}

void server::start() {
    std::cout << "Echo server started!\n" << std::endl;

    socket_wrapper client_socket = server_socket.accept();
    pipe_in.create();
    pipe_out.create();

    client_socket.send_fd(pipe_in.get_fd().first);
    client_socket.send_fd(pipe_out.get_fd().second);
    std::cout << "Client connected\n" << std::endl;

    int in_fd = pipe_out.get_fd().first;
    int out_fd = pipe_in.get_fd().second;
    while (true) {
        std::string msg = read_message(in_fd);
        std::cout << "Server got: " + msg << std::endl;

        write_message(out_fd, msg);
        std::cout << "Server sent: " + msg + "\n" << std::endl;

        if (msg == "SHUTDOWN") {
            std::cout << "Server down" << std::endl;
            break;
        }
    }
}

server::~server() {
    pipe_in.close();
    pipe_out.close();
    unlink(server_address.c_str());
}
