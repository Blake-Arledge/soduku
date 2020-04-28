//
// Created by Blake on 9/23/2016.
//

#include <fstream>
#include <iostream>
#include "Sudoku.h"

using namespace std;

Sudoku::Sudoku() {
    std::fill( &puzzleList[0][0], &puzzleList[rows][0], 0 );
}

Sudoku::~Sudoku() {}

void Sudoku::loadFromFile(std::string filename) {
    int a;
    std::ifstream in(filename);
    std::string errorMessage = std::string("Error: on file ") + filename;

    if (in.fail()) {
        throw std::runtime_error(errorMessage);
    }

    int count = 0;
    while (in.good() && !count) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                in.operator>>(a);
                //std::cout << "a: " << a << ends;
                puzzleList[i][j] = a;
                //std::cout << "(i,j): " << "(" << i << "," << j << ")" << ends;
            }
            //std::cout << endl;
        }
        count = 1;
        //why is this running twice?
    }
}

bool Sudoku::solve() {
    return assignValue(0,0);
}

bool Sudoku::assignValue(int row, int col) {

    //end of the puzzle has been reached
    if (row == 9) {
        return true;
    } else {

        if (puzzleList[row][col] != 0) {
            if (col == 8) {
                return assignValue(row + 1, 0);
            } else {
                return assignValue(row, col + 1);
            }
        }

        for (int i = 0; i < 10; i++) {
            bool valid = checkValue(row, col, i);
            if (valid) {
                puzzleList[row][col] = i;
                std::cout << puzzleList[row][col] << std::endl;

                bool possible = false;
                if (col == 8) {
                    possible = assignValue(row + 1, 0);
                } else {
                    possible = assignValue(row, col + 1);
                }

                if (possible) {
                    return true;
                } else {
                    puzzleList[row][col] = 0;
                }
            }
        }
        return false;
    }
}


bool Sudoku::checkValue(int row, int col, int val){
    //check if any value in row has the value - puzzle[iter][col]
    for(int i = 0; i < 9; i++){
        if(puzzleList[i][col] == val){
            return false;
        }
    }
    //check if any value in the col has the value- puzzle[row][iter]
    for(int i = 0; i < 9; i++){
        if(puzzleList[row][i] == val){
            return false;
        }
    }
    //check if any value in the remaining 4 squares of the block have the value
    //TODO: figure out how to check the block

   //for the first block:
    int rowRoot = 3*(row/3);
    int colRoot = 3*(col/3);
    int row2 = rowRoot + row2;
    int col2 = colRoot + col2;


    for(int i = rowRoot; i < row2; i++){
        for(int j = colRoot; j < col2; j++){
            if(puzzleList[i][j] == val){
                return false;
            }
        }
    }

    return true;
}

void Sudoku::print() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if((j == 3) || (j == 6)){
                std::cout  << "|"  << std::ends;
            }
            else if (i == 3){
                //std::cout << "------+-------+------" << std::endl;
            }
            std::cout << puzzleList[i][j] << std::ends;
        }
        std::cout << std::endl;
    }
}

bool Sudoku::equals(const Sudoku &other) const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if(puzzleList[i][j] != other.puzzleList[i][j]){
                return false;
            }
        }
    }
    return true;
}


