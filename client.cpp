//
// Created by vitalya on 19.05.19.
//

#include "client.h"
#include "message_utils.h"

#include <cstring>
#include <iostream>

client::client(char* socket_name)
    : server_address(socket_name)
    , client_socket()
{
    struct sockaddr_un address;
    memset(&address, 0, sizeof(sockaddr_un));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, socket_name, sizeof(address.sun_path) - 1);

    client_socket.connect(address);
    std::cout << "Connected to server" << std::endl;
}

void client::start() {
    int in_fd = client_socket.get_fd();
    int out_fd = client_socket.get_fd();

    while (true) {
        std::string msg;
        std::cin >> msg;
        if (msg == "exit" || std::cin.eof()) {
            break;
        }
        write_message(out_fd, msg);
        std::cout << "Client sent: " + msg << std::endl;

        std::string answer = read_message(in_fd);
        std::cout << "Client got: " + answer << "\n" << std::endl;
    }
}
