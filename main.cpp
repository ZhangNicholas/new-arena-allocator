#include <vector>
#include <iostream>
#include <map>

#include "stack_allocator.h"
#include "custom_vector.h"
#include "a_custom_vector.h"

template <class T, std::size_t N> using A = stack_allocator<T, N>;
template <class T, std::size_t N> using Vector = std::vector<T, stack_allocator<T, N>>;
template <class T, std::size_t N> using CVector = CustomVector<T>;
template <class T, std::size_t N> using ACVector = aCustomVector<T, stack_allocator<T, N>>;
template <class Key, class T, std::size_t N> using Map =
	std::map <
		Key,
		T,
		std::less<Key>,
		stack_allocator<std::pair<const Key, T>, N>
>;

unsigned int factorial(unsigned int n) {
	if (n == 0) return 1;
	return n * factorial(n - 1);
}

int main() {
	constexpr int container_size = 10;
	constexpr std::size_t arena_size = 1024; // bytes
	arena<arena_size> a;


	CustomVector<int> vec;
	std::map<int, int> m;
	Map<int, int, arena_size> m_custom_allocator {
		A<std::map<int, int>, arena_size>(a)
	};

	Vector<int, arena_size> v_custom_allocator {
		A<std::vector<int>, arena_size>(a)
	};

	std::vector<int, stack_allocator<int, arena_size>> v_custom_allocator_1 {
		stack_allocator<int, arena_size>(a)
	};

	// aCustomVector<int> vec;
	aCustomVector<int, stack_allocator<int, arena_size>> ca_vec {
		stack_allocator<int, arena_size>(a)
	};

	for (int i = 0; i < container_size; ++i) {
		m_custom_allocator[i] = factorial(i);
		std::cout << sizeof(m_custom_allocator[i]) << std::endl;
	}

	for (const auto& it : m_custom_allocator) {
		std::cout << it.first << ' ' << it.second << std::endl;
	}



	for (int i = 0; i < container_size; ++i) {
		v_custom_allocator_1.push_back(factorial(i));
		std::cout << sizeof(v_custom_allocator_1[i]) << std::endl;
	}

	for (const auto& it : v_custom_allocator_1) {
		std::cout << &it << std::endl;
	}
	
	std::cout << "custom vector with regular allocator" << std::endl;
	for (int i = 0; i < container_size; ++i) {
		vec.push_back(i);
	}

	for (It<int> it = vec.begin(); it != vec.end(); ++it) {
		std::cout << *it << std::endl;
	}
	
	std::cout << "custom vector with custom allocator" << std::endl;
	for (int i = 0; i < container_size; ++i) {
		ca_vec.push_back(i);
	}

	for (aIt<int, stack_allocator<int, arena_size>> it = ca_vec.begin(); it != ca_vec.end(); ++it) {
		std::cout << *it << std::endl;
	}
}