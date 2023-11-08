// Compiler options
// g++ -o main algorithm.cpp


/*
    Key's to a good cryptographic hash algorithm.


    Deterministic, The same input gives the same hashed output every time.
    Fast,
    Irreversible, you cannot reverse the algorithm and take the hash and convert it back to the string
    Utilize "avalanche effect", strings that are slightly altered should give vastly different results, ex. "fish" -> 5j4i, "fish1" -> // Compiler options
// g++ -o main algorithm.cpp
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>


using namespace std;
using namespace chrono;


// Insertion-sort algorithm
float InsertionSort(int Array[], int n)
{
    // Start timing, using chrono (DEBUG)
    time_point<steady_clock> start = steady_clock::now();


    float time;


    int i;
    int key;
    int j;


    for(i = 1; i < n;)
    {
        key = Array[i];
        j = i - 1;


        while((j >= 0) && (Array[j] > key))
        {
            Array[j + 1] = Array[j];
            j = j - 1;
        }
        Array[j + 1] = key;


        i++;
    }


    // Stop timing (DEBUG)
    time_point<steady_clock> end = steady_clock::now();
    duration<double, milli> fp_mi = end - start;
    time = fp_mi.count();


    return time;
}


main(int argc, char **argv)
{  
    int n = 500;
    float time;


    float AverageTime;


    vector<float> SumVector;


    for(int im = 0; im < 200;)
    {  
        int A[n];


        for(int i = 0; i < n;)
        {
            A[i] = rand() % 300 + 1;
            i++;
        }


        time = InsertionSort(A, n);


        cout << n << ";" << time << endl;


        im++;
        n = n + 100;
    }


    for(int Number = 0; Number < SumVector.size()-1;)
    {
        AverageTime += SumVector[Number];
        Number++;
    }


    AverageTime = AverageTime/SumVector.size();


    // Average time of 3000 elements over x arrays.
    //cout << AverageTime << endl;
}