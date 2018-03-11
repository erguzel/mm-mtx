//
// Created by oe019 on 30.12.17.
//

#ifndef MATRIX_MULTIPLIER_SEQUENTIALMATRIX_H
#define MATRIX_MULTIPLIER_SEQUENTIALMATRIX_H
#include <omp.h>
#include <iostream>
#include "Entry.h"
#include "../util/Resolver.cpp"


/**
 * Represents a matrix object with sequential elements
 */
class SequentialMatrix {
    //represents column and row lenths of SequentialMatrix object
    int sizeY, sizeX;
    float **_wholeRow;
    float **_wholeColumn;
    Entry *_Column;
    Entry *_Row;
    Entry *_RowEntries;
    Entry *_ColumnEntries;
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
        sizeY = rownum;
        //represents how many columns of the matrix instance has
        sizeX = colnum;
        //represents the Entry list instances
        _Entries = new Entry[sizeY * sizeX];
        //represents how many rows of the matrix instance has
        _Column = new Entry[sizeY];
        _Row = new Entry[sizeX];

        //if not want to fill the matrix entries while creating the SequentialMatrix instance
        if (!nonInitialize) {
            if(Resolver::isParalell){
                setRandomEntriesParallel(sizeY,sizeX);
            }
            else{
                setRandomEntries(sizeY, sizeX);
            }

        }
    }
    void setSequentialEntriesParallel(int rownn, int colln, float startVal){
        float startingValue = startVal;
        if (rownn == 0 || colln == 0) {
            Resolver::logMessage("SequentialMatrix object must have at least 1 row and 1 column.");
            Resolver::logMessage("Quitting..");
            throw std::exception();
        }

        // = (int)((int)startingValue != 1) ? 1 : (int)startingValue;
        int threadID;
        bool isStartValOne = (startingValue==1)? true: false;
        omp_set_num_threads(Resolver::number_of_threads);
#pragma omp parallel
        {
            int index;
            float entryvalue=0;
            float startVl ;
            Entry newEntry;
            threadID = omp_get_thread_num();
            for(int i = threadID; i<sizeY; i=i+Resolver::number_of_threads){
                for(int j = 0; j <sizeX; j++){
                    index = getIndexFromRowColumn(i+1,j+1,rownn,colln);
                    if(isStartValOne){
                        newEntry = Entry(i+1,j+1,index+1);
                        newEntry.setOriginalIndexPosition(index);
                        _Entries[index]= newEntry;
                    } else{
                        startVl = index+sizeX*sizeY;
                        newEntry = Entry(i+1,j+1,startVl+1);
                        newEntry.setOriginalIndexPosition(index);
                        _Entries[index]= newEntry;
                    }

                }

            }
        };
    }

    /**
 *
 * @param rown row dimension of the matrix object
 * @param coln column dimension of the matrix object
 * @param startvalue first index element of the matrix entries i.e a_11 value
 */
    void setSequentialEntries(int rown, int coln, float startvalue) {

        if (rown == 0 || coln == 0) {
            Resolver::logMessage("SequentialMatrix object must have at least 1 row and 1 column.");
            Resolver::logMessage("Quitting..");
            throw std::exception();
        }
        int row, column;
        startvalue = (startvalue == 0) ? 1 : startvalue;
        int index = (startvalue != 1) ? 1 : startvalue;

        for (int i = 0; i < rown; i++) {

            for (int j = 0; j < coln; j++) {

                _Entries[index - 1] = Entry(i + 1, j + 1, startvalue);
                index++;
                startvalue++;
            }
        }
    }

private:void setRandomEntriesParallel(int rown,int coln) {
        if (rown == 0 || coln == 0) {
            Resolver::logMessage("SequentialMatrix object must have at least 1 row and 1 column.");
            Resolver::logMessage("Quitting..");
            throw std::exception();
        }

        int threadID;
        omp_set_num_threads(Resolver::number_of_threads);
#pragma omp parallel
        {
            int index;
            float entryvalue = 0;
            Entry newEntry;
            threadID = omp_get_thread_num();
            for (int i = threadID; i < sizeY; i = i + Resolver::number_of_threads) {
                for (int j = 0; j < sizeX; j++) {
                    index = getIndexFromRowColumn(i + 1, j + 1, rown, coln);
                    entryvalue = Resolver::fRand(0, 1);
                    newEntry = Entry(i + 1, j + 1, entryvalue);
                    newEntry.setOriginalIndexPosition(index);
                    _Entries[index] = newEntry;


                }
            };

        }
    }
