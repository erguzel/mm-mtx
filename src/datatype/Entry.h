//
// Created by oe019 on 30.12.17.
//

#ifndef MATRIX_MULTIPLIER_ENTRY_H
#define MATRIX_MULTIPLIER_ENTRY_H

class Entry {
    //represents column and row indexes in mathematical expression
    int entryX=0, entryY=0, OriginalIndexPosition=0;
    //represents the value of the entry
    float value;

    /**
     * Creates and Entry object instance in the heap.
     * @param rowid Represents the row id of the matrix entry
     * @param colid Represents the col id of the matrix entry
     * @param val Represents the value of the matrix entry
     */
public:
    Entry(int rowid, int colid, float val) {
        entryX = rowid;
        entryY = colid;
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
    int getEntryRowInd() {
        return entryX;
    }

public:void setOriginalIndexPosition(int positionIndex){

        OriginalIndexPosition = positionIndex;// todo error handle
    }

public:int getOriginalIndexPosition(){
        return OriginalIndexPosition;
    }

/**
 * Gets the column indice of the Entry instance
 * @returns the column indice of the
 */
public:
    int getEntryColInd() {
        return entryY;
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


#endif //MATRIX_MULTIPLIER_ENTRY_H
