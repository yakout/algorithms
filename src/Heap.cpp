//#include "library.h"

#include <iostream>
#include <vector>
#include "Heap.h"

// max heapify --> O(lgn)
// build max Heap from unsorted array --> O(n)
// Heap sort --> O(nlgn)
// max Heap insert && get max -> O(lgn)

using namespace std;


//class Max_heap: public algo::Heap {
//
//};

/**
 * demo
 */
int main(int argc, char *argv[]) {
    cout << "Hello, World!" << endl;
    algo::Heap<int> heap1;
    heap1.build_max_heap(vector<int>{4, 1, 3, 2, 16, 9, 10, 14, 8, 7});
    heap1.sort();
    heap1.print_heap();
    return 0;
}