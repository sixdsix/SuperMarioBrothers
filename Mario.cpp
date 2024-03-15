/*
 Nathan Miller
 2366380
 nathmiller@chapman.edu 
 CPSC 350-03
 Assignment 2: NotSoSuperMarioBros
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "Mario.h"

using namespace std;
//constructor creates mario and the output file
Mario::Mario(int numlives, char** curLevel, int gridDimension, int marRow, int marCol, string outputFile) {
    std::srand(time(0));
    m_numLives = numlives;
    m_numCoins = 0;
    m_marRow = marRow;
    m_gridDimension = gridDimension;
    m_marCol = marCol;
    moveOn = false;
    m_curLevel = curLevel;
    m_killCount = 0;
    m_outputFile = outputFile;

    outFile.open(outputFile, fstream::app);
    if (!outFile.is_open()) {
        cout << "An Error opening the output file has occured." << endl;
        return;
    }
}

//destructor
Mario::~Mario() {}

//moves marios position and launches his interactions on the map
//nothing is passed, however there are outputs to the output file
void Mario::moveUp() {
    m_curLevel[m_marRow][m_marCol] = 'x';
    outFile << "Position: (" << m_marRow << ", " << m_marCol << ")" << endl;
    outFile << "Power Level: " << m_powerLevel << endl;

    if (m_marRow == 0) {
        m_marRow = m_gridDimension - 1;
        char temp = m_curLevel[m_marRow][m_marCol];
        // cout << "Temp MU: " << temp << endl;
        m_curLevel[m_marRow][m_marCol] = 'H';
        enemyId(temp);
    } else {
        m_marRow -= 1;
        char temp = m_curLevel[m_marRow][m_marCol];
        // cout << "Temp MU: " << temp << endl;
        m_curLevel[m_marRow][m_marCol] = 'H';
        enemyId(temp);
    }
}

//moves marios position and launches his interactions on the map
//nothing is passed, however there are outputs to the output file
void Mario::moveLeft() {
    m_curLevel[m_marRow][m_marCol] = 'x';
    outFile << "Position: (" << m_marRow << ", " << m_marCol << ")" << endl;
    outFile << "Power Level: " << m_powerLevel << endl;
    if (m_marCol == 0) {
        
        m_marCol = m_gridDimension - 1;
        char temp = m_curLevel[m_marRow][m_marCol];
        // cout << "Temp ML: " << temp << endl;
        enemyId(temp);
        m_curLevel[m_marRow][m_marCol] = 'H';
    } else {
       
        m_marCol -= 1;
        char temp = m_curLevel[m_marRow][m_marCol];
        // cout << "Temp ML: " << temp << endl;
        m_curLevel[m_marRow][m_marCol] = 'H';
        enemyId(temp);
    }
}

//moves marios position and launches his interactions on the map
//nothing is passed, however there are outputs to the output file
void Mario::moveDown() {
    m_curLevel[m_marRow][m_marCol] = 'x';
    outFile << "Position: (" << m_marRow << ", " << m_marCol << ")" << endl;
    outFile << "Power Level: " << m_powerLevel << endl;

    if (m_marRow == m_gridDimension - 1) {
        m_curLevel[m_marRow][m_marCol] = 'x';
        m_marRow = 0;
        char temp = m_curLevel[m_marRow][m_marCol];
        // cout << "Temp MD: " << temp << endl;
        m_curLevel[m_marRow][m_marCol] = 'H';
        enemyId(temp);
    } else {
        m_curLevel[m_marRow][m_marCol] = 'x';
        m_marRow += 1;
        char temp = m_curLevel[m_marRow][m_marCol];
        // cout << "Temp MD: " << temp << endl;
        m_curLevel[m_marRow][m_marCol] = 'H';
        enemyId(temp);
    }
}

//moves marios position and launches his interactions on the map
//nothing is passed, however there are outputs to the output file
void Mario::moveRight() {
    m_curLevel[m_marRow][m_marCol] = 'x';
    outFile << "Position: (" << m_marRow << ", " << m_marCol << ")" << endl;
    outFile << "Power Level: " << m_powerLevel << endl;
    if (m_marCol == m_gridDimension - 1) {
        m_marCol = 0;
        char temp = m_curLevel[m_marRow][m_marCol];
        // cout << "Temp MR: " << temp << endl;
        m_curLevel[m_marRow][m_marCol] = 'H';
        enemyId(temp);
    } else {
        m_marCol += 1;
        char temp = m_curLevel[m_marRow][m_marCol];
        // cout << "Temp MR: " << temp << endl;
        m_curLevel[m_marRow][m_marCol] = 'H';
        enemyId(temp);
    }
}

//returns Marios current number of lives
int Mario::getNumLives() {
    return m_numLives;
}

// runs a switch on the current enemy on the board and prompts their respective interactions
void Mario::enemyId(char temp) {
    switch (temp) {
        case 'c':
            collectCoin();
            break;
        case 'x':
            logNothing();
            break;
        case 'g':
            fightGoomba();
            break;
        case 'k':  
            fightKoopa();
            break;
        case 'm':
            addMushroom();
            break;
        case 'w':
            warp();
            break;
        case 'b':
            bossFight();
            break;
        default:
            cout << "landed on empty" << endl;
            break;
    }
}

//This function adds a coin to marios stache and if he has more than 20 coins,
//mario gains a life
void Mario::collectCoin() {
    ++m_numCoins;
    if (m_numCoins == 20) {
        ++m_numLives;
        m_numCoins = 0;
    }
    outFile << "Mario collected a coin" << endl;
}

//this function prints an string to the output if mario lands on an empty space
void Mario::logNothing() {
    outFile << "Mario landed on an empty space" << endl;
}

//this function creates a 80 percent chance mario defeats the goomba,
//if his power level is 0, he loses lives, otherwise he loses his powerlevel
void Mario::fightGoomba() {
    int random = rand() % 100;

    if (random > 80) {
        if (m_powerLevel == 0) {
            --m_numLives;
        } else {
            --m_powerLevel;
        }
        m_curLevel[m_marRow][m_marCol] = 'g';
        outFile << "Mario lost to a Goomba" << endl;
    } else {
        outFile << "Mario beat a Goomba" << endl;
        ++m_killCount;
        checkKillCount();
    }
    
}

//this function creates a 65 percent chance mario defeats the goomba,
//if his power level is 0, he loses lives, otherwise he loses his powerlevel
void Mario::fightKoopa() {
    int random = rand() % 100;

    if (random > 65) {
        if (m_powerLevel == 0) {
            --m_numLives;
        } else {
            --m_powerLevel;
        }
        m_curLevel[m_marRow][m_marCol] = 'k';
        outFile << "Mario lost to a Koopa" << endl;
    } else {
        outFile << "Mario beat a Koopa" << endl;
        ++m_killCount;
        checkKillCount();
    }
    
}
//this function raises marios powerlevel to a max of 2
void Mario::addMushroom() {
    if (m_powerLevel < 2) {
        ++m_powerLevel;
    } else {
        m_powerLevel = 2;
    }
   
   outFile << "Mario ate a mushroom" << endl;
}
//this function alters a boolean signifying the end of the while loop level
void Mario::warp() {
    moveOn = true;
    outFile << "Mario hit a warp pipe and moves on" << endl;
}
//this function removes both powerlevels if they are to be lost, then removes one life
//at a time as the user fights bowser
void Mario::bossFight() {
    if (m_powerLevel == 2) {
        while(m_numLives > 0) {
            int random = rand() % 100;
            if (random > 50) {
                m_powerLevel = 2;
                outFile << "Mario lost to bowser" << endl;
            } else {
                outFile << "Mario beat bowser" << endl;
                moveOn = true;
                //m_numLives = -1;
                break;
            }
        }
    } else {
        while(m_numLives > 0) {
            int random = rand() % 100;
            if (random > 50) {
                m_numLives -= 2;
                outFile << "Mario lost to bowser" << endl;
            } else {
                outFile << "Mario beat bowser" << endl;
                moveOn = true;
                //m_numLives = -1;
                break;
            }
        }
    }
}

//this function returns a boolean signifying the end of a while loop
bool Mario::shouldMoveOn() {
    return moveOn;
}

// this function returns private member variable numCoins
int Mario::getNumCoins() {
    return m_numCoins;
}

//this function tallys the users kills and adds a life if the number reaches 7
void Mario::checkKillCount() {
    if (m_killCount >= 7) {
        outFile << "Mario gained a life by defeating 7 enemies" << endl;
        ++m_numLives;
    } 
}