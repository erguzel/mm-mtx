//
// Created by oe019 on 30.12.17.
//

#ifndef MATRIX_MULTIPLIER_INITIALIZER_H
#define MATRIX_MULTIPLIER_INITIALIZER_H

#include <string>
#include <iostream>
#include <algorithm>
#include "../util/Resolver.cpp"

using namespace std;

/**
 * Represents the program initializer object
 */
class initializer {

/**
 * Initializes the program with the required configurations.
 */
public:
    static void Initialize(int arg, char **args) {

        commandLineParser(arg, args);
    }

/**
 * Parses command line arguments
 * @param arg commandline argument size
 * @param args commandline argument pointer list
 */
private:
    static void commandLineParser(int arg, char **args) {
        if (arg == 1) {
            Resolver::logMessage("Non parallel run is enabled.");
        }
        if (arg - 1 > 3) {
            Resolver::logMessage("error.. too may arguments specified. Quitting...");
            return;
        } else {
            bool flag = false;
            for (int i = 1; i < arg; i++) {
                Resolver::option = args[i];
                if (Resolver::option == "-pl") {
                    Resolver::logMessage("parallel mode is activated..");
                    Resolver::isParalell = true;
                    flag = true;
                    if (*args[i + 1] != ' ') {
                        string tnmbr = args[i + 1];
                        Resolver::number_of_threads = std::stoi(tnmbr);

                    }
                }
                    //if one if the parameters is -b
                else if (Resolver::option == "-cl") {
                    Resolver::logMessage("clock mode is activated..");
                    Resolver::isClock = true;
                    flag = true;
                }

            }
            if (flag == true) {
                Resolver::logMessage("program starting with valid arguments..");
            } else {
                Resolver::logMessage("program starting with default configuration..");
            }
        }
    }
};


#endif //MATRIX_MULTIPLIER_INITIALIZER_H
