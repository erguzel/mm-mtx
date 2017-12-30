//
// Created by oe019 on 30.12.17.
//

#ifndef IHPC_2017_WINTER_INITIALIZER_H
#define IHPC_2017_WINTER_INITIALIZER_H

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * Represents the program initializer object
 */
class Initializer {

//-----GLOBAL VARIABLES-------------
/**
 * Accepted commandline parameters
 */
    const std::string parameters[3] = {"-pl", "-cl", "-nt"};
/**
 * Represents the run mode in paralel
 */
    bool isPL;
/**
 * Represents the run mode with clock time
 */
    bool isCL;
/**
 * Represents the clock frequency calculation mode -clock
 */
    int isNT = 0;
/**
 * Represents current command line argument value
 */
    std::string option;
//--END--- GLOBAL VARIABLES-------

/**
 * Initializes the program with the required configurations.
 */
public:
    void Initialize(int arg, char **args) {

        commandLineParser(arg, args);
    }

private:/**
 * Writes a simple string message to the console
 * @param message the string consol message
 */
    void logMessage(std::string message) {
        std::cout << message << std::endl;
    }

    bool is_number(const std::string &s) {
        return !s.empty() && std::find_if(s.begin(),
                                          s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
    }

/**
 * Parses command line arguments
 * @param arg commandline argument size
 * @param args commandline argument pointer list
 */
private:
    void commandLineParser(int arg, char **args) {

        // firts argument is the file itself.
        //check argument number
        int para=0;
        if (arg > 5) {
            logMessage("error.. too may arguments specified. Quitting...");
            return;
        } else {
            for (int i = 1; i < arg; i++) {
                option = args[i];
                // if one of the parameters is -a
                if (option == "-pl") {
                    logMessage("parallel mode is activated..");
                    isPL = true;
                }
                    //if one if the parameters is -b
                else if (option == "-cl") {
                    logMessage("clock mode is on..");
                    isCL = true;
                } else if (option == "-nt") {

                    if (is_number(args[i])) {
                        option = args[i + 1];
                        para = std::stoi(option);
                    } else {
                        std::cout << "the option parameter " << args[i + 1] << " is not in correct format" << std::endl;
                        return;
                    }

                } else {
                    std::cout << "the argument " << args[i] << " is not supported yet" << std::endl;
                    return;
                }
            }

        }

    }
};
//-----END -- USER DEFINED TYPES-------------


#endif //IHPC_2017_WINTER_INITIALIZER_H
