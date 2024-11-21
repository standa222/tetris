#ifndef TETRIS_CONSTANTS_HPP
#define TETRIS_CONSTANTS_HPP

// constants for colors when printing
//           for limitations and default values for board size when initializing
//           for arrow keys


#define ARROW_KEY_UP 65
#define ARROW_KEY_DOWN 66
#define ARROW_KEY_LEFT 68
#define ARROW_KEY_RIGHT 67

#define DEFAULT_WIDTH 10
#define MIN_WIDTH 5
#define MAX_WIDTH 15
#define DEFAULT_HEIGHT 20
#define MIN_HEIGHT 15
#define MAX_HEIGHT 25
#define DEFAULT_LEVEL 1
#define MAX_LEVEL 20

#define BLOCK_CHAR "\u2588"
#define SIDE_LINE "\u2502"
#define BOTTOM_LINE "\u2500"
#define LEFT_BOTTOM_CORNER_CHAR "\u2514"
#define RIGHT_BOTTOM_CORNER_CHAR "\u2518"

#define COLOR_CYAN "\x1B[96m"
#define COLOR_YELLOW "\x1B[93m"
#define COLOR_PURPLE "\x1B[95m"
#define COLOR_GREEN "\x1B[92m"
#define COLOR_BLUE "\x1B[94m"
#define COLOR_RED "\x1B[91m"
#define COLOR_ORANGE "\x1B[33m"

#define COLOR_GREEN_BG "\x1B[42m"
#define COLOR_BLUE_BG "\x1B[44m"
#define COLOR_RED_BG "\x1B[41m"
#define COLOR_YELLOW_BG "\x1B[103m"
#define COLOR_PURPLE_BG "\x1B[105m"

#define COLOR_RESET "\x1B[m"
#define ANSI_CLEAR "\x1B[2J\x1B[H"

#endif //TETRIS_CONSTANTS_HPP
