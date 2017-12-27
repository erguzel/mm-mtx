// Olgun Ergüzel, 217205614, Computaitonal Physics
// other users
//

#include <iostream>
#include <thread>
#include <signal.h>


#pragma message ("please use -a or -b options for subquestions of task1.")
#pragma message ("please send -clock flag to enable clock time calculation.")

using namespace std;

//-----GLOBAL VARIABLES-------------
/**
 * Accepted commandline parameters
 */
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
//--END--- GLOBAL VARIABLES-------



//--------UTILIZATION FUNCTIONS
/**
 * Writes a simple string message to the console
 * @param message the string consol message
 */
void logMessage(string message) {
    cout << message << endl;
}
//--END----UTILIZATION FUNCTIONS -------------



//-------USER DEFINED TYPES
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
    //represents column and row lenths of SequentialMatrix object
    int _rowNum, _colNum;
    float ** _wholeRow;
    float ** _wholeColumn;
    //Represents the pointer collection of Entry instances
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
 *
 * @param rown row dimension of the matrix object
 * @param coln column dimension of the matrix object
 * @param startvalue first index element of the matrix entries i.e a_11 value
 */
    void setSequentialEntries(int rown, int coln, float startvalue) {

        if(rown == 0 || coln==0){
            logMessage("SequentialMatrix object must have at least 1 row and 1 column.");
            logMessage("Quitting..");
            throw std::exception();
        }
        int row, column;
        startvalue = (startvalue == 0) ? 1 : startvalue;
        int index = (startvalue != 1) ? 1 : startvalue;
//        int size = rown*coln ;

        for (int i = 0; i < rown; i++) {

            for (int j = 0; j < coln; j++) {

                _Entries[index - 1] = Entry(i + 1, j + 1, startvalue);
                index++;
                startvalue++;
            }
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
        if(rowind == 0 || colind == 0){
            logMessage("SequentialMatrix object must have at least 1 row and 1 column.");
            logMessage("Quitting..");
            throw std::exception();
        }
        if(rowind>_rowNum || colind > _colNum){
            logMessage("You demand a nonexisting element..");
            logMessage("Quitting..");
            throw std::exception();
        }
        int index = (colind-1) + ((rowind-1) * _colNum);
        return (_Entries[index].getValue());
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
        bool isMultipliable = (_colNum == factor->getRowNum())? true:false;

        if(!isMultipliable){
            logMessage("error!..matrix dimensions not match!, quitting..");
            throw std::exception();
        }
        SequentialMatrix *product = new SequentialMatrix(_rowNum,factor->getColNum(),true);
        float reusltant = 0;
        int index = 0;
        int i =0; int j = 0; int k = 0;
        for (i = 0; i < _rowNum; i++) {
            for (j = 0; j < factor->getColNum(); j++) {
                for(k = 0; k< _colNum; k++){
                    reusltant += *getRow(i + 1)[k] * (*factor->getColumn(j + 1)[k]);
                    if(k == _colNum-1){
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
    float **getRow(int rownum) {
        float *wholerow[_colNum];
        if(rownum == 0 || rownum > _rowNum ){
            cout<<"error!.. You demanded a nonexisting entry value. Minimum column or row number starts from 1"<<endl;
            throw std::exception(); //TODO should end the program
        }
        int entryindex = (rownum - 1) * _colNum;
        int index = 0;
        float *adress;
        Entry ent;
        for (int index=0; index <= _colNum; index++) {
            adress = _Entries[index + entryindex].getValue();
            wholerow[index] = adress;
        }
        _wholeRow = wholerow;

        return _wholeRow;

    }
/**
 * Gets the pointer list of column values for the given column number (i.e C(2))
 */
public:
    float **getColumn(short colnum) {
        if(colnum == 0 || colnum >_colNum ){
            cout<<"error!.. You demanded a nonexisting entry value. Minimum column or row number starts from 1"<<endl;
            throw std::exception(); //TODO ends the program
        }
        float *wholecolumn[_rowNum];
        float* adress;
        int topIndex = (colnum-1)+(_colNum*(_rowNum-1));
        int index = 0;
        for(int i = colnum-1; i<topIndex+1; i = i + _colNum){
            adress = _Entries[i].getValue();
            wholecolumn[index] = adress;
            index++;
        }
        _wholeColumn = wholecolumn;
        return _wholeColumn;
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
//-----END -- USER DEFINED TYPES-------------



//------ TEST METHODS -----------------
/**
 * Writes the Entry values of the matrix to the console screen.
 * @param sqm The pointer of the SequentialMatrix object at the heap
 */
void testMatrixEntries(SequentialMatrix *sqm) {
    cout<<"----TEST MATRIX ENTRIES-----"<<endl;
    for (int i = 0; i < sqm->getRowNum()*sqm->getColNum(); i++) {
        cout<<"M("<< sqm->getEntries()[i].getRowInd()<<","<<sqm->getEntries()[i].getColInd()<<")= "<<*sqm->getEntries()[i].getValue()<<endl;
    }
    cout<<"----end TEST MATRIX ENTRIES-----"<<endl;
}
/**
 * Writes the row values of given matrix and with desired row number to the console
 * @param sqm represents the pointer of the SequentialMatrix object instance
 * @param rowNum represents the desired row number of the SequentialMatrix object instance
 */
void  testGetRow(SequentialMatrix *sqm, int rowNum){
    cout<<"----TEST GET ROW-----"<<endl;
    for(int i = 0; i < sqm->getColNum(); i++){
        cout<<*sqm->getRow(rowNum)[i]<<endl;
    }
    cout<<"---- end TEST GET ROW-----"<<endl;
}
/**
 * Writes the column values of given matrix and with desired row number to the console
 * @param sqm represents the pointer of the SequentialMatrix object instance
 * @param colNum represents the desired column number of the SequentialMatrix object instance
 */
void testGetColumn(SequentialMatrix *sqm, int colNum){
    cout<<"----TEST GET COLUMN-----"<<endl;

    for(int i = 0; i < sqm->getRowNum(); i++){
        cout<<*sqm->getColumn(colNum)[i]<<endl;
    }

    cout<<"----end TEST GET COLUMN-----"<<endl;
}
/**
 * Writes the value of the Entry object instance of given matrix with desired row and column numbers to the console
 * @param sqm represents the pointer of SequentialMatrix object at the heap
 * @param rowNum Represents the row number of desired  value
 * @param colNum Represents the column number of desired value
 */
void testGetValue(SequentialMatrix* sqm, int rowNum, int colNum){
    cout<<"----TEST GET VALUE-----"<<endl;

    cout<< "value for M("<<rowNum<<","<<colNum<<")= " << *sqm->getValue(rowNum,colNum)<<endl;

    cout<<"----end TEST GET VALUE-----"<<endl;
}
/**
 * Writes the entry values of the resultant matrix multiplication to the console
 * @param matrixA represents the first matrix in commutator
 * @param matrixB represents the second matrix in commutator
 * @return returns the resultant matrix pointer after multiplication
 */
SequentialMatrix*  testMatrixMultiply(SequentialMatrix *matrixA, SequentialMatrix *matrixB){
    cout<<"-------TEST MATRIX MULTIPLY_____"<<endl;
   SequentialMatrix *result =  matrixA->MultiplyBy(matrixB);
   int count =0;
   for(int a = 0; a < matrixA->getRowNum()*matrixB->getColNum(); a++){
       cout<< *result->getEntries()[a].getValue()<<endl;
       count++;
   }
    cout<<"-------end TEST MATRIX MULTIPLY_____"<<endl;
    return  result;
}


//---END--- TEST METHODS ---------------



//-------<MAIN>-----------------------//
int main(int arg, char **args) {

    clock_t t1,t2;
    t1 = clock();
    SequentialMatrix * A = new SequentialMatrix(4,3,1, false);
    SequentialMatrix * B = new SequentialMatrix(3,4,13, false);
    SequentialMatrix * result = A->MultiplyBy(B);
    testMatrixEntries(result);
    testGetRow(result,3);
    testGetColumn(result,4);
    testGetValue(result,3,4);
    cout<<"---End of the program-----"<<endl;

    t2=clock();
    float diff ((float)t2-(float)t1);
    cout <<"runtime : " << diff<<" microsc"<<endl;
    diff = diff/CLOCKS_PER_SEC;
    delete A;
    delete B;
    delete result;
    cout <<"runtime : " << diff<<" sc"<<endl;

   // unsigned concurentThreadsSupported = std::thread::hardware_concurrency();

    return 0;
};