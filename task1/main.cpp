// Olgun Ergüzel, 217205614, Computaitonal Physics
// other users
//

#include <iostream>
#include <map>
#include <list>

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
 * Represents a single matrix entry
 */
class Entry{
    int rowInd, colInd;
    float value;
public:Entry(int rowid, int colid, float val){
        rowInd = rowid ; colInd = colid; value = val;
    }

    Entry() {}

public:int getRowInd(){
        return rowInd;
    }


public:int getColInd(){
        return colInd;
    }

public:float* getValue(){
        return &value;
    }

};


class IMatrix{ //TODO

};

/**
 * Represents a matrix object with random or sequential elements
 */
class SequentialMatrix{

    int _rowNum, _colNum;
    Entry  *_Entries;
/**
 * Creates an instance of matrix object
 */
public:SequentialMatrix(int rownum, int colnum, float startvalu=1){
        _Entries = new Entry[rownum*colnum];
        _rowNum = rownum;
        _colNum = colnum;

        setSequentialEntries(rownum,colnum,startvalu);
    }
~SequentialMatrix(){
        delete _Entries;
    }
/**
 * Get row dimension of the Matrix.
 */
public:int getRowNum(){
        return _rowNum;
    }
/**
 * Gets the column dimension of the Matrix
 */
public:int getColNum(){
        return  _colNum;
    }

    /**
     * Gets the value of the matrix element for the given row and column indexes i.e. M(3,5)
     */
public:float* getValue(short rowind, short colind){

        return (_Entries[rowind*colind-1].getValue());

    }
/**
 * Gets the pointer list of column values for the given row number (1st row, second row etc..)
 */
public: float**  getRow(short rownum){

        float *wholerow[_colNum];
        int count = (rownum-1)*_colNum;
        short index = 0;
        for(count; count<count+_colNum; count++ ){
            wholerow[index]= _Entries[count].getValue();
            index++;
        }

    }

public:std::list<float> getColumn(short colNum){
//TODO
    }

public:Entry* getEntries(){
        return _Entries;
    }

/**
 *
 * @param rown row dimension of the matrix object
 * @param coln column dimension of the matrix object
 * @param startvalu first a_11 value of the matrix
 */
void setSequentialEntries(int rown, int coln, float startvalu){

        startvalu = (startvalu == 0)? 1 : startvalu;
        int index=(startvalu != 1)? 1 : startvalu;
//        int size = rown*coln ;

        for(int i = 0; i < rown; i++){

            for(int j=0; j<coln; j++){

                _Entries[index-1] = Entry(i+1,j+1,startvalu);
                index++;
                startvalu++;
            }
        }
    }

private:void setRandomEntries(int rown, int coln,float interval){
    //TODO
    }

};

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
 * Main program logic.
 * @param arg represents the size of the command line argument char array
 * @param args represents the pointer array of command line argument values
 * @return returns a trivial integer
 */
int main(int arg, char** args) {

    SequentialMatrix *sm = new SequentialMatrix(6,6,1);
    SequentialMatrix *sm2 = new SequentialMatrix(6,6,36);


    for(int i = 0; i < 36; i++){
        cout<<"matrix1: "<< *sm->getEntries()[i].getValue()<<" matrix2: ";
        cout<< *sm2->getEntries()[i].getValue()<<endl;
    }

    delete sm;
    delete sm2;

    logMessage("stop here");
}