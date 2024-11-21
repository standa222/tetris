#ifndef UNTITLED_TETRIS_HPP
#define UNTITLED_TETRIS_HPP

#include <cstddef>
#include <vector>
#include <condition_variable>
#include "constants.hpp"
#include "window.hpp"
#include "block.hpp"

#define PERIOD 150

class tetris {
public:
    /**
     * Constructs a Tetris game with specified dimensions and starting level.
     * Initializes game state variables, creates a window, and sets up the game board
     * with empty cells. Instantiates the current and next blocks for gameplay.
     * Params are either given by input or set by default.
     *
     * @param width The width of the Tetris game board.
     * @param height The height of the Tetris game board.
     * @param level The starting level of the Tetris game.
     */
    explicit tetris(size_t width, size_t height, int level);

    /**
     * Determine whether the game is over (Game is over if the most upper row is not empty)
     */
    bool isGameOver() const;

    /**
     * Signals the Tetris game to update the graphical output on the window.
     * This function acquires a lock on the mutex and waits for a notification
     * using a conditional variable before redrawing the game state on the window.
     */
    void output();

    /**
     * Updates Tetris game state at a frequency determined by the current level.
     * Handles block default movement (falling down), line clearing, and transition to the next block.
     * Uses sleep duration based on level for timed updates.
     */
    void update();

    /**
     * Handles user input for controlling the Tetris game.
     * This function acquires a lock on the mutex, reads a character from the standard input,
     * and performs corresponding actions based on the input.
     * Supported commands include:
     *   - 'q': Quit the game and notify waiting threads.
     *   - 'a': Move the current block to the left on the game board.
     *   - 's': Move the current block down on the game board.
     *   - 'd': Move the current block to the right on the game board.
     *   - 'w': Rotate the current block on the game board.
     */
    void input();

    /**
    * Checks for and clears full lines in the Tetris game board.
    * Iterates through each row to identify complete lines, clears them,
    * and inserts new empty lines at the top. Calculates points based on
    * the number of lines cleared and updates the game level accordingly.
    */
    void checkFullLines();

    /**
    * Clears a full line in the Tetris game board and inserts a new empty line at the top.
     *
     * @param row The index of the full line to be cleared.
    */
    void clearLineAndInsertNew(size_t row);

    /**
     * Adds points based on how many lines were cleared. The points given are not linear.
     * For a tetris (cleaning 4 lines at once), way more points are given than clearing one line four times.
     *
     * @param linesCleared Number of lines that were cleared in the step
     */
    void addPoints(int linesCleared);

    /**
     * Destructor for Tetris class. Deletes current adn next blocks as those were allocated dynamically
     */
    ~tetris();


    void setBoard(const std::vector<std::vector<char>> &board);

    int getScore() const;

private:
    bool quit;
    size_t width, height;
    int score, lines, level, initialLevel;
    block* currentBlock;
    block* nextBlock;
    std::vector<std::vector<char>> board;
    int updateCounter;
    std::unique_ptr<Window> window;
    std::mutex mutex;
    std::condition_variable cvar;
};


#endif //UNTITLED_TETRIS_HPP
