#pragma once
#include <cstddef>

#include "arena.h"

template <class T, std::size_t N>
class stack_allocator
{
	arena<N>& a_;

public:
	typedef T value_type;

public:
	template <class U> struct rebind { typedef stack_allocator<U, N> other; };

	explicit stack_allocator(arena<N>& a) : a_{ a } {
	}

	template <class U>
	stack_allocator(const stack_allocator<U, N>& a)
		: a_(a.a_) {
		//std::cout << "constructor value x_ = " << x_ << std::endl;
	}
	stack_allocator(const stack_allocator&) = default;
	stack_allocator& operator=(const stack_allocator&) = delete;

	T* allocate(std::size_t n) {
		//std::cout << "x_ = " << x_ << std::endl;
		return reinterpret_cast<T*>(a_.allocate(n * sizeof(T)));
	}

	void deallocate(T* p, std::size_t n)
	{
		a_.deallocate(reinterpret_cast<char*>(p), n * sizeof(T));
	}

	template <class T1, std::size_t N1, class U, std::size_t M>
	friend
		bool
		operator==(const stack_allocator<T1, N1>& x, const stack_allocator<U, M>& y);

	template <class U, std::size_t M> friend class stack_allocator;
};

template <class T, std::size_t N, class U, std::size_t M>
bool
operator==(const stack_allocator<T, N>& x, const stack_allocator<U, M>& y)
{
	return N == M && &x.a_ == &y.a_;
}

template <class T, std::size_t N, class U, std::size_t M>
bool
operator!=(const stack_allocator<T, N>& x, const stack_allocator<U, M>& y)
{
	return !(x == y);
}