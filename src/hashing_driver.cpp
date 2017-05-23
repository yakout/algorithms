#include <iostream>


#include <data_structures/perfect_hash.h>


int main(int argc, char const *argv[]) {
	algo::perfect_hash<int> hash_table;

	try {
		// test 1 
		// hash_table.load("./testCases_lab4/keys1001000.txt", 1000, true);
		// test 2
		// hash_table.load("./testCases_lab4/keys10001000.txt", 1000, true);
		// test 3
		// hash_table.load("./testCases_lab4/keys100001000000.txt", 1000000, true);
		// test 4
		hash_table.load("./testCases_lab4/keys10000001000000.txt", 1000000, true);
		// random test
		// hash_table.load("./testCases_lab4/mytest.txt", 2, false);
		// 
		// std::cout << "value for key = 686: " << hash_table[999] << std::endl;
	} catch (const char* e) {
		std::cout << e << std::endl;
	}
	
	return 0;
}
