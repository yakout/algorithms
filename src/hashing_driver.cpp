#include <iostream>


#include <data_structures/perfect_hash.h>



int main(int argc, char const *argv[]) {
	algo::perfect_hash<int> hash_table;
	// algo::universal_hash uhf(2);
	// uhf.generate_random(0, 10);

	try {
		hash_table.load("./testCases_lab4/keys10000001000000.txt", 1000000, true);
	} catch (const char* e) {
		std::cout << e << std::endl;
	}
	// std::cout << "value for key = 686: " << hash_table[686] << std::endl;
	// std::cout << "value for key = 542: " << hash_table[542] << std::endl;
	// std::cout << "value for key = 571: " << hash_table[571] << std::endl;
	// std::cout << "value for key = 511: " << hash_table[511] << std::endl;
	// std::cout << "value for key = 813: " << hash_table[813] << std::endl;
	return 0;
}