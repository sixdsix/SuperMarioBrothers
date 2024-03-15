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
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;

//constructor
Level::Level(char* numLevels, char* numLives, char* gridDimension, char* percentCoins, char* percentNothing,char* percentGoombas, char* percentKoopas, char* percentMushrooms, char* outputFile) {
    std::srand(time(0));
    m_numLevels = atoi(numLevels);
    m_levelCount = 0;
    m_gridDimension = atoi(gridDimension);
    m_percentCoins = atoi(percentCoins);
    m_percentNothing = atoi(percentNothing);
    m_percentGoombas = atoi(percentGoombas);
    m_percentKoopas = atoi(percentKoopas);
    m_percentMushrooms = atoi(percentMushrooms);
    m_warpPipes = atoi(numLevels) - 1;
    m_nextLevel = false;
    m_success = false;
    m_numLives = atoi(numLives);
    m_numMoves = 0;
    m_outputFile = outputFile;

    //clearing previously existing text file
    outFile.open(outputFile);
    if (!outFile.is_open()) {
        cout << "An Error opening the output file has occured." << endl;
        return;
    }
    outFile.close();
    //creating new text file
    outFile.open(outputFile, fstream::app);
    if (!outFile.is_open()) {
        cout << "An Error opening the output file has occured." << endl;
        return;
    }

    for (int i = 1; i <= m_numLevels; ++i) {
        outFile << "Level: " << i << endl;
        char** curLevel = new char*[m_gridDimension];
        for (int i = 0; i < m_gridDimension; ++i) {
            curLevel[i] = new char[m_gridDimension];
        }

        populateLevel(curLevel, m_percentCoins, m_percentNothing, m_percentGoombas, m_percentKoopas, m_percentMushrooms);
        delete[] curLevel;
        outFile << endl << endl;
        

        if (m_success == true) {
            outFile << "Level: " << i << " complete" << endl << endl;
            m_success = false;
            m_nextLevel = false;
        } else {
            outFile << "Mario Lost Level: " << i << endl << endl;
            break;
        }
        ++m_levelCount;
    }
    if (m_levelCount == m_numLevels) {
        outFile << "Mario saved Peach" << endl;
        outFile << "It took " << m_numMoves << " moves" << endl;
    } else {
        outFile << "GAME OVER\n";
        outFile << "It took " << m_numMoves << " moves" << endl;
    }
    outFile.close();
}

//destructor
Level::~Level(){}

