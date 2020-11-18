#pragma once
#include <cstddef>

#include "arena.h"

template <class T, std::size_t N>
class arena_allocator
{
	arena<N>& a_;
public:
	typedef T value_type;

public:
	template <class U> struct rebind { typedef arena_allocator<U, N> other; };

	explicit arena_allocator(arena<N>& a) : a_(a) {}
	template <class U>
	arena_allocator(const arena_allocator<U, N>& a)
		: a_(a.a_) {}
	arena_allocator(const arena_allocator&) = default;
	arena_allocator& operator=(const arena_allocator&) = delete;

	T* allocate(std::size_t n)
	{
		return reinterpret_cast<T*>(a_.allocate(n * sizeof(T)));
	}
	void deallocate(T* p, std::size_t n)
	{
		a_.deallocate(reinterpret_cast<char*>(p), n * sizeof(T));
	}

	template <class T1, std::size_t N1, class U, std::size_t M>
	friend
		bool
		operator==(const arena_allocator<T1, N1>& x, const arena_allocator<U, M>& y);

	template <class U, std::size_t M> friend class arena_allocator;
};

template <class T, std::size_t N, class U, std::size_t M>
bool
operator==(const arena_allocator<T, N>& x, const arena_allocator<U, M>& y)
{
	return N == M && &x.a_ == &y.a_;
}

template <class T, std::size_t N, class U, std::size_t M>
bool
operator!=(const arena_allocator<T, N>& x, const arena_allocator<U, M>& y)
{
	return !(x == y);
}