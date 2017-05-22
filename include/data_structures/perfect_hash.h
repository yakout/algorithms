//
// Created by Ahmed Yakout on 5/12/17.
//

#ifndef ALGORITHMS_PERFECT_HASH_H__
#define ALGORITHMS_PERFECT_HASH_H__


#include <data_structures/universal_hash.h>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

namespace algo {
	
	template <typename T>
	class perfect_hash {
	private:
		struct slot_lv2 {
			int collisions = 0;
			T value;
			int key;
		};

		struct slot_lv1 {
			slot_lv2** secondry_hash_table;
			int collisions = 0;
			T value; // todo 
			int key;
			universal_hash* uhf;
			std::vector<int> temp_keys;
			int max = 0;

			slot_lv1(): temp_keys() {

			}

			~slot_lv1() {
				if (collisions > 1) {
					delete [] secondry_hash_table;
				}
			}
		};

		universal_hash* uhf;
		slot_lv1** primary_hash_table;
		int constant; // constant * size
		/**
		 * maximum key value.
		 */
		int max = 0;
		/**
		 * size of hash table M.
		 */
		int table_size;
		/**
		 * number of keys stored in hash table N.
		 */
		int keys_size;
	public:
		perfect_hash() {

		}

		~perfect_hash() {
			delete [] primary_hash_table;
		}

		/**
		 * ability to access elements in hash table by the associated key with [] operator.
		 * @param  key
		 * @return value
		 */
		T operator[](int key) {
			slot_lv1* slot1 = primary_hash_table[uhf->hash(key)];
			if (slot1 == nullptr) {
				throw "key not found";
			}

			// search in level 1
			if (slot1->key == key) {
				return slot1->value;
			} else if (slot1->collisions > 1) {
				// search in level two
				if (slot1->secondry_hash_table == nullptr) {
					throw "key not found";	
				}
				slot_lv2* slot2 = slot1->secondry_hash_table[slot1->uhf->hash(key)];
				if (slot2->key == key) {
					return slot2->value;
				}
			}
			throw "key not found";
		}

		/**
		 * load static keys from file.
		 * 
		 * NOTE: the file only contains keys, there is no values so i also put the keys as values
		 * just to pass the TA test cases -__-
		 * the implementation will change a little to handle the insertion of (key, value) pair.
		 * 
		 * @param file_name full file path.
		 * @param _size size of keys in file.
		 */
		void load(std::string file_name, int _keys_size, bool n) {
			keys_size = _keys_size;
			// size = _size;
			std::ifstream file;
			file.open(file_name);
			if (!file.is_open()) {
				std::cout << "Fail to open file: " << file_name << std::endl;
				throw "failed to open file";
			}
	        
	        std::string number_str;
			int number;
			int keys[keys_size];
			int i = 0;
	        while (std::getline(file, number_str, ',')) {
	        	number = std::stoi(number_str);
	        	keys[i] = number;
	        	// std::cout << keys[i] << std::endl;
	        	i++;
	            if (number > max) {
	            	max = number;
	            }
	        }

	        // now we have the maximum element in the array 
	        std::cout << "max element: " << max << std::endl;
	        uhf = new universal_hash();
	        
	        std::set<int> temp = remove_duplicates(keys);

	        keys_size = temp.size();
			int unique_keys[keys_size];
			int j = 0;
			for (auto it = temp.begin(); it != temp.end(); ++it, ++j) {
				unique_keys[j] = *it;
			}
			std::cout << "new size after removeing duplicates: " << keys_size << std::endl;

			if (n) {
				// O(n) space
				constant = 2;
				table_size = keys_size;
				uhf->set_size(table_size);
	        	uhf->generate_hash(max);

				init_lv1(unique_keys);
		        init_lv2();

			} else {
				// O(n^2) space
				constant = 1;
				table_size = keys_size * keys_size;
				std::cout << "table_size: " << table_size << std::endl;
				std::cout << "keys_size: " << keys_size << std::endl;
				uhf->set_size(table_size);
	        	uhf->generate_hash(max);
				load(unique_keys);
			}

			if (check_collisions()) {
		       	std::cout << "not perfect hash!" << std::endl;
		    } else {
	        	std::cout << "no collisions" << std::endl;
	        	std::cout << "number of rebuild times needed: " << uhf->get_rebuild_times() << std::endl;
		    }
		}

