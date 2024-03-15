/*
 Nathan Miller
 2366380
 nathmiller@chapman.edu 
 CPSC 350-03
 Assignment 2: NotSoSuperMarioBros
*/
#include <iostream>
#include "Level.h"
#include "Mario.h"

int main(int argc, char** argv) {
    
    Level* level = new Level(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);

    delete level;
    return 0;
}