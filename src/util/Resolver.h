//
// Created by Olgun Erguzel on 11.03.2018.
//

#ifndef MATRIX_MULTIPLIER_RESOLVER_H
#define MATRIX_MULTIPLIER_RESOLVER_H

#include <string>
#include <iostream>
#include <algorithm>



static class Resolver {

public:
    static bool isParalell = false;
public:
    static bool isClock = false;
public:
    static clock_t start;
public:
    static clock_t finish;
public:
    double progressTime;
public:
    static std::string option;
public:
    static double fRand(double fMin, double fMax)
    {
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

public:
    static  int getIndexFromRowColumn(int rowNumber, int columnNumber, int ColumnSize, int RowSize) {
        int currentIndex = (RowSize+((rowNumber-1)*RowSize) - (RowSize-columnNumber))-1;
        return currentIndex;
    }

/**
 * Writes a simple string message to the console
 * @param message the string consol message
 */
public:
    static  void logMessage(std::string message) {
        std::cout << message << std::endl;
    }

public:
    static int number_of_threads = 1;
};


#endif //MATRIX_MULTIPLIER_RESOLVER_H