	private:
		std::set<int> remove_duplicates(int keys[]) {
			std::set<int> temp(keys, keys + keys_size);
			return temp;
		}

		void init_lv1(int keys[]) {
			primary_hash_table = new slot_lv1 *[table_size] {nullptr};
			int key;
			// std::cout << size << std::endl;
	        for (int i = 0; i < keys_size; ++i) {
	        	// std::cout << i << std::endl;
	        	key = keys[i];
	        	// std::cout << uhf->hash(key) << std::endl;
	        	slot_lv1* current_slot = primary_hash_table[uhf->hash(key)];
	        	// std::cout << i << std::endl;
	        	if (current_slot != nullptr) {
	        		// std::cout << "?\n";
	        		current_slot->collisions++;
	        		// std::cout << "!\n";
	        		// store keys that cause collisions in temp vector for later use in level 2.
	        		current_slot->temp_keys.push_back(key);
	        		if (key > current_slot->max) {
	        			current_slot->max = key;
	        		}
	        	} else {
	        		// std::cout << "debug2" << std::endl;
	        		slot_lv1* slot = new slot_lv1();
	        		slot->key = key;
	        		slot->value = key;
	        		slot->collisions++;
	        		slot->max = key;
	        		primary_hash_table[uhf->hash(key)] = slot;
	        	}
	        }
	        // std::cout << size << std::endl;
	        if (!test_condition()) {
	        	uhf->regenerate_hash();
	        	if (uhf->get_rebuild_times() < 4) {
					init_lv1(keys);
	        	} else {
	        		throw "bad things is happening.";
	        	}
	        }
		}

		void init_lv2() {
			for (int i = 0; i < table_size; ++i) {
				if (primary_hash_table[i] != nullptr && primary_hash_table[i]->collisions != 1) {
					// std::cout << "i= " << i << " collisions: " << primary_hash_table[i]->collisions
					// 			<< " | in: " << primary_hash_table[i]->key << std::endl;
					
					// if (primary_hash_table[i]->collisions == 1) {
					// 	continue;
					// }
					
					// std::cout << " --------- " << std::endl;
					// std::cout << "i " << i << std::endl;
					// std::cout << "key " << primary_hash_table[i]->key << std::endl;
					// std::cout << "collisions " << primary_hash_table[i]->collisions << std::endl;

					init_lv2_slot(primary_hash_table[i]);
				} else {
					// no keys hashed to this slot, or there is no collision in this slot and 
					// no need to have a second hash table.
					continue;
				}
			}
		}

