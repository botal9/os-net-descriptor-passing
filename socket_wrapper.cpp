//
// Created by vitalya on 27.05.19.
//

#include "socket_wrapper.h"
#include <cstring>
#include <stdexcept>


void error(const std::string &msg) {
    throw std::runtime_error(msg + ": " + strerror(errno));
}

socket_wrapper::socket_wrapper()
    : fd(socket(AF_UNIX, SOCK_SEQPACKET, 0))
{
    if (fd == -1) {
        error("Unable to create socket");
    }
}

socket_wrapper::socket_wrapper(int fd_)
    : fd(fd_)
{
}

socket_wrapper::socket_wrapper(socket_wrapper&& other) noexcept
    : fd(other.fd)
{
    other.fd = -1;
}

socket_wrapper::~socket_wrapper() {
    if (fd != -1) {
        close(fd);
    }
}

socket_wrapper& socket_wrapper::operator=(socket_wrapper&& other) noexcept {
    fd = other.fd;
    other.fd = -1;
    return *this;
}

void socket_wrapper::bind(sockaddr_un& address) {
    int ret = ::bind(fd, reinterpret_cast<sockaddr*>(&address), sizeof(address));
    if (ret == -1) {
        error("Unable to bind socket");
    }
}

void socket_wrapper::connect(sockaddr_un& address) {
    int ret = ::connect(fd, reinterpret_cast<sockaddr*>(&address), sizeof(sockaddr));
    if (ret == -1) {
        error("Unable to connect socket");
    }
}

void socket_wrapper::listen() {
    int ret = ::listen(fd, 10);
    if (ret == -1) {
        error("Unable to listen socket");
    }
}

socket_wrapper socket_wrapper::accept() {
    if (fd == -1) {
        error("Unable to accept socket");
    }
    int new_fd = ::accept(fd, nullptr, nullptr);
    return socket_wrapper(new_fd);
}

void socket_wrapper::send_fd(int fd_) {
    struct msghdr msg = {nullptr};
    char buf[CMSG_SPACE(sizeof(fd_))];
    memset(buf, 0, sizeof(buf));

    struct iovec io = {.iov_base = (void *) "", .iov_len = 1};
    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
    msg.msg_control = buf;
    msg.msg_controllen = sizeof(buf);

    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN(sizeof(fd_));

    memmove(CMSG_DATA(cmsg), &fd_, sizeof(fd_));

    msg.msg_controllen = cmsg->cmsg_len;

    if (sendmsg(fd, &msg, 0) < 0) {
        error("Unable to send file descriptor");
    }
}

int socket_wrapper::get_fd() {
    msghdr msg = {nullptr};
    cmsghdr* cmsghdr;
    char buffer[CMSG_SPACE(sizeof(int))];
    char copy[512];
    bzero(buffer, sizeof(buffer));
    iovec io = {.iov_base = &copy, .iov_len = sizeof(copy)};

    msg.msg_control = buffer;
    msg.msg_controllen = sizeof(buffer);
    msg.msg_iov = &io;
    msg.msg_iovlen = 1;
    if (recvmsg(fd, &msg, 0) < 0) {
        return -1;
    }

    cmsghdr = CMSG_FIRSTHDR(&msg);
    int ret_fd;
    memcpy(&ret_fd, (int *) CMSG_DATA(cmsghdr), sizeof(int));
    return ret_fd;
}
