//
// Created by Ahmed Yakout on 5/13/17.
//


/**
 *
 * A TEMPLATED DISJOINT-SET DATA STRUCTURE.
 * 
 * disjoint set has two main operations: find() and unit()
 * there is many implementation for disjoing set, using linked-list or rooted trees.
 * the running time for rooted trees is theoritically superlinear.
 * but for all our real life applications it's linear.
 *
 *
 *
 * 
 * This class it based on rooted tree implementation.
 * 
 */



#ifndef ALGORITHMS_DISJOINT_SET_H__
#define ALGORITHMS_DISJOINT_SET_H__

namespace algo {
	/**
	 * 
	 * disjoint set is data structure that maintains a collection of disjoint dynamic sets
	 * and each set is idintified by a representatave which is a member of the set, and we don't
	 * care acutally which member we choose as representative, in some applications we may care!
	 * 
	 */
	template <typename T>
	class disjoint_set {
	private:
		T data;
		unsigned rank;
		disjoint_set* parent;
	public:
		/**
		 * creates a new set whose only member (thus representative) is the given element x.
		 */
		disjoint_set(T value): data(value), rank(0), parent(this) {
		}
		~disjoint_set() {
		}

		/**
		 * returns a pointer to the representative of the (unique) set that contains element x;
		 */
		disjoint_set<T>* find_set();
		/**
		 * unites the dynamic set that contain x and y into a new set that is the union of these two sets.
		 */
		void union_set(disjoint_set<T>*);
		/**
		 * return data in the node..
		 * @return T.
		 */
		T get_data();

	private:
		/**
		 * unites the dynamic set that contain x and y into a new set that is the union of these two sets.
		 */
		void link_set(disjoint_set<T>*);
	};

	

	/**  F U N C T I O N S   D E F I N T I O N S   **/
	
	template<typename T>
	T disjoint_set<T>::get_data() {
		return data;
	}

	template<typename T>
	disjoint_set<T>* disjoint_set<T>::find_set() {
		if (this != this->parent) {
			this->parent = parent->find_set();
		}
		return this->parent;
	}

	template<typename T>
	void disjoint_set<T>::link_set(disjoint_set<T>* y) {
		// std::cout << y->get_data() << std::endl; 
		if (this->rank > y->rank) {
			y->parent = this->parent;
		} else {
			this->parent = y;
			if (this->rank == y->rank) {
				y->rank++;
			}
		}
	}

	template<typename T>
	void disjoint_set<T>::union_set(disjoint_set<T>* y) {
		find_set()->link_set(y->find_set());
	}

}

#endif
