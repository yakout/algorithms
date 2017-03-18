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
#include "quick_sort.h"
#include <chrono>
#include "avl_tree.h"


// max heapify --> O(lgn)
// build max Heap from unsorted array --> O(n)
// Heap sort --> O(nlgn)
// max Heap insert_key && get max -> O(lgn)

using namespace std;
using namespace algo;

/**
 * demo
 */
int main(int argc, char *argv[]) {
//    vector<int> v {3, 5, 9, 6, 8, 20, 10, 12, 18, 9};
////    Heap<int> heap1;
//    Heap<int> heap2(v);
////    heap1.build_max_heap(vector<int>{4, 1, 3, 2, 16, 9, 10, 14, 8, 7});
////    heap1.sort();
////    cout << heap1.extract_max(v) << endl;
////    heap1.toString();
//
////    bubble_sort(v);
////    insertion_sort(v);
//
//
//
//
//    auto t1 = std::chrono::high_resolution_clock::now();
////    merge_sort(v, 0, v.size() - 1);
//    selection_sort(v);
////    heap2.sort();
////    quick_sort(v, 0, v.size() - 1);
//    auto t2 = std::chrono::high_resolution_clock::now();
//
//    auto diff = t2-t1;
//
//    for (int i = 0; i < v.size(); ++i) {
//        cout << v[i] << endl;
//    }
//    cout << "time taken: " << diff.count() << endl;

    AVL<int> test;
//    test.insert_key("g");
//    test.insert_key("h");
//    test.insert_key("f");
//    test.insert_key("z");
//    test.insert_key("b");
//    test.insert_key("n");
//    test.insert_key("v");
//    test.insert_key("x");
//    test.insert_key("z");
//    test.insert_key("y");
//    test.insert_key("i");
//    test.insert_key("q");
//    test.insert_key("a");

    // test case #1
     /** left_left node = 13
         left_right node = 13
         left_left node = 4
         left_right node = 5
     */
//    test.insert_key(13);
//    test.insert_key(8);
//    test.insert_key(5);
//    test.insert_key(9);
//    test.insert_key(4);
//    test.insert_key(6);
//    test.insert_key(12);
//    test.insert_key(2);
//    test.insert_key(1);
//    test.insert_key(3);


//    test.to_string();
    test.load_file("/Users/nesmayakout/CLionProjects/algorithms/n.txt");

    cout << "height of tree = " << test.height() << endl;
    cout << "minimum value = " << test.minimum(test.get_tree())->value << endl;
    cout << "maximum value = " << test.maximum(test.get_tree())->value << endl;
    cout << "root value = " << test.get_tree()->value << endl;
    return 0;
}