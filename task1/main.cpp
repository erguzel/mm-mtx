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
static bool isClock = false;
//
//global variables;
string option;

//--------utilization functions

//writes given message to console or log file. // todo
void logMessage(string message){
    cout<< message << endl;
}

//-----USER DEFINED TYPES

//initializes the system : parses commandline parameters, sets global switches for the program run mode
class initializer{

public:static void Initialize(int arg, char** args){

        commandLineParser(arg, args);
    }

    //configures run structures according to the run mode
public: static void Configure(){

    }
    //Parses command line parameters and sets the global switches for run mode.
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

//represents a matrix element (this structure could be used for other tasks as well, since 1 cpp file demanded per task, this struct will be reused for other tasks in repeated core manner.)
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

//represents a complete matrix (this structure could be used for other tasks as well, since 1 cpp file demanded per task, this struct will be reused for other tasks in repeated core manner.)
class Matrix{

    int rowNum, colNum;
    Entry  **Entries;

//constructor with row and column number initializers
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

public:void setEntries(Entry entries[]){
        Entries = &entries;
    }

public:Entry** getEntries(){
        return Entries;
    }

};

// OBJECT FACTORY

class Factory{

public: static Entry* CreateEntry(int colid, int rowid, float val){
        Entry * e = new Entry(&colid,&rowid,&val);
        return e;

    }

    //creates a matrix object and returns its adress;
public: static Matrix* CreateMatrix(int rownum, int colnum){
        Matrix * m = new Matrix (&rownum,&colnum);//actual definition in heap with the  adress of parameters
        return m;
    };
public:static Matrix* CreateMatrix(Entry  **Entries){
        Matrix* m2 = new Matrix(Entries);
        return  m2;
    }
};

//


//--------main
int main(int arg, char** args) {


    Factory fac;
    Entry *poent1 = fac.CreateEntry(1,1,1.12);
    Entry *poent2 = fac.CreateEntry(1,2,1.15);
    Entry *poent3 = fac.CreateEntry(1,3,1.17);

    //list of entry pointers pointing real value in heap
    Entry *ents[] = {poent1,poent2,poent3};

    //size of the entry pointer array
    int siz = sizeof(ents)/ sizeof(*ents);

    cout<<"Size of entries: "<<siz<< endl;

    //print any value of entries int the entry pointer array
    for(int i = 0 ; i<siz; i++){
        cout<< *ents[i]->getValue()<< endl;
    }


    poent1->setValue(3.15);

    cout<<"------------";

    //print any value of entries int the entry pointer array
    for(int i = 0 ; i<siz; i++){
        cout<< *ents[i]->getValue()<< endl;
    }

    cout<<"-------Matrix-----"<<endl;


    Matrix *m = fac.CreateMatrix(ents);

    Entry * ents1 =  *m->getEntries();
    int size = sizeof(ents1)/ sizeof(*ents1);


    cout<<size<<endl;




    logMessage("stophere");

}