//populates the level with randomized inputs and then creates and runs the game
void Level::populateLevel(char** curLevel, int percentCoins, int percentNothing,int percentGoombas, int percentKoopas, int percentMushrooms) {
    // these equations convert the percentage to a decimal and then 
    //multiply by the dimension squared to get a number of how many items are needed
    int numCoins = percentCoins * .01 * pow(m_gridDimension, 2);
    int numNothing = percentNothing * .01 * pow(m_gridDimension, 2);
    int numGoombas = percentGoombas * .01 * pow(m_gridDimension, 2);
    int numKoopas = percentKoopas * .01 * pow(m_gridDimension, 2);
    int numMushrooms = percentMushrooms * .01 * pow(m_gridDimension, 2);

    //filling array with ~'s as temp values to ensure authenticity of randomeness
    for (int rows = 0; rows < m_gridDimension; ++rows) {
        for (int cols = 0; cols < m_gridDimension; ++ cols) {
            curLevel[rows][cols] = '~';
        }
    }

    //creating coins
    while(numCoins > 0) {
        int rand1 = rand() % m_gridDimension;
        int rand2 = rand() % m_gridDimension;
        if (curLevel[rand1][rand2] == '~') {
            curLevel[rand1][rand2] = 'c';
            numCoins--;
         }
    }
    //creating empty spaces
    while(numNothing > 0) {
        int rand1 = rand() % m_gridDimension;
        int rand2 = rand() % m_gridDimension;
        if (curLevel[rand1][rand2] == '~') {
            curLevel[rand1][rand2] = 'x';
            numNothing--;
         }
    }
    //creating goombas
    while(numGoombas > 0) {
        int rand1 = rand() % m_gridDimension;
        int rand2 = rand() % m_gridDimension;
        if (curLevel[rand1][rand2] == '~') {
            curLevel[rand1][rand2] = 'g';
            numGoombas--;
        }
    }
    //creating koopas
    while(numKoopas > 0) {
        int rand1 = rand() % m_gridDimension;
        int rand2 = rand() % m_gridDimension;
        if (curLevel[rand1][rand2] == '~') {
            curLevel[rand1][rand2] = 'k';
            numKoopas--;
        }
    }
    //creating mushrooms
    while(numMushrooms > 0) {
        int rand1 = rand() % m_gridDimension;
        int rand2 = rand() % m_gridDimension;
        if (curLevel[rand1][rand2] == '~') {
            curLevel[rand1][rand2] = 'm';
            numMushrooms--;
        }
    }

    if (m_warpPipes !=0 ) {
        //creating warp pipe on all levels except last
        int rand1 = rand() % m_gridDimension;
        int rand2 = rand() % m_gridDimension;
        curLevel[rand1][rand2] = 'w';
        --m_warpPipes;
    }
    //creating boss
    int rand1 = rand() % m_gridDimension;
    int rand2 = rand() % m_gridDimension;
    curLevel[rand1][rand2] = 'b';

    for (int i = 0; i < m_gridDimension; ++i) {
        for (int j = 0; j < m_gridDimension; ++j) {
            if (curLevel [i][j] == '~') {
                curLevel[i][j] = 'x';
            }
        }
    }

    printLevel(curLevel);

    //creating Mario on Map
    rand1 = rand() % m_gridDimension;
    rand2 = rand() % m_gridDimension;
    curLevel[rand1][rand2] = 'H';
    
    int randMove = rand() % 4 + 1;

    Mario* mario = new Mario(m_numLives, curLevel, m_gridDimension, rand1, rand2, m_outputFile);
    
    while (mario->getNumLives() > 0 && mario->shouldMoveOn() == false) {
        ++m_numMoves;
        if (randMove == 4) {
            outFile << "Mario will move up" << endl << endl;
            outFile << "Level: " << m_levelCount + 1 << endl;
            mario->moveUp();
            outFile << "Lives: " << mario->getNumLives() << endl;
            outFile << "Coins: " << mario->getNumCoins() << endl;
            randMove = rand() % 4 + 1;
        } else if (randMove == 3) {
            outFile << "Mario will move down" << endl << endl;
            outFile << "Level: " << m_levelCount + 1 << endl;
            mario->moveDown();
            outFile << "Lives: " << mario->getNumLives() << endl;
            outFile << "Coins: " << mario->getNumCoins() << endl;
            randMove = rand() % 4 + 1;
        } else if (randMove ==2 ) {
            outFile << "Mario will move left" << endl << endl;
            outFile << "Level: " << m_levelCount + 1 << endl;
            mario->moveLeft();
            outFile << "Lives: " << mario->getNumLives() << endl;
            outFile << "Coins: " << mario->getNumCoins() << endl;
            randMove = rand() % 4 + 1;
        } else {
            outFile << "Mario will move right" << endl << endl;
            outFile << "Level: " << m_levelCount + 1 << endl;
            mario->moveRight();
            outFile << "Lives: " << mario->getNumLives() << endl;
            outFile << "Coins: " << mario->getNumCoins() << endl;
            randMove = rand() % 4 + 1;
        }
    }


    if (mario->shouldMoveOn()) {
        m_success = true;
    } else {
        m_success = false;
    }
}

void Level::printLevel(char** curLevel) {
    for (int rows = 0; rows < m_gridDimension; ++rows) {
        for (int cols = 0; cols < m_gridDimension; ++cols) {
            outFile << "[" << curLevel[rows][cols] << "]";
        }
        outFile << endl;
    }
    outFile << endl;
}

void Level::setNextLevel(bool nextLevel) {
    m_nextLevel = nextLevel;
}




