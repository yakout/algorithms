//
// Created by Ahmed Yakout on 5/13/17.
//

#include <iostream>
#include "disjoint_set.h"


/**
 * demo
 */
int main(int argc, char *argv[]) {
	algo::disjoint_set<int> set1(1);
	algo::disjoint_set<int> set2(2);
	algo::disjoint_set<int> set3(3);
	algo::disjoint_set<int> set4(4);
	algo::disjoint_set<int> set5(5);
	algo::disjoint_set<int> set6(6);
	algo::disjoint_set<int> set7(7);
	algo::disjoint_set<int> set8(8);
	algo::disjoint_set<int> set9(9);
	algo::disjoint_set<int> set10(10);
	algo::disjoint_set<int> set11(11);
	algo::disjoint_set<int> set12(12);
	algo::disjoint_set<int> set13(13);
	algo::disjoint_set<int> set14(14);
	algo::disjoint_set<int> set15(15);
	algo::disjoint_set<int> set16(16);

	set2.union_set(&set1);
	set2.union_set(&set2);
	set2.union_set(&set3);
	set2.union_set(&set4);
	set2.union_set(&set5);
	set2.union_set(&set6);
	set2.union_set(&set7);
	set2.union_set(&set8);


	set9.union_set(&set9);
	set9.union_set(&set10);
	set9.union_set(&set11);
	set9.union_set(&set12);
	set9.union_set(&set13);
	set9.union_set(&set14);
	set9.union_set(&set15);
	set9.union_set(&set16);

	std::cout << set8.find_set()->get_data() << std::endl;
	std::cout << set15.find_set()->get_data() << std::endl;

}