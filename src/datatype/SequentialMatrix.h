//
// Created by oe019 on 30.12.17.
//

#ifndef IHPC_2017_WINTER_SEQUENTIALMATRIX_H
#define IHPC_2017_WINTER_SEQUENTIALMATRIX_H

#include <iostream>
#include "Entry.h"


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
            std::cout<<"SequentialMatrix object must have at least 1 row and 1 column."<<std::endl;
            std::cout<<"Quitting.."<<std::endl;
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
            std::cout<<"SequentialMatrix object must have at least 1 row and 1 column."<<std::endl;
            std::cout<<"Quitting.."<<std::endl;
            throw std::exception();
        }
        if(rowind>_rowNum || colind > _colNum){
            std::cout<<"You demand a nonexisting element.."<<std::endl;
            std::cout<<"Quitting.."<<std::endl;
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
            std::cout<<"error!..matrix dimensions not match!, quitting.."<<std::endl;
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
            std::cout<<"error!.. You demanded a nonexisting entry value. Minimum column or row number starts from 1"<<std::endl;
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
            std::cout<<"error!.. You demanded a nonexisting entry value. Minimum column or row number starts from 1"<<std::endl;
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


#endif //IHPC_2017_WINTER_SEQUENTIALMATRIX_H
