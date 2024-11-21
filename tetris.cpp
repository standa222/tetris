#include <iostream>
#include <thread>
#include <cstring>

#include "headers/tetris.hpp"

double power(double base, int power) {
    double result = base;
    for (int i = 0; i<power;i++) {
        result *= base;
    }
    return result;
}

tetris::tetris(size_t width, size_t height, int level) :
    quit(false),
    width(width),
    height(height),
    score(0), updateCounter(0), lines(0), level(level), initialLevel(level) {

    currentBlock = new block(width,height);
    nextBlock = new block(width,height);
    window = std::make_unique<Window>(std::cout,width,height);
    std::vector<char> innerVec;
    for (size_t row = 0;row < height;row++) {
        innerVec = {};
        for (size_t column = 0; column < width; column++) {
            innerVec.push_back('0');
        }
        board.push_back(innerVec);
    }
}

// destructor to delete dynamically allocated currentBlock

tetris::~tetris() {
    delete currentBlock;
    delete nextBlock;
}

void tetris::output() {
    std::unique_lock<std::mutex> lg(mutex);
    cvar.wait(lg);
    window->redraw(board,currentBlock, score,level,lines,quit,nextBlock);
}

void tetris::input() {
    std::unique_lock<std::mutex> lg(mutex);
    lg.unlock();
    if (quit)
        return;

    char c[3];

    std::cin>>c[0];

    if (c[0]==27) {
        std::cin>>c[1]>>c[2];
    }

    switch (int(c[0])) {
        case 'q':
            quit = true;
            break;
        case 'a':
            currentBlock->moveLeft(board);
            break;
        case 's':
            currentBlock->moveDown(board);
            break;
        case 'd':
            currentBlock->moveRight(board);
            break;
        case 'w':
            currentBlock->rotate(board);
            break;
        case 27: // arrow key was pressed;
            switch(c[2]) {
                case ARROW_KEY_LEFT:
                    currentBlock->moveLeft(board);
                    break;
                case ARROW_KEY_DOWN:
                    currentBlock->moveDown(board);
                    break;
                case ARROW_KEY_RIGHT:
                    currentBlock->moveRight(board);
                    break;
                case ARROW_KEY_UP:
                    currentBlock->rotate(board);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    cvar.notify_one();
}

void tetris::update() {
    // the game updates the faster, the higher the level is
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(PERIOD * power(0.90,level))));
    std::unique_lock<std::mutex> lg(mutex);
    updateCounter++;
    // base move down every 5 updates
    if (updateCounter>=5) {
        if (!currentBlock->canMoveDown(board)) {
            board = currentBlock->drawOnBoard(board);
            // game is over if the first row is not empty
            for (char c : board[0]) {
                if (c != '0') {
                    quit = true;
                    cvar.notify_one();
                }
            }
            checkFullLines();
            delete currentBlock;
            currentBlock = nextBlock;
            nextBlock = new block(width,height);

        } else {
            currentBlock->moveDown(board);
        }
        updateCounter = 0;
    }
    cvar.notify_all();
}

bool tetris::isGameOver() const {
    return quit;
}

void tetris::checkFullLines() {
    bool lineFull = true;
    int linesCleared = 0;
    for (size_t row = 0; row < height; row++) {
        lineFull = true;
        for (auto c : board[row] ) {
            if (c == '0') {
                lineFull = false;
                break;
            }
        }
        if (lineFull) {
            clearLineAndInsertNew(row);
            linesCleared++;
        }
    }
    addPoints(linesCleared);
    level = (lines / 5) + initialLevel;
}

void tetris::clearLineAndInsertNew(size_t row) {
    board.erase(board.begin()+row);
    std::vector<char> newLine;
    for (size_t i = 0;i<width;i++) newLine.push_back('0');
    board.insert(board.begin(),newLine);
}

void tetris::addPoints(int linesCleared) {
    lines += linesCleared;
    switch (linesCleared) {
        case 1:
            score += (level+1)*40;
            break;
        case 2:
            score += (level+1)*100;
            break;
        case 3:
            score += (level+1)*300;
            break;
        case 4:
            score += (level+1)*1200;
            break;
        default:
            break;
    }

}

void tetris::setBoard(const std::vector<std::vector<char>> &board) {
    tetris::board = board;
}

int tetris::getScore() const {
    return score;
}
