//
// Created by oe019 on 30.12.17.
//

#ifndef IHPC_2017_WINTER_TEST_H
#define IHPC_2017_WINTER_TEST_H

#include "datatype/SequentialMatrix.h"
#include "iostream"

using namespace std;

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
#endif //IHPC_2017_WINTER_TEST_H
