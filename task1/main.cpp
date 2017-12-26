// Olgun Ergüzel, 217205614, Computaitonal Physics
// other users
//

#include <iostream>
#include <thread>


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
void logMessage(string message) {
    cout << message << endl;
}

//-----USER DEFINED TYPES

/**
 * Represents a single matrix entry
 */
class Entry {
    //represents column and row indexes in mathematical expression
    int rowInd, colInd;
    //represents the value of the entry
    float value;
    /**
     * Creates and Entry object instance in the heap.
     * @param rowid
     */
public:
    Entry(int rowid, int colid, float val) {
        rowInd = rowid;
        colInd = colid;
        value = val;
    }
/**
 * Instance constructor with no parameter;
 */
    Entry() {}
/**
 * Gets the row index of the Entry instance
 * @returns the row index of the entry
 */
public:
    int getRowInd() {
        return rowInd;
    }

/**
 * Gets the column indice of the Entry instance
 * @returns the column indice of the
 */
public:
    int getColInd() {
        return colInd;
    }
/**
 * Gets the value pointer of the Entry instance
 * @returns the value pointer of the Entry instance
 */
public:
    float *getValue() {
        return &value;
    }

};

/**
 * Represents a matrix object with sequential elements
 */
class SequentialMatrix {

    int _rowNum, _colNum;
    Entry *_Entries;
/**
 * Creates an instance of SequentialMatrix object
 * Represents a single square matrix initialized with the the elements of sequential numbers (optional)
 * @param noninitialize do not fill the matrixs pointers if stays true
 * @param rowNum column size of the square matrix
 * @param colNum row size of the square matrix
 * @param startValu first value of the _Entries array poniter
 */
public:
    SequentialMatrix(int rownum, int colnum, float startvalu = 1, bool nonInitialize = true) {

        //represents the Entry list instances
        _Entries = new Entry[rownum * colnum];
        //represents how many rows of the matrix instance has
        _rowNum = rownum;
        //represents how many columns of the matrix instance has
        _colNum = colnum;

        //if not want to fill the matrix entries while creating the SequentialMatrix instance
        if(!nonInitialize){
            setSequentialEntries(rownum, colnum, startvalu);
        }
    }
/**
 * Parameterless constructor of SequentialMatrix object
 */
    SequentialMatrix() {}
/**
 * Destructor of SequentialMatrix instance object
 */
    ~SequentialMatrix() {
        delete _Entries;
    }
/**
 * Gets column dimension of the Matrix
 */
public:
    int getRowNum() {
        return _rowNum;
    }
/**
 * Gets row dimension of the Matrix
 */
public:
    int getColNum() {
        return _colNum;
    }

    /**
     * Get the value  pointer of the matrix element for the given row and column indices (!= indexes) i.e. M(3,5)
     */
public:
    float *getValue(short rowind, short colind) {

        return (_Entries[rowind * colind - 1].getValue());

    }

/**
 * gets the pointer collection of entry objects
 */
public:
    Entry *getEntries() {
        return _Entries;
    }

    /**
     * @param factor represents the pointer of target matrix to be multiplied.
     * @returns creates another instance of resultant matrix and return its pointer.
     */
public:
    SequentialMatrix *MultiplyBy(SequentialMatrix *factor) {

        SequentialMatrix *product = new SequentialMatrix(_rowNum,_colNum, true);
        float reusltant = 0;
        int index = 0;
        int i =0; int j = 0; int k = 0;
        for (i = 0; i < _rowNum; i++) {
            for (j = 0; j < _colNum; j++) {
               for(k = 0; k< factor->_colNum; k++){
                   reusltant += *getRow(i + 1)[k] * (*factor->getColumn(j + 1)[k]);
                   if(k == factor->getColNum()-1){
                       product->getEntries()[index] = *new Entry(i+1,j+1,reusltant);
                       index++;
                       reusltant = 0;
                   }
               }
            }
        }

        return product;
    }
/**
 * Gets the pointer list of row values for the given row number (1st row, second row etc..)
 */
public:
    float **getRow(short rownum) {

        if(rownum == 0){
            cout<<"error!.. minimum column or row number starts from 1"<<endl;
        }

        float *wholerow[_colNum];
        int entryindex = (rownum - 1) * _colNum;
        int index = 0;
        float *adress;
        Entry ent;
        for (index; index < _colNum; index++) {
            adress = _Entries[index + entryindex].getValue();
            wholerow[index] = adress;
        }
        return wholerow;
    }
/**
 * Gets the pointer list of column values for the given column number (i.e C(2))
 */
public:
    float **getColumn(short colnum) {

        float *wholecolumn[_rowNum];

        int index = 0;
        int entryindex = (colnum - 1);
        float *adress;
        Entry ent;
        for (index; index < _colNum; index++) {
            adress = _Entries[entryindex].getValue();
            wholecolumn[index] = adress;
            entryindex = entryindex + _rowNum;
            //cout<< *asd <<endl;
        }
        return wholecolumn;
    }

/**
 *
 * @param rown row dimension of the matrix object
 * @param coln column dimension of the matrix object
 * @param startvalu first index element of the matrix entries i.e a_11 value
 */
    void setSequentialEntries(int rown, int coln, float startvalu) {

        startvalu = (startvalu == 0) ? 1 : startvalu;
        int index = (startvalu != 1) ? 1 : startvalu;
//        int size = rown*coln ;

        for (int i = 0; i < rown; i++) {

            for (int j = 0; j < coln; j++) {

                _Entries[index - 1] = Entry(i + 1, j + 1, startvalu);
                index++;
                startvalu++;
            }
        }
    }

private:
    void setRandomEntries(int rown, int coln, float interval) {
        //TODO
    }

};

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
                    cout << "the argument " << args[i] << " is not supported yet" << endl;
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

void  test(int arg, char** args){
    clock_t t1,t2;
   t1 = clock();
   SequentialMatrix *sm =  new SequentialMatrix(100, 100, 1, false);
   SequentialMatrix *sm2 = new SequentialMatrix(100, 100, 101 , false);

   SequentialMatrix *result =  sm->MultiplyBy(sm2);

   int count =0;


   for(int a = 0; a < 100; a++){
       cout<< *result->getEntries()[a].getValue()<<endl;
       count++;
   }
   cout<<"number of entry values: "<<count<<endl;


   delete sm;
   delete sm2;
   delete result;
   t2 = clock();
   logMessage("stop here:");
   float diff ((float)t2-(float)t1);
   cout <<"runtime : " << diff<<" microsc"<<endl;
   diff = diff/CLOCKS_PER_SEC;
   cout <<"runtime : " << diff<<" sc"<<endl;

}

/**
 * Main program logic.
 * @param arg represents the size of the command line argument char array
 * @param args represents the pointer array of command line argument values
 */

int main(int arg, char **args) {
    test(arg,args);
    unsigned concurentThreadsSupported = std::thread::hardware_concurrency();

}