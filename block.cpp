
#include <iostream>
#include <random>
#include "headers/block.hpp"


block::block(size_t boardWidth, size_t boardHeight) :
    boardWidth(boardWidth), boardHeight(boardHeight) {
    // pick random block (7 options)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0,6);
    int randInt = distribution(gen);

    pos = {(boardWidth/2)-1,0};
    char block = blocks[randInt];
    colour = colours[randInt];

    // block chars is different for every piece
    switch (block) {
        case 'I':
            width = 1;
            height = 4;
            blockChars = {colour,colour,colour,colour};
            break;
        case 'O':
            width = 2;
            height = 2;
            blockChars = {colour,colour,colour,colour};
            break;
        case 'T':
            width = 2;
            height = 3;
            blockChars = {colour,'0',colour,colour,colour,'0'};
            break;
        case 'S':
            width = 2;
            height = 3;
            blockChars = {colour,'0',colour,colour,'0',colour};
            break;
        case 'J':
            width = 2;
            height = 3;
            blockChars = {'0',colour,'0',colour,colour,colour};
            break;
        case 'Z':
            width = 2;
            height = 3;
            blockChars = {'0',colour,colour,colour,colour,'0'};
            break;
        case 'L':
            width = 2;
            height = 3;
            blockChars = {colour, '0',colour,'0',colour,colour};
            break;
        default:
            break;
    }
}

std::vector<std::vector<char>> block::drawOnBoard(std::vector<std::vector<char>> board) {
    for (int i = 0; i < height;i++) {
        for (int j = 0; j < width; j++) {
            if (blockChars[i*width+j]!='0') {
                board[pos.second + i][pos.first + j] = blockChars[i * width + j];
            }
        }
    }
    return board;
}

bool block::canMoveDown(const std::vector<std::vector<char>>& board) const {
    // check that block stays in the board
    if (pos.second+height >= boardHeight){
        return false;
    }
    // check that underneath every column there is an empty space
    for (size_t i = 0; i < width;i++) {
        for (int j = static_cast<int>(height)-1;j>=0;j--) {
            if (blockChars[j*width+i] != '0') {
                if (board[pos.second+j+1][pos.first+i] != '0') {
                    return false;
                } else {
                    break;
                }

            }
        }
    }
    return true;
}

void block::moveDown(const std::vector<std::vector<char>>& board) {
    if (canMoveDown(board)) {
        pos.second++;
    }
}

bool block::canMoveRight(const std::vector<std::vector<char>>& board) const {
    if (pos.first+width >= boardWidth) return false;

    // check that next to every line there is an empty space
    for (size_t i = 0; i < height;i++) {
        for (int j = static_cast<int>(width)-1;j>=0;j--) {
            if (blockChars[i*width+j] != '0') {
                if (board[pos.second+i][pos.first+j+1] != '0') {
                    return false;
                } else {
                    break;
                }

            }
        }
    }
    return true;
}

void block::moveRight(const std::vector<std::vector<char>>& board) {
    if (canMoveRight(board)) {
        pos.first++;
    }
}

bool block::canMoveLeft(const std::vector<std::vector<char>>& board) const {
    if (pos.first <= 0) return false;
    // check that next to every line there is an empty space
    for (size_t i = 0; i < height;i++) {
        for (int j = 0;j<width;j++) {
            if (blockChars[i*width+j] != '0') {
                if (board[pos.second+i][pos.first+j-1] != '0') {
                    return false;
                } else {
                    break;
                }

            }
        }
    }
    return true;
}

void block::moveLeft(const std::vector<std::vector<char>>& board) {
    if (canMoveLeft(board)) {
        pos.first--;
    }
}

bool block::canRotate(const std::vector<std::vector<char>> &board) {
    size_t rotatedWidth = height;
    size_t rotatedHeight = width;
    std::vector<char> rotated;
    for (int i = (int)width-1; i >= 0; i--) {
        for (int j =  0; j < height; j++) {
            rotated.push_back(blockChars[j*width+i]);
        }
    }

    if (colour == 'c') return canRotateI(board,rotated);

    // move left in case it is needed and possible

    if (pos.first+rotatedWidth > boardWidth) {
        if (canMoveLeft(board)) {
            moveLeft(board);
        } else {
            return false;
        }
    }
    if (pos.second+rotatedHeight > boardHeight) {
        return false;
    }

    // check if the game board has empty space for the rotated piece

    for (size_t i = 0; i < rotatedHeight;i++) {
        for (size_t j = 0; j < rotatedWidth; j++) {
            if (rotated[i*rotatedWidth+j] != '0') {
                if (board[pos.second+i][pos.first+j] != '0') {
                    return false;
                }
            }
        }
    }
    return true;
}


void block::rotate(const std::vector<std::vector<char>> &board) {
    if (canRotate(board)) {
        std::vector<char> rotated;
        for (size_t i = 0; i < width; i++) {
            for (int j = static_cast<int>(height) - 1; j >= 0; j--) {
                rotated.push_back(blockChars[j * width + i]);
            }
        }
        blockChars = rotated;
        auto tmp = width;
        width = height;
        height = tmp;
    }
}


bool block::canRotateI(const std::vector<std::vector<char>> &board,std::vector<char> rotated) {

    // move left in case it is needed and possible
    size_t stepsNeeded;
    if ((pos.first + height > boardWidth)) {
        stepsNeeded = pos.first + height - boardWidth;
    } else {
        stepsNeeded = 0;
    }
    for (size_t i = 0; i<stepsNeeded;i++) {
        for (int j = 0; j<width;j++) {
            if (board[pos.second+j][pos.first-(i+1)] != '0') {
                return false;
            }
        }
    }
    for (int i = 0; i < stepsNeeded;i++) {
        moveLeft(board);
    }

    // check if the game board has empty space for the rotated piece

    for (size_t i = 0; i < width;i++) {
        for (size_t j = 0; j < height; j++) {
            if (rotated[i*height+j] != '0') {
                if (board[pos.second+i][pos.first+j] != '0') {
                    return false;
                }
            }
        }
    }
    return true;
}

std::pair<size_t, size_t> block::getPos() {
    return pos;
}

void block::setPos(std::pair<size_t, size_t> newPos) {
    pos = newPos;
}

size_t block::getHeight() const {
    return height;
}

size_t block::getWidth() const {
    return width;
}

std::vector<char> block::getBlockChars() {
    return blockChars;
}
