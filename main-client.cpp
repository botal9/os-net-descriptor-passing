//
// Created by vitalya on 19.05.19.
//

#include "client.h"

#include <functional>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Address argument expected" << std::endl;
        return EXIT_FAILURE;
    }
    try {
        client client(argv[1]);
        std::cout << "This is echo client. Send something to the server and it will return back.\n"
                     "Type \"SHUTDOWN\" to shutdown, type \"exit\" to exit.\n" << std::endl;
        client.start();
        std::cout << "Exited" << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
