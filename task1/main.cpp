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

public:void setEntries(Entry **entries){
        Entries = entries;
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

    /*creates a matrix object and returns its adress;
public: static Matrix* CreateMatrix(int rownum, int colnum){
        Matrix * sm = new Matrix (&rownum,&colnum);//actual definition in heap with the  adress of parameters
        return sm;
    };*/
public:static Matrix* CreateMatrix(Entry  **Entries){
        Matrix* m2 = new Matrix(Entries);
        return  m2;
    }
};

//


//--------main
int main(int arg, char** args) {


    Factory fac;

    Entry *newEnt1 = fac.CreateEntry(3,4,1.1);
    Entry *newEnt2 = fac.CreateEntry(3,5,15.5);
    Entry *newEnt3 = fac.CreateEntry(3,6,18.1);
    Entry *newEnt4 = fac.CreateEntry(4,1,13.2);
    Entry *newEnt5 = fac.CreateEntry(4,2,19.1);
    Entry *newEnt6 = fac.CreateEntry(4,3,11.1);

    Entry * sixents[] ={newEnt1,newEnt2,newEnt3, newEnt4,newEnt5,newEnt6};

    Entry * newents[36];
    int entrynum = 0;
    for(int am = 0; am<6 ; am++){

        for(int n = 0; n<6; n++){
            float number =  (am+n+1)*(am+n+2);
            Entry * ent = fac.CreateEntry(am+1,n+1,number);
            newents[entrynum] = ent;
            entrynum++;

        }
    }

   for(int u = 0; u<36; u++){
       cout<< "row ind:"<< *newents[u]->getRowInd()<< " col ind:" << *newents[u]->getColInd()<<" val:" << *newents[u]->getValue() << endl;

   }

    Matrix * mat = fac.CreateMatrix(newents);

    cout<<"matrix starts-----"<<endl;

    for(int h = 0; h<36; h++){
        cout<< " row ind:"<< *mat->getEntries()[h]->getRowInd() << " col ind:" << *mat->getEntries()[h]->getColInd() << " value:" <<*mat->getEntries()[h]->getValue()<< endl;
    }

    cout<<"setting matrix entries to sixentries"<<endl;

    mat->setEntries(sixents);



    for(int h = 0; h<6; h++){
        cout<< " row ind:"<< *mat->getEntries()[h]->getRowInd() << " col ind:" << *mat->getEntries()[h]->getColInd() << " value:" <<*mat->getEntries()[h]->getValue()<< endl;
    }

    logMessage("stophere");

}