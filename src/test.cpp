//
// Created by Ahmed Yakout on 3/11/17.
//

#include <iostream>
#include <vector>
#include "heap.h"
#include "bubble_sort.h"
#include "merge_sort.h"
#include "insertion_sort.h"
#include "selection_sort.h"
#include <chrono>


// max heapify --> O(lgn)
// build max Heap from unsorted array --> O(n)
// Heap sort --> O(nlgn)
// max Heap insert && get max -> O(lgn)

using namespace std;
using namespace algo;

/**
 * demo
 */
int main(int argc, char *argv[]) {
    vector<int> v {3, 5, 9, 6, 8, 20, 10, 12, 18, 9};
//    Heap<int> heap1;
//    Heap<int> heap2(v);
//    heap1.build_max_heap(vector<int>{4, 1, 3, 2, 16, 9, 10, 14, 8, 7});
//    heap1.sort();
//    cout << heap1.extract_max(v) << endl;
//    heap1.toString();

//    bubble_sort(v);
//    merge_sort(v, 0, v.size() - 1);
//    insertion_sort(v);
    auto t1 = std::chrono::high_resolution_clock::now();
    selection_sort(v);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto diff = t2-t1;

    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << endl;
    }
    cout << "time taken: " << diff.count() << endl;
    return 0;
}