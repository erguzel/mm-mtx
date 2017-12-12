// Olgun Ergüzel, 217205614, Computaitonal Physics
// other users
//

#include <iostream>

#pragma message ("please use -a or -b options for subquestions of task1.")
#pragma message ("please send -clock flag to enable clock time calculation.")

using namespace std;

//accepted commandline parameters

const string parameters[2] = {"-a", "-b"};

//global switches
static bool isA = false;
static bool isB = false;

//--------utilization functions

//writes given message to console or log file. // todo
void logMessage(string message){
    cout<< message << endl;
}

//Parses command line parameters and sets the global switches for run mode.
void commandLineParser(int arg, char** args){
    string option = (args[1]);
    parameters->find("-a");
    if(option == "a"){
        isA = true;
        logMessage("the global switch set to a");
    }
    else if (option == "b"){
        isB = true;
        logMessage("the global switch set to b" );
    } else{
        cout << "this argument is not supported yet" << std::endl;
    }
}
//--------main
int main(int arg, char** args) {
    // parse commandline parameters
    commandLineParser(arg,args);
}
