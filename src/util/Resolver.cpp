//
// Created by Olgun Erguzel on 11.03.2018.
//

#include "Resolver.h"


bool::Resolver::isParalell = false;

bool Resolver:: isClock = false;

clock_t Resolver:: start;

clock_t Resolver:: finish;

double Resolver:: progressTime;

std::string Resolver:: option;

double Resolver:: fRand(double fMin, double fMax);

int Resolver:: getIndexFromRowColumn(int rowNumber, int columnNumber, int ColumnSize, int RowSize);

void Resolver:: logMessage(std::string message);

int Resolver:: number_of_threads = 1;

