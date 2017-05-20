//
// Created by Ahmed Yakout on 5/20/17.
//

#ifndef ALGORITHMS_UNIVERSAL_HASH_H__
#define ALGORITHMS_UNIVERSAL_HASH_H__


#include <cmath>
#include <random>


namespace algo {

	class universal_hash {
	private:
		int a;
		int b;
		int prime;
		int size;

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
		universal_hash(int _size): size(_size) {

		}

		void set_size(int new_size) {
			size = new_size;
		}

		void generate_hash(int max_element) {
			prime = generate_prime(max_element);
			a = generate_random(1, prime - 1);
			b = generate_random(0, prime - 1);
		}

		int generate_random(int min, int max) {
			std::mt19937 rng;
		    rng.seed(std::random_device()());
		    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max); // distribution in range [min, max]

		    // std::cout << dist(rng) << std::endl;
		    // std::cout << dist(rng) << std::endl;
		    // std::cout << dist(rng) << std::endl;
		    // std::cout << dist(rng) << std::endl;
		    // std::cout << dist(rng) << std::endl;
		    // std::cout << dist(rng) << std::endl;
		    // std::cout << dist(rng) << std::endl;
		    // std::cout << dist(rng) << std::endl;
		    return dist(rng);
		}

		int generate_prime(int max_element) {
			int i = max_element;
			while (!is_prime(++i));
			return i;
		}

		int hash(int key) {
    		return (((a * key + b) % prime) % size);
		}

	};
}


#endif // ALGORITHMS_UNIVERSAL_HASH_H__