private:void setRandomEntries(int rown, int coln){

        if (rown == 0 || coln == 0) {
            Resolver::logMessage("SequentialMatrix object must have at least 1 row and 1 column.");
            Resolver::logMessage("Quitting..");
            throw std::exception();
        }
        float randNum = 0;
        int row, column;
        int index =0;
        for (int i = 0; i < rown; i++) {
            for (int j = 0; j < coln; j++) {
                randNum = Resolver::fRand(0,1);
                _Entries[index ] = Entry(i + 1, j + 1, randNum);
                index++;
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
    int getSizeY() {
        return sizeY;
    }
/**
 * Gets row dimension of the Matrix
 */
public:
    int getSizeX() {
        return sizeX;
    }
    /**
     * Get the value  pointer of the matrix element for the given row and column indices (!= indexes) i.e. M(3,5)
     */
public:
    float *getValue(short rowind, short colind) {
        if (rowind == 0 || colind == 0) {
            Resolver::logMessage("SequentialMatrix object must have at least 1 row and 1 column.");
            Resolver::logMessage("Quitting..");
            throw std::exception();
        }
        if (rowind > sizeY || colind > sizeX) {
            Resolver::logMessage("You demand a nonexisting element..");
            Resolver::logMessage("Quitting..");
            throw std::exception();
        }
        int index = (colind - 1) + ((rowind - 1) * sizeX);
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
     * Returns true if given matrices are multipliable
     * @param firstMtxcol column number of first matrix.
     * @param secondMtxrow row number of second matrix
     */
public:
    bool isMultipliable(int firstMtxcol, int secondMtxrow) {
        return (firstMtxcol == secondMtxrow) ? true : false;
    }

    /**
     * Gets the element index of the (i,j) element of the (n,m) matrix
     */
private:
    int getIndexFromRowColumn(int rowNumber, int columnNumber, int ColumnSize, int RowSize) {
        int currentIndex = (RowSize+((rowNumber-1)*RowSize) - (RowSize-columnNumber))-1;
        return currentIndex;
    }

#define NUMBER_OF_THEADS 2
public:
    SequentialMatrix *ParallelMultiplyBy(SequentialMatrix *factorMatrix) {
        if (Resolver::isClock) {
            Resolver::start = clock();
        }//for enabling clock switch sent from comandline
        if (!isMultipliable(sizeX, factorMatrix->getSizeY())) {
            Resolver::logMessage("error!..matrix dimensions not match!, quitting..");
            throw std::exception();//todo end program
        }
        int factorMatrixColNum = factorMatrix->getSizeX();
        SequentialMatrix *product = new SequentialMatrix(sizeY, factorMatrixColNum, true);


        omp_set_num_threads(Resolver::number_of_threads);
#pragma omp parallel
        {
            float resultant;
            std::cout << omp_get_thread_num() << " : is thread id" << std::endl;
            int i, j, k;
            int rowindice;
            int colindice;

            int index = 0;
            Entry ent;
            Entry *val ;
            Entry *val1;
            int nOfThreads;
            int threadId;

            threadId = omp_get_thread_num();

#pragma omp for
            for (i = threadId; i < sizeY; i = i + Resolver::number_of_threads) {
                rowindice = (i+1);
                val = getEntryRow(rowindice);
                for (j = 0; j < factorMatrix->getSizeX(); j++) {
                    colindice = j+1;
                    val1 = factorMatrix->getEntryColumn(colindice);
                    for (k = 0; k < sizeX; k++) {
                        resultant += *val[k].getValue() * (*val1[k].getValue());
                        if(k==sizeX-1){
                            index = getIndexFromRowColumn(rowindice, colindice, sizeY,factorMatrixColNum);
                            ent = *new Entry(rowindice, colindice, resultant);
                            ent.setOriginalIndexPosition(index);
                            product->getEntries()[ent.getOriginalIndexPosition()] = ent;
                            resultant = 0;
                        }
                    }
                }
            }

        }

        //for(int a=0;a<product->sizeY*product->sizeX; a++){
        //    cout<<"-rowin="<<product->getEntries()[a].getEntryRowInd()<<"--colin="<<product->getEntries()[a].getEntryColInd()<<"--value"<<*product->getEntries()[a].getValue()<<"--indexpos"<<product->getEntries()[a].getOriginalIndexPosition()<<endl;
        //  }

        return product;

    }
    /**
     * @param factor represents the pointer of target matrix to be multiplied.
     * @returns creates another instance of resultant matrix and return its pointer.
     */
public:
    SequentialMatrix *MultiplyBy(SequentialMatrix *factor) {
        // bool isMultipliable = (sizeX == factor->getSizeY())? true:false;

        if (!isMultipliable(sizeX, factor->getSizeY())) {
            Resolver::logMessage("error!..matrix dimensions not match!, quitting..");
            throw std::exception();
        }
        int colsize = factor->getSizeX();
        SequentialMatrix *product = new SequentialMatrix(sizeY, colsize, true);
        float reusltant = 0;
        int index = 0;
        int i;
        int j;
        int k;
        for (i = 0; i < sizeY; i++) {
            for (j = 0; j < factor->getSizeX(); j++) {
                for (k = 0; k < sizeX; k++) {
                    reusltant += *getRow(i + 1)[k] * (*factor->getColumn(j + 1)[k]);
                    if (k == sizeX - 1) {
                        product->getEntries()[index] = *new Entry(i + 1, j + 1, reusltant);
                        index++;
                        reusltant = 0;
                    }
                }
            }
        }

        return product;
    }


public:
    Entry *getEntryColumn(int colnum) {
        if (colnum == 0 || colnum > sizeX) {
            std::cout << "error!.. You demanded a nonexisting entry value. Minimum column or row number starts from 1"
                 << std::endl;
            throw std::exception(); //TODO ends the program
        }

        int topIndex = 0;
        topIndex = (colnum - 1) + (getSizeX() * (sizeY - 1));//todo 3 is row num but not initializing?
        int index = 0;
        Entry ent;
        for (int i = colnum - 1; i < topIndex + 1; i = i + sizeX) {
            _Column[index] = _Entries[i];
            index++;
        }
        return _Column;
        //_wholeColumn = wholecolumn;
        //return _wholeColumn;
    }

public:
    Entry *getEntryRow(int rowNum) {
        if (rowNum == 0 || rowNum > sizeY) {
            std::cout << "error!.. You demanded a nonexisting entry value. Minimum column or row number starts from 1"
                 << std::endl;
            throw std::exception(); //TODO should end the program
        }

        //index that desired row's starting point index position in the _Entries array
        int downidex = (rowNum - 1) * sizeX;
        //to count row size
        int index = 0;
        //for entry value
        float value;
        Entry ent;
        for (index; index < sizeX; index++) {

            _Row[index] = _Entries[downidex];
            downidex++;
        }

        return _Row;

    }


/**
 * Gets the pointer list of row values for the given row number (1st row, second row etc..)
 */
public:
    float **getRow(int rownum) {
        float *wholerow[sizeX];
        if (rownum == 0 || rownum > sizeY) {
            std::cout << "error!.. You demanded a nonexisting entry value. Minimum column or row number starts from 1"
                 << std::endl;
            throw std::exception(); //TODO should end the program
        }
        int entryindex = (rownum - 1) * sizeX;
        int index = 0;
        float *adress;
        Entry ent;
        for (int index = 0; index <= sizeX; index++) {
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
        if (colnum == 0 || colnum > sizeX) {
            std::cout << "error!.. You demanded a nonexisting entry value. Minimum column or row number starts from 1"
                 << std::endl;
            throw std::exception(); //TODO ends the program
        }
        float *wholecolumn[sizeY];
        float *adress;
        int topIndex = (colnum - 1) + (sizeX * (sizeY - 1));
        int index = 0;
        for (int i = colnum - 1; i < topIndex + 1; i = i + sizeX) {
            adress = _Entries[i].getValue();
            wholecolumn[index] = adress;
            index++;
        }
        _wholeColumn = wholecolumn;
        return _wholeColumn;
    }
};


#endif //MATRIX_MULTIPLIER_SEQUENTIALMATRIX_H
