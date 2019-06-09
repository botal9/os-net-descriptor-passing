//
// Created by vitalya on 27.05.19.
//

#ifndef OS_NET_SOCKET_WRAPPER_H
#define OS_NET_SOCKET_WRAPPER_H

#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <zconf.h>

class socket_wrapper {
public:
    socket_wrapper();
    socket_wrapper(const socket_wrapper& other) = delete;
    socket_wrapper(socket_wrapper&& other) noexcept;
    ~socket_wrapper();

    socket_wrapper& operator=(const socket_wrapper& other) = delete;
    socket_wrapper& operator=(socket_wrapper&& other) noexcept;

    void bind(sockaddr_un& address);
    void connect(sockaddr_un& address);
    void listen();
    socket_wrapper accept();

    void send_fd(int fd_);
    int get_fd();

private:
    explicit socket_wrapper(int fd_);

private:
    int fd;
};


#endif //OS_NET_SOCKET_WRAPPER_H
