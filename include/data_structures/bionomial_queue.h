//
// Created by Ahmed Yakout on 3/30/17.
//

#ifndef ALGORITHMS_BIONOMIAL_QUEUE_H__
#define ALGORITHMS_BIONOMIAL_QUEUE_H__

#include <iostream>
#include <fstream>

// IN PSEUDO CODE

namespace algo {

	class bionomial_queue {
	public:
		struct Node {
			int key; 
			T value;
			int degree; // rank/order/height/max_depth of the tree
			Node *sibiling, *parent, *child;
		};
		
		bionomial_queue();
		~bionomial_queue();

		Node* find_minimum(H);
		Node link(x, y);
		Node merge(H1, H2);
		Node union_(H1, H2);
		void insert(H, x, key, data);
		Node* extract_min(H);
		Node* decrese_key(H, key, new_key);
		Node* delete_node(H, key);
	};


	// this subroutine checks all roots which is at most floor(lgn) + 1
	// so the running time is O(lgn) in worst case (upper bound)
	// note that we can make is theta(1) by keeping a pointer to minimum and update is regularly
	find_minimum(H) {
		Node y = nil;
		Node x = H.head;
		int min = infinityl
		while (x != nil) {
			if (x.key < min) {
				min = x.key;
			}
			y = x;
			x = x.sibiling;
		}
		return y;
	}



	// link two bionomial tree (make the x the left most child of y)
	Node link(x, y) {
		x.parent = y
		// ...
	}

	// merge two bionomial heaps (it's same as merge subroutine in merge sort)
	// H1, and H2 already sorted by degree
	// O(lgn)
	Node merge(H1, H2);


	// O(lgn)
	Node union_(H1, H2);



	// O(lgn)
	insert(H, x, key, data) {
		H_new = make_bionomial_heap();
		x.p = nullptr;
		x.sibiling = nullptr;
		x.child = nullptr;
		x.degree = 0;
		x.value = data;
		x.key = key;
		H_new.head = x;
		union_(H_new, H);
	}


	// O(lgn)
	Node* extract_min(H) {
		// find min of H and remove it
		x = H.remove(minimum(H)); // assuming remove will return the delete node
		// reverse the order of linked list of x's childern
		head = x.reverse(); // assuming reverse will return the new head
		H_new = make_bionomial_heap();
		H_new.head = head;
		union_(H_new, H);
		return x;
	}


	// new_key must be lower the key
	// O(lgn)
	Node* decrese_key(H, key, new_key) {
		// update key

		// in while loop:
		// compare with parent if lower than parent
		// exchange
		// confinue loop until parent is nill or parent is lower than the node
	}


	Node* delete_node(H, key) {
		decrese_key(H, key, -inf);
		extract_min(H);
	}

}

#endif






