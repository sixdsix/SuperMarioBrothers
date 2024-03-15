/*
 Nathan Miller
 2366380
 nathmiller@chapman.edu 
 CPSC 350-03
 Assignment 2: NotSoSuperMarioBros
*/
#ifndef MARIO_H
#define MARIO_H
#include <fstream>

class Mario {
    private:
        int m_numLives;
        int m_numCoins;
        int m_powerLevel;
        int m_marRow;
        int m_gridDimension;
        int m_marCol;
        char** m_curLevel;
        std::ofstream outFile;
        bool moveOn;
        int m_killCount;
        std::string m_outputFile;
    public:
        Mario(int numLives, char** curLevel, int gridDimension, int marRow, int marCol, std::string outputFile);
        ~Mario();
        int getNumLives();
        int getNumCoins();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void enemyId(char temp);
        void collectCoin();
        void logNothing();
        void fightGoomba();
        void fightKoopa();
        void addMushroom();
        void warp();
        void bossFight();
        bool shouldMoveOn();
        void checkKillCount();
};





#endif