#ifndef TETRIS_WINDOW_HPP
#define TETRIS_WINDOW_HPP

#include <vector>
#include <cstddef>
#include <iostream>
#include "constants.hpp"
#include "block.hpp"

class Window {
public:
    /**
     * Constructs a Tetris game window with the specified output stream, width, and height.
     *
     * @param outputStream The output stream to display the Tetris game window.
     * @param width The width of the Tetris game window.
     * @param height The height of the Tetris game window.
     */
    explicit Window(std::ostream &outputStream, size_t width, size_t height);

    /**
     * Redraws the Tetris game window with the updated state.
     * Draws the current block onto the game board and prints the
     * refreshed game window, including the board, score, level, lines, and next block.
     *
     * @param board Tetris game board
     * @param currentBlock Pointer to the current Tetris block.
     * @param score The current score in the Tetris game.
     * @param level The current level in the Tetris game.
     * @param lines The number of lines cleared in the Tetris game.
     * @param quit Flag indicating if the game has ended.
     * @param nextBlock Pointer to the next Tetris block.
    */
    void redraw(std::vector<std::vector<char>> board, block* currentBlock, int score, int level, int lines, bool quit, block* nextBlock);

    /**
     * Draws the Tetris game board with the specified elements including the block,
     * score, level, lines, and next block.
     * Iterates through all chars in game board and uses ANSI escape codes for colors
     * for better visualisation.
     *
     * @param board Tetris game board.
     * @param score The current score in the Tetris game.
     * @param level The current level in the Tetris game.
     * @param lines The number of lines cleared in the Tetris game.
     * @param quit Flag indicating if the game has ended.
     * @param nextBlock Pointer to the next Tetris block to be displayed.
     */
    void drawBoard(const std::vector<std::vector<char>>& board,int score, int level, int lines, bool quit, block* nextBlock);

    /**
     * Prints the preview of the next block coming to the game.
     * Uses ANSI escape codes for colors for better visualisation.
     *
     * @param nextBlock
     * @param row
     */
    void printNextBlock(block* nextBlock,int row);

    /**
     * Draws the tetris logo.
     */
    void printTetris();
private:
    std::ostream &outputStream;     // odkaz na vystupni proud (std::cout)
    size_t width, height;           // rozmery hraci plochy
};












#endif //TETRIS_WINDOW_HPP
