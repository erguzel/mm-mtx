// Olgun Ergüzel, 217205614, Computaitonal Physics
// other users
//

#include <iostream>

#pragma message ("please use -a or -b options for subquestions of task1.")
#pragma message ("please send -clock flag to enable clock time calculation.")

using namespace std;

//accepted commandline parameters

const string parameters[2] = {"-a", "-b"};

/**
 * Represents the run mode -a
 */
static bool isA = false;
/**
 * Represents the run mode -b
 */
static bool isB = false;
/**
 * Represents the clock frequency calculation mode -clock
 */
static bool isClock = false;

/**
 * Represents current command line argument value
 */
string option;

//--------utilization functions

/**
 * Writes a simple string message to the console
 * @param message the string consol message
 */
void logMessage(string message){
    cout<< message << endl;
}

//-----USER DEFINED TYPES

/**
 * Represents the program initializer object
 */
class initializer{

/**
 * Initializes the program with the required configurations.
 */
public:static void Initialize(int arg, char** args){

        commandLineParser(arg, args);
    }
/**
 * Configures the program according to the run modes
 */
public: static void Configure(){

    }
/**
 * Parses command line arguments
 */
private:static void commandLineParser(int arg, char** args){
        // cout<<"the parameter is"<<option<<endl;

        //no parameters provided
        if (arg == 1){
            isA = true;
            isB = true;
            logMessage("Multimode run is enabled.");
        }

        // firts argument is the file itself.
        //check argument number
        if (arg-1 > 2){
            logMessage("error.. too may arguments specified. Quitting...");
            return;
        }
        else{
            bool flag = false;
            for (int i = 1 ; i < arg ; i++){
                option = args[i];
                // if one of the parameters is -a
                if(option =="-a"){
                    logMessage("mode a is activated..");
                    isA = true;
                    flag = true;
                }
                    //if one if the parameters is -b
                else if (option == "-b"){
                    logMessage("mode b is activated..");
                    isB = true;
                    flag = true;
                }
                else{
                    cout<<"the argument " << args[i] << " is not supported yet"<<endl;
                }

            }

            if (flag == true){
                logMessage("program starting with valid arguments..");
            } else{
                logMessage("To run in multimode, please specify no parameter or specify both correctly.");
                logMessage("No valid argument provided, quitting...");
                return;
            }
        }
    }
};

/**
 * Represents a single matrix entry
 */
class Entry{
    int rowInd, colInd;
    float value;
public:Entry(int *rowid, int *colid, float *val){
        rowInd = *rowid ; colInd = *colid; value = *val;
    }

public:Entry(){

    }
public:void setRowInd(int *ind){
        rowInd = *ind;
    }

public:int* getRowInd(){
        return &rowInd;
    }

public:void setColInd(int ind){
        colInd = ind;
    }

public:int* getColInd(){
        return &colInd;
    }

public:void setValue(float val){
        value = val;
    }

public:float* getValue(){
        return &value;
    }

};

/**
 * Represents a whole matrix object
 */
class Matrix{

    int rowNum, colNum;
    Entry  **Entries;


public:Matrix(int *rownum, int *colnum){
        rowNum = *rownum;
        colNum = *colnum;
    }

public: Matrix (Entry **entries){
        Entries =  entries;
    }

public:void setRowNum(int rownum){

        rowNum = rownum;
    }

public:int* getRowNum(){
        return &rowNum;
    }

public:void setColNum(int colnum){
        colNum = colnum;
    }

public:int* getColNum(){
        return  &colNum;
    }

public:void setEntries(Entry **entries){
        Entries = entries;
    }

public:Entry** getEntries(){
        return Entries;
    }

};

// OBJECT FACTORY

class Factory{
/**
 * Creates a pointer to a new instance of Entry object.
 */
public: static Entry* CreateEntry(int colid, int rowid, float val){
        Entry * e = new Entry(&colid,&rowid,&val);
        return e;

    }

/**
 * Creates a pointer to a new instance of Matrix object.
 */
public:static Matrix* CreateMatrix(Entry  **Entries){
        Matrix* m2 = new Matrix(Entries);
        return  m2;
    }
};

//


class foo{
    int a;

public:foo(int aa){
        a = aa;
    }

public:int getaProp(){
        return a;
    }

public:void setaProp(int aa){
        a =aa;
    }


};


/**
 * Main program logic.
 * @param arg represents the size of the command line argument char array
 * @param args represents the pointer array of command line argument values
 * @return returns a trivial integer
 */
int main(int arg, char** args) {



}