//
// Created by oe019 on 30.12.17.
//

#ifndef IHPC_2017_WINTER_INITIALIZER_H
#define IHPC_2017_WINTER_INITIALIZER_H

#include <string>
#include <iostream>

/**
 * Represents the program initializer object
 */
class Initializer {

//-----GLOBAL VARIABLES-------------
/**
 * Accepted commandline parameters
 */
    const std::string parameters[2] = {"-a", "-b"};
/**
 * Represents the run mode -a
 */
   static bool isA;
/**
 * Represents the run mode -b
 */
    static bool isB;
/**
 * Represents the clock frequency calculation mode -clock
 */
    static bool isClock;
/**
 * Represents current command line argument value
 */
    static std::string option;
//--END--- GLOBAL VARIABLES-------

/**
 * Initializes the program with the required configurations.
 */
public:
    static void Initialize(int arg, char **args) {

        commandLineParser(arg, args);
    }

private:/**
 * Writes a simple string message to the console
 * @param message the string consol message
 */
    static void logMessage(std::string message) {
        std::cout << message << std::endl;
    }

/**
 * Parses command line arguments
 * @param arg commandline argument size
 * @param args commandline argument pointer list
 */
private:
    static void commandLineParser(int arg, char **args) {
        // cout<<"the parameter is"<<option<<endl;

        //no parameters provided
        if (arg == 1) {
            isA = true;
            isB = true;
            logMessage("Multimode run is enabled.");
        }

        // firts argument is the file itself.
        //check argument number
        if (arg - 1 > 2) {
            logMessage("error.. too may arguments specified. Quitting...");
            return;
        } else {
            bool flag = false;
            for (int i = 1; i < arg; i++) {
                option = args[i];
                // if one of the parameters is -a
                if (option == "-a") {
                    logMessage("mode a is activated..");
                    isA = true;
                    flag = true;
                }
                    //if one if the parameters is -b
                else if (option == "-b") {
                    logMessage("mode b is activated..");
                    isB = true;
                    flag = true;
                } else {
                    std::cout << "the argument " << args[i] << " is not supported yet" << std::endl;
                }

            }

            if (flag == true) {
                logMessage("program starting with valid arguments..");
            } else {
                logMessage("To run in multimode, please specify no parameter or specify both correctly.");
                logMessage("No valid argument provided, quitting...");
                return;
            }
        }
    }
};
//-----END -- USER DEFINED TYPES-------------


#endif //IHPC_2017_WINTER_INITIALIZER_H
