#include <iostream>
#include <thread>

#include "headers/arguments.hpp"
#include "headers/constants.hpp"
#include "headers/window.hpp"
#include "headers/tetris.hpp"


void set_raw(bool set) {
    if (set) {
        system("stty raw");  // enable raw
    } else {
        system("stty -raw"); // disable raw
    }
}

int main(int argc, char *argv[]) {
    auto computeThread = [](tetris& tetris) {
        bool q = false;
        while (!q) {
            tetris.update();
            q = tetris.isGameOver();
        }
    };
    auto outputThread = [](tetris& tetris) {
        bool q = false;
        while (!q) {
            tetris.output();
            q = tetris.isGameOver();
        }
    };
    auto inputThread = [](tetris& tetris) {
        bool q = false;
        while (!q) {
            tetris.input();
            q = tetris.isGameOver();
        }
    };

    set_raw(true);
    std::cout << "\e[8;"
                 "40;100t";  // set terminal window to a certain size

    auto inputArgs = ArgParser::parseInputArgs(argc, argv);
    tetris tetris(inputArgs.width, inputArgs.height, inputArgs.level);
    std::thread t1(computeThread, std::ref(tetris));
    std::thread t2(outputThread, std::ref(tetris));
    std::thread t3(inputThread, std::ref(tetris));

    t1.join();
    t2.join();
    t3.join();
    set_raw(false);

    return 0;
}


