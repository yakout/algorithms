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
			unsigned collisions = 0; 
			T value;
			unsigned key;
		};

		struct slot_lv1 {
			slot_lv2** secondry_hash_table;
			unsigned collisions = 0;
			T value; // todo 
			unsigned key;
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
		int thresold = 2; // 2 * size
		int max = 0;
		int size;
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
		T& operator[](int key) {
			slot_lv1* slot1 = primary_hash_table[uhf->hash(key)];
			if (slot1->collisions > 1) {
				slot_lv2* slot2 = slot1->secondry_hash_table[slot1->uhf->hash(key)];
				if (slot2->key == key) {
					return slot2->value;
				}
			} else if (slot1->key == key) {
				return slot1->value;
			}

			throw "key not found";
		}

		/**
		 * load static keys from file.
		 * @param file_name full file path.
		 * @param _size size of keys in file.
		 */
		void load(std::string file_name, int _size) {
			size = _size;
			std::ifstream file;
			file.open(file_name);
			if (!file.is_open()) {
				std::cout << "Fail to open file: " << file_name << std::endl;
				throw "failed to open file";
			}

			std::cout <<"Opened OK" << std::endl;
	        std::string number_str;

			int number;
			int keys[size + 1];
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
	        std::cout << max << std::endl;
	        uhf = new universal_hash(size);
	        uhf->generate_hash(max);


	        // for (int i = 0; i < size - 1; i++)
	        // {
	        // 	std::cout << keys[i] << std::endl;
	        // }
	        
	        std::set<int> temp = remove_duplicates(keys);
	        size = temp.size();
			int unique_keys[size];
			int j = 0;
			for (auto it = temp.begin(); it != temp.end(); ++it, ++j) {
				unique_keys[j] = *it;
			}
			std::cout << "new size after removeing duplicates: " << size << std::endl;


			// load(unique_keys, size); uncomment this for O(n^2) space
	        init_lv1(unique_keys);
	        init_lv2();
		}

		std::set<int> remove_duplicates(int keys[]) {
			std::set<int> temp(keys, keys+size);
			return temp;
		}

		void init_lv1(int keys[]) {
			primary_hash_table = new slot_lv1 *[size];
			int key;
	        for (int i = 0; i < size; ++i) {
	        	key = keys[i];
	        	slot_lv1* current_slot = primary_hash_table[uhf->hash(key)];
	        	if (current_slot != nullptr) {
	        		current_slot->collisions++;
	        		// store keys that cause collisions in temp vector for later use in level 2.
	        		current_slot->temp_keys.push_back(key);
	        		if (key > current_slot->max) {
	        			current_slot->max = key;
	        		}
	        	} else {
	        		slot_lv1* slot = new slot_lv1();
	        		slot->key = key;
	        		slot->value = key;
	        		slot->collisions++;
	        		slot->max = key;
	        		primary_hash_table[uhf->hash(key)] = slot;
	        	}
	        }
		}

		void init_lv2() {
			int sum_of_squares = 0;
			for (int i = 0; i < size; ++i) {
				if (primary_hash_table[i] != nullptr) {
					sum_of_squares += primary_hash_table[i]->collisions * primary_hash_table[i]->collisions;
					// std::cout << "i= " << i << " collisions: " << primary_hash_table[i]->collisions
					// 			<< " | in: " << primary_hash_table[i]->key << std::endl;
					init_lv2_slot(primary_hash_table[i]);
				} else {
					// no keys hashed to this slot.
				}
			}
			std::cout << "sum_of_squares = " << sum_of_squares << std::endl;
		}

		void init_lv2_slot(slot_lv1* slot) {
			slot->secondry_hash_table = new slot_lv2 *[slot->collisions];
			slot->uhf = new universal_hash(slot->collisions);
			slot->uhf->generate_hash(slot->max);
			for (int i = 0; i < slot->collisions - 1; ++i) {
				slot_lv2* slot2 = new slot_lv2();
				// std::cout << slot->temp_keys[i] << std::endl;
				slot2->key = slot->temp_keys[i];
				slot2->value = slot->temp_keys[i];
				slot->secondry_hash_table[slot->uhf->hash(slot2->key)] = slot2;
			}
			slot->temp_keys.clear();
		}



		/**
		 * temp implementation for O(n^2) hash table space 
		 * @param keys  
		 * @param _size 
		 */
		void load(int keys[], int _size) {
			size = _size*_size;
			uhf = new universal_hash(size);
			uhf->generate_hash(max);
			primary_hash_table = new slot_lv1 *[size];
			for (int i = 0; i < _size; ++i) {
				int key = keys[i];
				if (primary_hash_table[uhf->hash(key)] != nullptr) {
					primary_hash_table[uhf->hash(key)]->collisions++;
				} else {
					slot_lv1* slot = new slot_lv1();
					slot->key = key;
					slot->collisions++;
					primary_hash_table[uhf->hash(key)] = slot;
				}
			}

			for (int i = 0; i < size; ++i) {
				if (primary_hash_table[i] != nullptr) {
					std::cout << "i= " << i << " collisions: " << primary_hash_table[i]->collisions
								<< " | in: " << primary_hash_table[i]->key << std::endl;
				}
			}
		}
		
	};

}


#endif // ALGORITHMS_PERFECT_HASH_H__