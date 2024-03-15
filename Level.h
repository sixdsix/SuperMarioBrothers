/*
 Nathan Miller
 2366380
 nathmiller@chapman.edu 
 CPSC 350-03
 Assignment 2: NotSoSuperMarioBros
*/
#ifndef LEVEL_H
#define LEVEL_H
#include <fstream>
class Level {
    private:
        int m_numLevels;
        int m_gridDimension;
        int m_percentCoins;
        int m_levelCount;
        int m_percentNothing;
        int m_percentGoombas;
        int m_percentKoopas;
        int m_percentMushrooms;
        int m_numLives;
        bool m_nextLevel;
        bool m_success;
        int m_warpPipes;
        int m_numMoves;
        std::ofstream outFile;
        std::string m_outputFile;
    public:
        Level(char* numLevels, char* numLives, char* gridDimension, char* percentCoins, char* percentNothing, char* percentGoombas, char* percentKoopas, char* percentMushrooms, char* outputFile);
        ~Level();
        void populateLevel(char** curLevel, int percentCoins, int percentNothing, int percentGoombas, int percentKoopas, int percentMushrooms);
        void printLevel(char** curLevel);
        void setNextLevel(bool nextLevel);
};




#endif