#include <iostream>

#include "headers/window.hpp"
#include "headers/block.hpp"

Window::Window(std::ostream &outputStream, size_t width, size_t height) :
        outputStream(outputStream),
        width(width),
        height(height) { }

void Window::redraw(std::vector<std::vector<char>> board, block* currentBlock, int score, int level, int lines, bool quit, block* nextBlock) {
    board = currentBlock->drawOnBoard(board);
    outputStream << ANSI_CLEAR << COLOR_RESET;
    printTetris();
    drawBoard(board,score,level,lines, quit, nextBlock);
    outputStream<<std::endl;
}

void Window::drawBoard(const std::vector<std::vector<char>>& board,int score, int level, int lines, bool quit, block* nextBlock) {
    for (size_t row = 0; row < height; row++) {
        outputStream<<"           " SIDE_LINE;
        for (char c : board[row]) {
            switch (c) {
                case 'c':
                    outputStream<<COLOR_CYAN BLOCK_CHAR COLOR_RESET;
                    break;
                case 'y':
                    outputStream<<COLOR_YELLOW BLOCK_CHAR COLOR_RESET;
                    break;
                case 'p':
                    outputStream<<COLOR_PURPLE BLOCK_CHAR COLOR_RESET;
                    break;
                case 'g':
                    outputStream<<COLOR_GREEN BLOCK_CHAR COLOR_RESET;
                    break;
                case 'b':
                    outputStream<<COLOR_BLUE BLOCK_CHAR COLOR_RESET;
                    break;
                case 'r':
                    outputStream<<COLOR_RED BLOCK_CHAR COLOR_RESET;
                    break;
                case 'o':
                    outputStream<<COLOR_ORANGE BLOCK_CHAR COLOR_RESET;
                    break;
                default:
                    outputStream<<" ";
            }

        }
        outputStream<<SIDE_LINE;
        if (row == 0 && quit) {
            outputStream<< "     " COLOR_YELLOW_BG " G A M E   O V E R " COLOR_RESET;
        }

        if (row == 3) {
            outputStream<< "     " COLOR_PURPLE_BG " NEXT BLOCK: " COLOR_RESET;
        }

        printNextBlock(nextBlock,row);

        if (row == 10) {
            outputStream<<  "     " COLOR_RED_BG " SCORE: " << score <<" " COLOR_RESET;
        }
        if (row == 12) {
            outputStream<< "     " COLOR_GREEN_BG " LINES: " << lines << " " COLOR_RESET;
        }
        if (row == 14) {
            outputStream<<  "     " COLOR_BLUE_BG " LEVEL: " << level << " " COLOR_RESET;
        }
        outputStream<<"\n\r";
    }

    outputStream<<"           " LEFT_BOTTOM_CORNER_CHAR;
    for (size_t column = 0;column<width;column++) outputStream<<BOTTOM_LINE;
    outputStream<<RIGHT_BOTTOM_CORNER_CHAR "\n\r";
}

void Window::printTetris() {
    outputStream << "\n" COLOR_RED BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR " " COLOR_ORANGE BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR " " COLOR_YELLOW BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR " " COLOR_GREEN BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR "   " COLOR_BLUE BLOCK_CHAR "   " COLOR_PURPLE BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR "\n\r";
    outputStream << "  " COLOR_RED BLOCK_CHAR "   " COLOR_ORANGE BLOCK_CHAR "     " COLOR_YELLOW "  " BLOCK_CHAR "   " COLOR_GREEN BLOCK_CHAR "   " BLOCK_CHAR "  " COLOR_BLUE BLOCK_CHAR "  " COLOR_PURPLE BLOCK_CHAR "\n\r";
    outputStream << "  " COLOR_RED BLOCK_CHAR "   " COLOR_ORANGE BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR  " " COLOR_YELLOW "  " BLOCK_CHAR "   " COLOR_GREEN BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR " " COLOR_BLUE "  " BLOCK_CHAR "   " COLOR_PURPLE BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR "\n\r";
    outputStream << "  " COLOR_RED BLOCK_CHAR "   " COLOR_ORANGE BLOCK_CHAR "     " COLOR_YELLOW "  " BLOCK_CHAR "   " COLOR_GREEN BLOCK_CHAR "   " BLOCK_CHAR "  " COLOR_BLUE  BLOCK_CHAR "      " COLOR_PURPLE BLOCK_CHAR "\n\r";
    outputStream << "  " COLOR_RED BLOCK_CHAR "   " COLOR_ORANGE BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR " " COLOR_YELLOW "  " BLOCK_CHAR "   " COLOR_GREEN BLOCK_CHAR "   " BLOCK_CHAR "  " COLOR_BLUE  BLOCK_CHAR "  " COLOR_PURPLE BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR  "\n\r";

    outputStream << COLOR_RESET "\n\n";
}

void Window::printNextBlock(block *nextBlock, int row) {
    switch (nextBlock->colour) {
        case 'c':
            if (row >= 5 && row <= 8) {
                outputStream<< "     " COLOR_CYAN BLOCK_CHAR COLOR_RESET;
            }
            break;
        case 'y':
            if (row == 5 || row == 6) {
                outputStream<< "     " COLOR_YELLOW BLOCK_CHAR BLOCK_CHAR COLOR_RESET;
            }
            break;
        case 'p':
            if (row== 5 || row == 7) {
                outputStream<< "     " COLOR_PURPLE BLOCK_CHAR " " COLOR_RESET;
            }
            if (row == 6) {
                outputStream<< "     " COLOR_PURPLE BLOCK_CHAR BLOCK_CHAR COLOR_RESET;
            }
            break;
        case 'g':
            if (row == 5) {
                outputStream<< "     " COLOR_GREEN BLOCK_CHAR " " COLOR_RESET;
            }
            if (row == 6) {
                outputStream<< "     " COLOR_GREEN BLOCK_CHAR BLOCK_CHAR COLOR_RESET;
            }
            if (row == 7) {
                outputStream<< "     " COLOR_GREEN " " BLOCK_CHAR COLOR_RESET;
            }
            break;
        case 'b':
            if (row == 5 || row == 6) {
                outputStream<< "     " COLOR_BLUE " " BLOCK_CHAR COLOR_RESET;
            }
            if (row == 7) {
                outputStream<< "     " COLOR_BLUE BLOCK_CHAR BLOCK_CHAR COLOR_RESET;
            }
            break;
        case 'r':\
        if (row == 5) {
                outputStream<< "     " COLOR_RED " " BLOCK_CHAR COLOR_RESET;
            }
            if (row == 6) {
                outputStream<< "     " COLOR_RED BLOCK_CHAR BLOCK_CHAR COLOR_RESET;
            }
            if (row == 7) {
                outputStream<< "     " COLOR_RED BLOCK_CHAR " " COLOR_RESET;
            }
            break;
        case 'o':
            if (row == 5 || row == 6) {
                outputStream<< "     " COLOR_ORANGE BLOCK_CHAR " " COLOR_RESET;
            }
            if (row == 7) {
                outputStream<< "     " COLOR_ORANGE BLOCK_CHAR BLOCK_CHAR COLOR_RESET;
            }
            break;
        default:
            break;
    }
}
