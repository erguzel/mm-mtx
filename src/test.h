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
void testMatrixEntries(SequentialMatrix *sqm, string Name) {
    cout << "----TEST MATRIX ENTRIES-----" << endl;
    float value=0;
    int colin=0;
    int rowin=0;
    Entry * ents = sqm->getEntries();
    for(int k = 0; k<sqm->getSizeX()*sqm->getSizeY();k++){
        value =*ents[k].getValue();
        colin = ents[k].getEntryColInd();
        rowin = ents[k].getEntryRowInd();
        cout<<Name<<"("<<rowin<<","<<colin<<"): "<<value<<endl;
        //cout<<"M("<<product->getEntries()[k].getColInd()<<","<<product->getEntries()[k].getRowInd()<<"): "<< product->getEntries()[k].getValue()<<endl;

    }
    cout << "----end TEST MATRIX ENTRIES-----" << endl;
}

/**
 * Writes the row values of given matrix and with desired row number to the console
 * @param sqm represents the pointer of the SequentialMatrix object instance
 * @param rowNum represents the desired row number of the SequentialMatrix object instance
 */
void testGetRow(SequentialMatrix *sqm, int rowNum) {
    cout << "----TEST GET ROW-----" << rowNum << endl;
    for (int i = 0; i < sqm->getSizeX(); i++) {
        cout << *sqm->getRow(rowNum)[i] << endl;
    }
    cout << "---- end TEST GET ROW-----" << endl;
}

/**
 * Writes the column values of given matrix and with desired row number to the console
 * @param sqm represents the pointer of the SequentialMatrix object instance
 * @param colNum represents the desired column number of the SequentialMatrix object instance
 */
void testGetColumn(SequentialMatrix *sqm, int colNum) {
    cout << "----TEST GET COLUMN-----" << colNum << endl;

    for (int i = 0; i < sqm->getSizeY(); i++) {
        cout << *sqm->getColumn(colNum)[i] << endl;
    }

    cout << "----end TEST GET COLUMN-----" << endl;
}

/**
 * Writes the value of the Entry object instance of given matrix with desired row and column numbers to the console
 * @param sqm represents the pointer of SequentialMatrix object at the heap
 * @param rowNum Represents the row number of desired  value
 * @param colNum Represents the column number of desired value
 */
void testGetValue(SequentialMatrix *sqm, int rowNum, int colNum) {
    cout << "----TEST GET VALUE-----" << endl;

    cout << "value for M(" << rowNum << "," << colNum << ")= " << *sqm->getValue(rowNum, colNum) << endl;

    cout << "----end TEST GET VALUE-----" << endl;
}

void testEntryRow(Entry* entryrow, int columnSize){
    for(int i = 0; i < columnSize; i++){
        float value = *entryrow[i].getValue();
        int colin = entryrow[i].getEntryColInd();
        int rowin = entryrow[i].getEntryRowInd();
        int inpos = entryrow[i].getOriginalIndexPosition();

        cout<<"M("<< rowin<<","<<colin<<"):"<<value<<"--> index posistion: "<<inpos<<endl;
    }
}

/**
 * Writes the entry values of the resultant matrix multiplication to the console
 * @param matrixA represents the first matrix in commutator
 * @param matrixB represents the second matrix in commutator
 * @return returns the resultant matrix pointer after multiplication
 */
SequentialMatrix *testMatrixMultiply(SequentialMatrix *matrixA, SequentialMatrix *matrixB) {
    cout << "-------TEST MATRIX MULTIPLY_____" << endl;
    SequentialMatrix *result = matrixA->MultiplyBy(matrixB);
    int count = 0;
    for (int a = 0; a < matrixA->getSizeY() * matrixB->getSizeX(); a++) {
        cout << *result->getEntries()[a].getValue() << endl;
        count++;
    }
    cout << "-------end TEST MATRIX MULTIPLY_____" << endl;
    return result;
}


//---END--- TEST METHODS ---------------



#endif //IHPC_2017_WINTER_TEST_H
