#include <cstring>

#include "iostream"
#include "headers/arguments.hpp"

void printTetris() {
    std::cout << "\n" COLOR_RED BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR " " COLOR_ORANGE BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR " " COLOR_YELLOW BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR " " COLOR_GREEN BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR "   " COLOR_BLUE BLOCK_CHAR "   " COLOR_PURPLE BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR "\n\r";
    std::cout << "  " COLOR_RED BLOCK_CHAR "   " COLOR_ORANGE BLOCK_CHAR "     " COLOR_YELLOW "  " BLOCK_CHAR "   " COLOR_GREEN BLOCK_CHAR "   " BLOCK_CHAR "  " COLOR_BLUE BLOCK_CHAR "  " COLOR_PURPLE BLOCK_CHAR "\n\r";
    std::cout << "  " COLOR_RED BLOCK_CHAR "   " COLOR_ORANGE BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR  " " COLOR_YELLOW "  " BLOCK_CHAR "   " COLOR_GREEN BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR " " COLOR_BLUE "  " BLOCK_CHAR "   " COLOR_PURPLE BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR "\n\r";
    std::cout << "  " COLOR_RED BLOCK_CHAR "   " COLOR_ORANGE BLOCK_CHAR "     " COLOR_YELLOW "  " BLOCK_CHAR "   " COLOR_GREEN BLOCK_CHAR "   " BLOCK_CHAR "  " COLOR_BLUE  BLOCK_CHAR "      " COLOR_PURPLE BLOCK_CHAR "\n\r";
    std::cout << "  " COLOR_RED BLOCK_CHAR "   " COLOR_ORANGE BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR " " COLOR_YELLOW "  " BLOCK_CHAR "   " COLOR_GREEN BLOCK_CHAR "   " BLOCK_CHAR "  " COLOR_BLUE  BLOCK_CHAR "  " COLOR_PURPLE BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR BLOCK_CHAR  "\n\r";

    std::cout << COLOR_RESET "\n\n";
}

void printHelpMessage() {
    std::cout<<ANSI_CLEAR;
    printTetris();
    std::cout<< "Hello and welcome to tetris made by Stanislav Sadilek (sadilsta).\n\r";
    std::cout<<"This is my seminar work for course B6B36PCC - Programming in C/C++\n\n\r";
    std::cout<< "You can control the game with both WASD keys and arrow keys\n\r";
    std::cout<< "S or DOWN   - move the block one row down\n\r";
    std::cout<< "A or LEFT   - move the block one column left\n\r";
    std::cout<< "D or RIGHT  - move the block one column right\n\r";
    std::cout<< "W or UP     - rotate block\n\r";
    std::cout<< "Q           - quit the game\n\n\r";
    std::cout<< "When starting the game, you can set the initial level and board width and height\n\rin command line using following:\n\n\r";
    std::cout<< "-w or -width   - sets the board width between 5 and 15 columns. Default width is 10 columns.\n\r";
    std::cout<< "-h or -height  - sets the board height between 15 and 25 rows. Default height is 20 rows.\n\r";
    std::cout<< "-l or -level   - sets the initial level between 1 and 20. Default initial level is 1.\n\n\r";
    std::cout<< "Your goal is to clear lines. For clearing lines you get points.\n\r";
    std::cout<< "For every 5 cleared lines, your level rises up by 1.\n\r";
    std::cout<< "The higher the level, the faster (and therefore the harder) the game gets.\n\n\r";
    std::cout<< " G O O D   L U C K ! ! !\n\n\r";
}

InputArgs ArgParser::parseInputArgs(int argc, char *argv[]) {
    auto parsedArgs = InputArgs{DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_LEVEL};

    // Check for --help option
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--help") == 0) {
            printHelpMessage();
            std::exit(0);
        }
    }

    for (int i = 1; i < argc; i += 2) {
        int tmp;
        if (std::strlen(argv[i]) > 1)
            switch (argv[i][1]) {
                case 'w':
                    if ((std::strlen(argv[i]) <= 2 || !std::strcmp(argv[i], "-width")) &&
                        str2int(&tmp, argv[i + 1]) >= 0 && tmp >= MIN_WIDTH && tmp <= MAX_WIDTH)
                        parsedArgs.width = tmp;
                    break;
                case 'h':
                    if ((std::strlen(argv[i]) <= 2 || !std::strcmp(argv[i], "-height")) &&
                        str2int(&tmp, argv[i + 1]) >= 0 && tmp >= MIN_HEIGHT && tmp <= MAX_HEIGHT)
                        parsedArgs.height = tmp;
                    break;
                case 'l':
                    if ((std::strlen(argv[i]) <= 2 || !std::strcmp(argv[i], "-level")) &&
                        str2int(&tmp, argv[i + 1]) >= 0 && tmp >= DEFAULT_LEVEL && tmp <= MAX_LEVEL)
                        parsedArgs.level = tmp;
                    break;
                default:
                    break;
            }
    }
    return parsedArgs;
}

int ArgParser::str2int(int *res, const char *str) {
    try {
        *res = std::stoi(str);
    } catch (const std::invalid_argument &e) {
        return -1;
    } catch (const std::out_of_range &e) {
        return -2;
    }
    return 0;
}
