//
// Created by oe019 on 30.12.17.
//

#ifndef IHPC_2017_WINTER_ENTRY_H
#define IHPC_2017_WINTER_ENTRY_H

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


#endif //IHPC_2017_WINTER_ENTRY_H
