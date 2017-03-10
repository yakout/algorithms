#ifndef ALGORITHMS_HEAP_H__
#define ALGORITHMS_HEAP_H__

#include <iostream>
#include <vector>

namespace algo {
    using namespace std;
        /**
         * binary heap data structure
         */
        template<typename T>
        class Heap {
        private:
            int heap_size;
            int length;
            vector<T> __heap;
        public:
            Heap(): __heap(){};
            ~Heap() {};

            inline T parent(int i) { return (i - 1) >> 1; }

            inline T left(int i) { return (i << 1) + 1; }

            inline T right(int i) { return (i << 1) + 2; }

            /**
             * swap element at index i with element at index j.
             * @param i
             * @param j
             */
            inline void swap(int i, int j) {
                __heap[i] ^= __heap[j];
                __heap[j] ^= __heap[i];
                __heap[i] ^= __heap[j];
            }


            /**
             * the running time of 1 heapify operation on a subtree of size n is theta(1)
             * the running time of total heapify operation is given by the recurrence relation
             * T(n) <= T(2n/3) + theta(1)
             * the solution of this recurrence relation by master theorem is O(lgn).
             * @param i the subtree rooted at index i.
             */
            void max_heapify(int i) {
                int greatest = i;
                int left_child = left(i);
                int right_child = right(i);
                if (left_child < heap_size && __heap[i] < __heap[left_child]) {
                    greatest = left_child;
                }
                if (right_child < heap_size && __heap[greatest] < __heap[right_child]) {
                    greatest = right_child;
                }
                if (greatest != i) {
                    swap(i, greatest);
                    max_heapify(greatest);
                }
                return;
            }

            /**
             *
             * @param array
             */
            void build_max_heap(vector<T> array) {
                __heap = array;
                heap_size = (int) array.size();
                for (int i = heap_size / 2; i >= 0; i--) {
                    max_heapify(i);
                }
            }

            /**
             * sorting array with heapsort algorithm
             */
            void sort() {
                for (int i = (int) (__heap.size() - 1); i > 0; i--) {
                    swap(0, i);
                    heap_size--;
                    max_heapify(0);
                }
                heap_size = (int) __heap.size();
            }

            /**
             * print heap's element
             */
            void print_heap() {
                for (int i = 0; i < heap_size; ++i) {
                    printf("value = %d at node = %d\n", __heap[i], i);
                }
            }

        };
};

#endif