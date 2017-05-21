//
// Created by Ahmed Yakout on 5/20/17.
//

#ifndef ALGORITHMS_UNIVERSAL_HASH_H__
#define ALGORITHMS_UNIVERSAL_HASH_H__


#include <cmath>
#include <random>


namespace algo {

	/**
	 * The idea behind universal hashing is to avoid choosing the keys to be hashed by some fixed
	 * hash function which can yeild an average retrival time of theta(n), instead we can choose
	 * the hash function randomly from carefully designed class of hash functions.
	 */
	class universal_hash {
	private:
		/**
		 * random generated.
		 */
		unsigned long long a;
		/**
		 * random generated.
		 */
		unsigned long long b;
		/**
		 * generated prime.
		 */
		unsigned long long prime;
		/**
		 * size of hash table M.
		 */
		unsigned long long size;
		/**
		 * maximum element in the static data.
		 */
		int max_element;
		/**
		 * number of times required to rebuild the hash table.
		 */
		int rebuild_counter = 0;

	public:

		universal_hash(int _size): size(_size) {
		}

		universal_hash() {
		}

		/**
		 * generate the hash function paramters.
		 */
		void generate_hash(int _max_element) {
			int max_element = _max_element;
			int max = std::max(max_element, (int)size);
			prime = generate_prime(max);
			a = generate_random(1, prime - 1);
			b = generate_random(1, prime - 1);
		}

		/**
		 * re-generate the hash function paramters.
		 */
		void regenerate_hash() {
			rebuild_counter++;
			generate_hash(max_element);
		}

		/**
		 * generate universal hashing using the matrix method.
		 * https://www.cs.cmu.edu/~avrim/451f11/lectures/lect1004.pdf
		 */
		void generate_matrix() {
			// todo implement the matrix method
		}

	private:
		int generate_random(int min, int max) {
			std::mt19937 rng;
		    rng.seed(std::random_device()());
		    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max); // distribution in range [min, max]
		    return dist(rng);
		}

		/**
		 * given the maximum element in a static data this method will generate the next prime larger
		 * than the maximum element.
		 * @param  max_element 
		 * @return generated prime
		 */
		int generate_prime(int max_element) {
			int i = max_element;
			while (!is_prime(++i));
			return i;
		}

		/**
		 * methods to test if number is prime or not.
		 * @param  p 
		 * @return
		 */
		bool is_prime(int p) {
			if (p == 2) {
				return true;
			} else if (p == 1) {
				return false;
			}
			for (int i = 2; i < std::sqrt(p) + 1; ++i) {
				if (p % i == 0) {
					return false;
				}
			}
			return true;
		}

	public:
		/**
		 * return the size of static data used in this universal hash function.
		 * @return 
		 */
		int get_size() {
			return size;
		}

		int get_rebuild_times() {
			return rebuild_counter;
		}

		void set_size(int new_size) {
			size = new_size;
		}

		/**
		 * hash some key with the hash function generated.
		 * @param  key
		 * @return     
		 */
		int hash(int key) {
			// std::cout << "prime:  " << prime << std::endl;
			// std::cout << "size:  " << size << std::endl;
			// std::cout << a << std::endl;
			// std::cout << key << std::endl;
    		int hash = (((a * key) + b) % prime) % size;
    		// int hash = ((( (key * a) % prime) * b) % prime) % size;
    		// std::cout << hash  % size << std::endl;
    		return hash;
		}

	};
}


#endif // ALGORITHMS_UNIVERSAL_HASH_H__