		void init_lv2_slot(slot_lv1* slot) {
			// std::cout << "+++++++++" << std::endl;
			int size_2 = (slot->collisions) * (slot->collisions);
			slot->secondry_hash_table = new slot_lv2 *[size_2] { nullptr };

			for (int i = 0; i < size_2; ++i)
			{
				if (slot->secondry_hash_table[i] != nullptr) {
					// slot->secondry_hash_table[i] = nullptr;
				}
			}

			for (int i = 0; i < size_2; ++i)
			{
				if (slot->secondry_hash_table[i] != nullptr) {
					std::cout << "555555555555555 khkhkhkhkhhkhkhkhkh خخخخخخخخ" << std::endl;
				}
			}

			slot->uhf = new universal_hash(size_2);
			// std::cout << "max " << slot->max << std::endl;
			// std::cout << "collisions " << slot->collisions << std::endl;
			// std::cout << "temp_keys " << slot->temp_keys.size() << std::endl;
			slot->uhf->generate_hash(slot->max);

			for (int i = 0; i < slot->temp_keys.size(); ++i) {
				int key  = slot->temp_keys[i];
				// slot_lv2* slot2 = new slot_lv2();
				// slot2->key = key;
				// slot2->value = key;
				// slot2->collisions++;
				// if (slot2->collisions > 1) {
				// 	std::cout << slot2->collisions << std::endl;
				// }
				// slot->secondry_hash_table[slot->uhf->hash(key)] = slot2;

				slot_lv2* current_slot = slot->secondry_hash_table[slot->uhf->hash(key)];
				// std::cout << "i " << i << std::endl;
				// std::cout << "key " << key << std::endl;
				// std::cout << "hash: "<< slot->uhf->hash(key) << std::endl;
	        	if (current_slot != nullptr) {
	    //     		std::cout << "i " << i << std::endl;
					// std::cout << "key " << key << std::endl;
					// std::cout << "hash: "<< slot->uhf->hash(key) << std::endl;

	        		current_slot->collisions++;
	        		if (current_slot->collisions > 1) {
						// std::cout << current_slot->collisions << std::endl;
					}
					// init_lv2_slot(slot);
	        	} else {
	        		// std::cout << "debug2" << std::endl;
	        		slot_lv2* slot2 = new slot_lv2();
	        		slot->key = key;
	        		slot->value = key;
	        		// slot->collisions++;
	        		slot->secondry_hash_table[slot->uhf->hash(key)] = slot2;
	        	}
			}
			slot->temp_keys.clear();
			slot->collisions = 1;
		}


		/**
		 * ckeck if collision happens
		 * @return returns true collisions occured in any slot.
		 */
		bool check_collisions() {
			for (int i = 0; i < table_size; ++i) {
				if (primary_hash_table[i] != nullptr) {
					if (primary_hash_table[i]->collisions > 1) {
						// std::cout << primary_hash_table[i]->collisions << std::endl;
						return true;
					}

					if (primary_hash_table[i]->uhf != nullptr && primary_hash_table[i]->secondry_hash_table != nullptr) {
						for (int j = 0; j < primary_hash_table[i]->uhf->get_size(); ++j) {
							if (primary_hash_table[i]->secondry_hash_table[j] != nullptr 
									&& primary_hash_table[i]->secondry_hash_table[j]->collisions > 1) {
								return true;
							}
						}
					}
				}
			}
			return false;
		}

		/**
		 * test the condition that sum of collisions square < constant * size.
		 * @return true if the condition is true.
		 */
		bool test_condition() {
			int sum_of_squares = 0;
			for (int i = 0; i < table_size; ++i) {
				if (primary_hash_table[i] != nullptr) {
					sum_of_squares += primary_hash_table[i]->collisions * primary_hash_table[i]->collisions;
				} 
			}
			std::cout << "sum_of_squares = " << sum_of_squares << std::endl; 
			if (sum_of_squares < constant * keys_size) {
				return true;
			}
			return false;
		}

		/**
		 * temp implementation for O(n^2) hash table space 
		 * @param keys  
		 * @param _size 
		 */
		void load(int keys[]) {
			primary_hash_table = new slot_lv1 *[table_size] {nullptr};
			for (int i = 0; i < keys_size; ++i) {
				int key = keys[i];
				if (primary_hash_table[uhf->hash(key)] != nullptr) {
					primary_hash_table[uhf->hash(key)]->collisions++;
				} else {
					slot_lv1* slot = new slot_lv1();
					slot->key = key;
					slot->value = key;
					slot->collisions++;
					primary_hash_table[uhf->hash(key)] = slot;
				}
			}

			if (check_collisions()) {
	        	uhf->regenerate_hash();
	        	if (uhf->get_rebuild_times() < 4) {
					load(keys);
	        	} else {
	        		throw "bad things is happening.";
	        	}
	        }
		}
	};

}


#endif // ALGORITHMS_PERFECT_HASH_H__