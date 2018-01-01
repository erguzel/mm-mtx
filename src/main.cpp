//
// Created by oe019 on 30.12.17.
//

#include <iostream>
#include <thread>
#include <omp.h>
#include "datatype/SequentialMatrix.h"
#include "test.h"
#include "util/Initializer.h"

#pragma message ("please send -pl flag for running all loops in parallel.")
#pragma message ("please send -cl flag to enable clock time calculation.")
#pragma message ("please send -nt option with parameter for predetermining number of threads. i.e mxgbra -nt 4")

using namespace std;

//-------<MAIN>-----------------------//

int main(int arg, char **args) {

    int nthreads, tid;

#pragma paralel private(tid)
    {tid = omp_get_thread_num();
        nthreads=omp_get_num_threads();
        cout<< "threadNUm: " <<tid<<"--"<<"nthreads: "<< nthreads <<endl;
#pragma omp for
        for (int i = 0; i < 100; i++) {
            cout << "number: " << i << endl;

        }
    }

/*
#pragma omp parallel private(tid)
    {

        tid = ::omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        //Only master thread does this
        if (tid == 0) {
            nthreads = ::omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }

    }
*/
    //testParalelLoopBasic() ;

    //Initializer i;
    //i.Initialize(arg,args);
    //clock_t t1,t2;
    //t1 = clock();
    /*
    SequentialMatrix * A = new SequentialMatrix(6,6,1, false);
    SequentialMatrix * B = new SequentialMatrix(6,6,37, false);
    SequentialMatrix * result = A->MultiplyBy(B);
    testMatrixEntries(result);
    testGetRow(result,3);
    testGetColumn(result,3);
    testGetValue(result,3,3);
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
*/
    return 0;
};