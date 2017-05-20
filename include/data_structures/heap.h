#ifndef ALGORITHMS_HEAP_H__
#define ALGORITHMS_HEAP_H__

#include <iostream>
#include <vector>
#include <string.h>

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
            Heap(vector<T> range): __heap() {
                heap_size = range.size();
                __heap = range;
                build_max_heap();
            };
            Heap(): __heap() {};
            ~Heap() {};

        private:
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

            template <typename Type>
            inline void swap(vector<Type>& range, int i, int j) {
                range[i] ^= range[j];
                range[j] ^= range[i];
                range[i] ^= range[j];
            }

        public:

            /**
             * the complexity of building a heap is O(n) although it looks like O(nlgn)
             * see this link for proof {@link http://www.cs.sfu.ca/CourseCentral/307/petra/2009/SLN_2.pdf}
             * @param array
             */
            void build_max_heap() {
                for (int i = heap_size - 1 / 2; i >= 0; i--) {
                    max_heapify(i);
                }
            };

            /**
             * general purposes
             * @param range
             * @return
             */
            template <typename Type>
            void build_max_heap(vector<Type> &range) {
                for (int i = (range.size() - 1) / 2; i >= 0; i--) {
                    max_heapify(range, range.size(), i);
                }
            };

            /**
             * the running time of 1 heapify operation on a subtree of size n is theta(1)
             * the running time of total heapify operation is given by the recurrence relation
             * T(n) <= T(2n/3) + theta(1)
             * the solution of this recurrence relation by master theorem is O(lgn).
             * @param i the subtree rooted at index i.
             */
            void max_heapify(int i) {
                // todo: accept range as parameters.
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
            };

            template <typename Type>
            void max_heapify(vector<Type> &range, int size, int i) {
                int greatest = i;
                int left_child = left(i);
                int right_child = right(i);
                if (left_child < size && range[i] < range[left_child]) {
                    greatest = left_child;
                }
                if (right_child < size && range[greatest] < range[right_child]) {
                    greatest = right_child;
                }
                if (greatest != i) {
                    swap(range, i, greatest);
                    max_heapify(range, size, greatest);
                }
                return;
            };


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
            };

            template <typename Type>
            void sort(vector<Type> range) {
                build_max_heap(range);
                for (int i = (int) (range.size() - 1); i > 0; i--) {
                    swap(range, 0, i);
                    max_heapify(range, --heap_size, 0);
                }
            }

            T extract_max() {
                if (heap_size < 1) {
                    // todo make your own exception.
                    throw underflow_error("heap underflow");
                }
                T max = __heap[0];
                __heap[0] = __heap[--heap_size];
                max_heapify(0);
                return max;
            };

            /**
             * removes and returns the element of the heap with largest key.
             * the runnig time of extraxt max is O(lgn)
             * @param range
             * @return
             */
            template <typename Type>
            Type extract_max(vector<Type> range) {
                if (range.size() < 1) {
                    // todo make your own exception.
                    throw underflow_error("heap underflow");
                }
                build_max_heap(range);
                Type max = range[0];
                range[0] = range[range.size() - 1];
                max_heapify(range, range.size() - 1, 0);
                return max;
            };


            template <typename Type>
            T getMax(vector<Type> range) {
                vector<Type> temp = range;
                build_max_heap(temp);
                return temp[0];
            }

            /**
             * the running time is O(lgn) since the max path from the updated node to the root is
             * the height of the tree = lgn.
             * @param i
             * @param new_value
             */
            void change_value(int i, T new_value) {
                if (__heap[i] > new_value) {
                    throw invalid_argument("new value is smaller than the current value"
                            " which will break the heap property");
                }
                __heap[i] = new_value;
                while (i > 0 && __heap[i] > __heap[parent(i)]) {
                    swap(i, parent(i));
                    i = parent(i);
                }
            }

            /**
             * inserts element x into the heap.
             * the running time on an n element heap is O(lgn)
             * @return
             */
            void insert(T value) {
                heap_size++;
                __heap.push_back(new T);
                change_value(heap_size - 1, value);
            }

            T getMax() {
                return __heap[0];
            }

            /**
             * print heap's element
             */
            void toString() {
                for (int i = 0; i < heap_size; ++i) {
                    printf("value = %d at node = %d\n", __heap[i], i);
                }
            };

        };
};

#endif