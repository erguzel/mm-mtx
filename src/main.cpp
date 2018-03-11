//
// Created by oe019 on 30.12.17.
//

#include <iostream>
#include <thread>
#include "datatype/SequentialMatrix.h"
#include "test.h"
#include "util/Initializer.h"

#pragma message ("please send -pl flag for running all loops in parallel.")
#pragma message ("please send -cl flag to enable clock time calculation.")
#pragma message ("please send -nt option with parameter for predetermining number of threads. i.e mxgbra -nt 4")

using namespace std;

int main(int arg, char **args) {
    clock_t t1, t2;
    t1 = clock();
    initializer in;
    in.Initialize(arg, args);

    SequentialMatrix *A = new SequentialMatrix(4, 3, 1, false);
    //testEntryRow(A->getEntryRow(6));
    SequentialMatrix *B = new SequentialMatrix(3, 5, 1, false);
    //C needs a row number 5 and any col number
    SequentialMatrix *C = new SequentialMatrix(5,2,1, false);
    //testEntryRow(B->getEntryRow(6));

    testMatrixEntries(A,"A");
    testMatrixEntries(B,"B");
    testMatrixEntries(C,"C");

    SequentialMatrix *result;
    SequentialMatrix *resultant;

    if (Resolver::isParalell) {
        cout << "number of threads: " << Resolver::number_of_threads << endl;
        resultant = A->ParallelMultiplyBy(B);
        result = resultant->ParallelMultiplyBy(C);
        testMatrixEntries(result, "ABC");
        //
        Resolver::finish = clock();
        if(Resolver::isClock){
            float diff((float) Resolver::finish - (float) Resolver::start);
            cout << "runtime : " << diff << " microsc" << endl;
            Resolver::progressTime = diff / CLOCKS_PER_SEC;
            cout << "runtime : " << Resolver::progressTime << " sc" << endl;
        }

    } else {
        cout << "number of threads: " << Resolver::number_of_threads << endl;
        resultant = A->ParallelMultiplyBy(B);
        result = resultant->MultiplyBy(C);
        testMatrixEntries(result, "ABC");
        //
        Resolver::finish = clock();
        if(Resolver::isClock){
            float diff((float) Resolver::finish - (float) Resolver::start);
            cout << "runtime : " << diff << " microsc" << endl;
            Resolver::progressTime = diff / CLOCKS_PER_SEC;
            cout << "runtime : " << Resolver::progressTime << " sc" << endl;
        }
    }

    // delete A;
    //delete B;
    //delete result;


    return 0;
};