//
// Created by vitalya on 09.06.19.
//

#ifndef OS_NET_DESCRIPTOR_PASSING_PIPE_H
#define OS_NET_DESCRIPTOR_PASSING_PIPE_H

#include <utility>

class pipe {
public:
    pipe() = default;

    pipe(const pipe& other) = delete;
    pipe& operator=(const pipe& other) = delete;

    void create();
    void close();

    std::pair<int, int> get_fd();

private:
    int fd[2] = {-1, -1};
};


#endif //OS_NET_DESCRIPTOR_PASSING_PIPE_H
