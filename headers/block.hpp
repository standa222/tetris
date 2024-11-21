#ifndef TETRIS_BLOCK_HPP
#define TETRIS_BLOCK_HPP

#include <utility>
#include <cstddef>
#include <vector>
#include "constants.hpp"

class block {
public:
    /**
     * Constructs a Tetris block with a specified width and height for the game board.
     * Generates a random block type, sets its position, color, and character representation,
     * based on the chosen block type. Initializes the block's dimensions and characters.
     *
     * @param boardWidth The width of the Tetris game board.
     * @param boardHeight The height of the Tetris game board.
    */
    block(size_t boardWidth, size_t boardHeight);

    /**
     * Reflects the Tetris block on the given game board at its current position.
     *
     * @param board The game board to draw the block on.
     * @return The updated game board with the block drawn.
     */
    std::vector<std::vector<char>> drawOnBoard(std::vector<std::vector<char>> board);


    /**
     * Determines if movement to given direction is valid.
     * @param board Tetris game board
     * @return false if block is at the bottom/side of the board or there is no empty space to fit in the block,
     *         true otherwise
     */
    bool canMoveDown(const std::vector<std::vector<char>>& board) const;
    bool canMoveRight(const std::vector<std::vector<char>>& board) const;
    bool canMoveLeft(const std::vector<std::vector<char>>& board) const;


    /**
     * If the block can move in given direction, change its position, otherwise do nothing
     * @param board Tetris game board
     */
    void moveDown(const std::vector<std::vector<char>>& board);
    void moveRight(const std::vector<std::vector<char>>& board);
    void moveLeft(const std::vector<std::vector<char>>& board);

    /**
     * Determines if block can rotate. Move the block when needed for the rotation to be made (if possible to move).
     *
     * @param board Tetris game board
     * @return false if block can rotate, true otherwise
     */
    bool canRotate(const std::vector<std::vector<char>>& board);

    /**
     * Determines if block can rotate. Move the block when needed for the rotation to be made (if possible to move).
     * A bit different implementation because it is an I piece
     *
     * @param board Tetris game board
     * @return false if block can rotate, true otherwise
     */
    bool canRotateI(const std::vector<std::vector<char>>& board,std::vector<char> rotated);

    /**
     * Rotates the Tetris block clockwise if a valid rotation is possible.
     *
     * @param board Tetris game board
     */
    void rotate(const std::vector<std::vector<char>>& board);

    char colour;

    std::pair<size_t,size_t> getPos();
    void setPos(std::pair<size_t,size_t> newPos);
    std::vector<char> getBlockChars();
    size_t getHeight() const;
    size_t getWidth() const;
private:
    size_t width,height, boardWidth, boardHeight;
    std::pair<size_t,size_t> pos;
    std::vector<char> blockChars;
    const char blocks[7] = {'I','O','T','S','J','Z', 'L'};
    const char colours[7] = {'c','y','p','g','b','r','o'}; // cyan, yellow, purple, green, blue, red, orange
};







#endif //TETRIS_BLOCK_HPP
