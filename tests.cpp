#include "headers/catch.hpp"
#include "headers/tetris.hpp"
#include "headers/block.hpp"

/**
* testing:
 *
 * validation of movement of block
 * movement of block
 * validation of rotation of block
 * rotation of block
 *
 * points based on lines
 *
 * ending
*/

std::vector<std::vector<char>> generateBoardWithFullLines(size_t boardWidth,size_t boardHeight ,int fullLines) {
    std::vector<std::vector<char>> board;
    std::vector<char> innerVec;
    for (size_t row = 0;row < boardHeight;row++) {
        innerVec = {};
        for (size_t column = 0; column < boardWidth; column++) {
            if (row < boardHeight-fullLines) {
                innerVec.push_back('0');
            } else {
                innerVec.push_back('r');
            }
        }
        board.push_back(innerVec);
    }
    return board;
}


std::vector<std::vector<char>> generateEmptyBoard(size_t boardWidth, size_t boardHeight) {
    return generateBoardWithFullLines(boardWidth,boardHeight,0);
}

std::vector<std::vector<char>> generateFullBoard(size_t boardWidth, size_t boardHeight) {
    return generateBoardWithFullLines(boardWidth,boardHeight,(int)boardHeight);
}

std::vector<char> rotateTest(block b) {
    std::vector<char> rotated;
for (size_t i = 0; i < b.getWidth(); i++) {
        for (int j = static_cast<int>(b.getHeight()) - 1; j >= 0; j--) {
            rotated.push_back(b.getBlockChars()[j * b.getWidth() + i]);
        }
    }
    return rotated;
}

bool sameVectors(std::vector<char> v1, std::vector<char> v2) {
    if (v1.size() != v2.size()) {
        return false;
    }
    for (int i = 0; i<v1.size();i++) {
        if (v1[i]!=v2[i]) {
            return false;
        }
    }
    return true;
}

TEST_CASE("Validation of movement") {
    size_t boardWidth = 10;
    size_t boardHeight = 15;
    block block(boardWidth,boardHeight);

    SECTION("Right after spawn on empty board") {
        std::vector<std::vector<char>> board = generateEmptyBoard(boardWidth,boardHeight);
        REQUIRE(block.canMoveDown(board));
        REQUIRE(block.canMoveRight(board));
        REQUIRE(block.canMoveLeft(board));
    }

    SECTION("Right after spawn on full board") {
        std::vector<std::vector<char>> board = generateFullBoard(boardWidth,boardHeight);
        REQUIRE_FALSE(block.canMoveLeft(board));
        REQUIRE_FALSE(block.canMoveDown(board));
        REQUIRE_FALSE(block.canMoveRight(board));
    }

    SECTION("In left bottom corner on empty board") {
        std::vector<std::vector<char>> board = generateEmptyBoard(boardWidth,boardHeight);
        block.setPos(std::make_pair(0,boardHeight-block.getHeight()));
        REQUIRE_FALSE(block.canMoveLeft(board));
        REQUIRE_FALSE(block.canMoveDown(board));
        REQUIRE(block.canMoveRight(board));
    }
}

TEST_CASE("Movement") {
    size_t boardWidth = 10;
    size_t boardHeight = 15;
    block block(boardWidth,boardHeight);
    std::pair<size_t ,size_t> initPos = block.getPos();
    std::vector<std::vector<char>> board = generateEmptyBoard(boardWidth,boardHeight);

    SECTION("Down") {
        block.moveDown(board);
        std::pair<size_t ,size_t > expected = std::make_pair(initPos.first,initPos.second+1);
        REQUIRE(block.getPos().first==expected.first);
        REQUIRE(block.getPos().second==expected.second);
    }

    SECTION("Right") {
        block.moveRight(board);
        std::pair<size_t ,size_t > expected = std::make_pair(initPos.first+1,initPos.second);
        REQUIRE(block.getPos().first==expected.first);
        REQUIRE(block.getPos().second==expected.second);
    }

    SECTION("Left") {
        block.moveLeft(board);
        std::pair<size_t ,size_t > expected = std::make_pair(initPos.first-1,initPos.second);
        REQUIRE(block.getPos().first==expected.first);
        REQUIRE(block.getPos().second==expected.second);
    }
}

TEST_CASE("Validation of rotation") {
    size_t boardWidth = 10;
    size_t boardHeight = 15;
    block block(boardWidth,boardHeight);

    SECTION("Right after spawn on empty board") {
        std::vector<std::vector<char>> board = generateEmptyBoard(boardWidth,boardHeight);
        REQUIRE(block.canRotate(board));
    }

    SECTION("Right after spawn on full board") {
        std::vector<std::vector<char>> board = generateFullBoard(boardWidth,boardHeight);
        REQUIRE_FALSE(block.canRotate(board));
    }
}

TEST_CASE("Rotation") {
    size_t boardWidth = 10;
    size_t boardHeight = 15;
    block block(boardWidth,boardHeight);
    std::vector<std::vector<char>> board = generateEmptyBoard(boardWidth,boardHeight);

    SECTION("Rotate") {
        std::vector<char> expected = rotateTest(block);
        block.rotate(board);
        REQUIRE(sameVectors(expected,block.getBlockChars()));
    }

    SECTION("Rotate 4 times should always be the same block") { // for some blocks it is even less
        std::vector<char> expected2 = block.getBlockChars();
        block.rotate(board);
        block.rotate(board);
        block.rotate(board);
        block.rotate(board);
        REQUIRE(sameVectors(expected2,block.getBlockChars()));
    }
}

// Points scale non-linear based on lines cleared
// Way more points are given when cleared 4 lines in one step than clearing one line four times
TEST_CASE("Giving points") {
    size_t boardWidth = 10;
    size_t boardHeight = 15;
    int level = 3;
    tetris t(boardWidth,boardHeight,level);

    SECTION("Zero cleared lines") {
        t.setBoard(generateEmptyBoard(boardWidth,boardHeight));
        t.checkFullLines();
        REQUIRE(t.getScore()==0);
    }

    SECTION("One cleared line") {
        t.setBoard(generateBoardWithFullLines(boardWidth,boardHeight,1));
        t.checkFullLines();
        REQUIRE(t.getScore()==(level+1)*40);
    }

    SECTION("Two cleared lines") {
        t.setBoard(generateBoardWithFullLines(boardWidth,boardHeight,2));
        t.checkFullLines();
        REQUIRE(t.getScore()==(level+1)*100);
    }

    SECTION("Three cleared lines") {
        t.setBoard(generateBoardWithFullLines(boardWidth,boardHeight,3));
        t.checkFullLines();
        REQUIRE(t.getScore()==(level+1)*300);
    }

    SECTION("Four cleared lines") {
        t.setBoard(generateBoardWithFullLines(boardWidth,boardHeight,4));
        t.checkFullLines();
        REQUIRE(t.getScore()==(level+1)*1200);
    }
}

TEST_CASE("Ending of game") {
    size_t boardWidth = 10;
    size_t boardHeight = 15;
    int level = 3;
    tetris t(boardWidth,boardHeight,level);

    SECTION("Empty board") {
        t.setBoard(generateEmptyBoard(boardHeight,boardHeight));
        t.update();
        REQUIRE_FALSE(t.isGameOver());
    }

    SECTION("Full board") {
        t.setBoard(generateFullBoard(boardHeight,boardHeight));

        for(int i = 0; i<5;i++) t.update();

        REQUIRE(t.isGameOver());
    }
}