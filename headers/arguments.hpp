#ifndef TETRIS_ARGUMENTS_HPP
#define TETRIS_ARGUMENTS_HPP
#include "constants.hpp"


/*
 * Enable or disable terminal raw mode
 */
void set_raw(bool set);
/*
 * Parameters for initializing
 *
 */
struct InputArgs {
    int width, height, level;
};

class ArgParser {
public:
    /*
     * Parsing of the input
     * -w width of the board
     * -h height of the board
     * -l initial level
     */
    static InputArgs parseInputArgs(int argc, char *argv[]);
private:
    /*
     * Get int from string
     */
    static int str2int(int *res, const char *str);
};


#endif //TETRIS_ARGUMENTS_HPP
