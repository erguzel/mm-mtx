//
// Created by oe019 on 30.12.17.
//

#include <iostream>
#include <thread>
#include "datatype/SequentialMatrix.h"
#include "test.h"

#pragma message ("please use -a or -b options for subquestions of task1.")
#pragma message ("please send -clock flag to enable clock time calculation.")

using namespace std;

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