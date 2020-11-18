#pragma once
#include <cstddef>

#include "arena.h"

template <class T, std::size_t N>
class ntarena_allocator
{
	ntarena& a_;
public:
	typedef T value_type;

public:
	template <class U> struct rebind { typedef ntarena_allocator<U, N> other; };

	explicit ntarena_allocator(ntarena& a) : a_(a) {}
	template <class U>
	ntarena_allocator(const ntarena_allocator<U, N>& a)
		: a_(a.a_) {}
	ntarena_allocator(const ntarena_allocator&) = default;
	ntarena_allocator& operator=(const ntarena_allocator&) = delete;

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
		operator==(const ntarena_allocator<T1, N1>& x, const ntarena_allocator<U, M>& y);

	template <class U, std::size_t M> friend class ntarena_allocator;
};

template <class T, std::size_t N, class U, std::size_t M>
bool
operator==(const ntarena_allocator<T, N>& x, const ntarena_allocator<U, M>& y)
{
	return N == M && &x.a_ == &y.a_;
}

template <class T, std::size_t N, class U, std::size_t M>
bool
operator!=(const ntarena_allocator<T, N>& x, const ntarena_allocator<U, M>& y)
{
	return !(x == y);
}