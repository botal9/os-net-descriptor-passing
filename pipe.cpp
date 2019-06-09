//
// Created by vitalya on 09.06.19.
//

#include "pipe.h"

#include <zconf.h>
#include <stdexcept>

void pipe::create() {
    int ret = ::pipe(fd);
    if (ret == -1) {
        throw std::runtime_error("Unable to create pipe");
    }
}

void pipe::close() {
    for (int tmp_fd : fd) {
        int ret = ::close(tmp_fd);
        if (ret == -1) {
            throw std::runtime_error("Unable to close pipe");
        }
    }
}

std::pair<int, int> pipe::get_fd() {
    return {fd[0], fd[1]};
}
