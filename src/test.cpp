//
// Created by Ahmed Yakout on 3/11/17.
//

#include <iostream>
#include <vector>
#include "data_structures/heap.h"
#include "sorting_algorithms/bubble_sort.h"
#include "sorting_algorithms/merge_sort.h"
#include "sorting_algorithms/insertion_sort.h"
#include "sorting_algorithms/selection_sort.h"
#include "sorting_algorithms/quick_sort.h"
#include <chrono>
#include "data_structures/avl_tree.h"
#include "data_structures/dictionary.h"



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
    // vector<int> v {3, 5, 9, 6, 8, 20, 10, 12, 18, 9};
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
//    auto t11 = std::chrono::high_resolution_clock::now();
//    merge_sort(v, 0, v.size() - 1);
//    selection_sort(v);
//    heap2.sort();
//    quick_sort(v.begin(), v.end() - 1);
//    auto t22 = std::chrono::high_resolution_clock::now();
//
//    auto diff1 = t22-t11;
//
//    for (int i = 0; i < v.size(); ++i) {
//        cout << v[i] << endl;
//    }
//    cout << "time taken: " << diff1.count() << endl;
//




    AVL<int> test;
    // test case #1

//    auto t1 = std::chrono::high_resolution_clock::now();
//
    // // screen shot 1
    // test.insert_key(41);
    // test.insert_key(5);
    // test.insert_key(74);
    // test.insert_key(15);
    // test.insert_key(78);
    // test.insert_key(90);
    // test.insert_key(29);
    // test.insert_key(93);
    // test.insert_key(34);
    // test.insert_key(27);
    // test.insert_key(33);
    // test.insert_key(30);
    // test.insert_key(43);
    // test.insert_key(26);
    // test.insert_key(52);
    // test.insert_key(32);
    // test.insert_key(87);
    // test.insert_key(22);
    // test.insert_key(77);
    // test.insert_key(94);
    // test.insert_key(20);
    // test.insert_key(24);
    // test.insert_key(76);
    // test.insert_key(51);
    test.insert_key(1);
    test.insert_key(2);
    test.insert_key(3);
    test.insert_key(4);
    test.insert_key(5);
    test.insert_key(6);
    test.insert_key(7);
    test.insert_key(8);
    test.insert_key(9);
    test.insert_key(10);
    test.insert_key(11);
    test.insert_key(12);
    test.insert_key(13);
    test.insert_key(14);
    test.insert_key(15);
    test.insert_key(16);
    test.insert_key(17);
    test.insert_key(18);
    test.insert_key(19);
    test.insert_key(20);


    // // screen shot 2
    // test.delete_key(1);

//    auto t2 = std::chrono::high_resolution_clock::now();


    // dictionary dict;

    // dict.load("/Users/nesmayakout/Desktop/Lab2/TestCases/dictionary.txt");
    // cout << dict.size() << endl;
    // cout << dict.height() << endl;

    // ifstream delet_infile("/Users/nesmayakout/Desktop/Lab2/TestCases/deletions.txt");

    // string line1;
    // int flag = 0;
    // while (getline(delet_infile, line1)) {
    //     dict.remove(line1);
    // }

    // cout << dict.size() << endl;
    // cout << dict.height() << endl;
    // cout << "flag = " << flag;

    print_ascii_node(test.get_tree());
    cout <<  "height = " << test.height() << endl;




//
//
//
//
//
//
////    test.load_file("/Users/nesmayakout/CLionProjects/algorithms/n.txt");
//    auto diff = t2 - t1;


//    struct X {
//        X *l;
//        X(): l(nullptr) {};
//    };
//
//    X* a = new X;
//    X* b = new X;
//    a->l = b;
//    b->l = a;



//    dictionary dict;
//    auto t1 = std::chrono::high_resolution_clock::now();
//    dict.load("/Users/nesmayakout/CLionProjects/algorithms/words.txt");
//    auto t2 = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double>  diff = t2 - t1;

//    cout << "height of tree = " << test.height() << endl;
//    cout << "minimum value = " << test.minimum(test.get_tree())->value << endl;
//    cout << "maximum value = " << test.maximum(test.get_tree())->value << endl;
//    cout << "root value = " << test.get_tree()->value << endl;
//    dict.print_statistics();
//    cout << "time taken: " << diff.count() << endl;
    return 0;
}