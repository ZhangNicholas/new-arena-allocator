#pragma once
#include <cstddef>

template <std::size_t N>
class ntarena
{
	static const std::size_t alignment = 16;
	static const std::size_t m_ntarena_size;
	char nbuf_[m_ntarena_size];
	alignas(alignment) char buf_[N];
	char* ptr_;

	std::size_t
		align_up(std::size_t n) { return n + (alignment - 1) & ~(alignment - 1); }

public:
	const std::size_t m_ntarena_size;
	ntarena(std::size_t ntarena_size) : ptr_(buf_), m_arena_size{ ntarena_size } {}
	ntarena(const ntarena&) = delete;
	ntarena& operator=(const ntarena&) = delete;

	char* allocate(std::size_t n)
	{
		n = align_up(n);
		if (buf_ + N - ptr_ >= n)
		{
			char* r = ptr_;
			ptr_ += n;
			std::cout << "Allocation in the current block" << std::endl;
			return r;
		}
		std::cout << "New block of " << n << "was allocated" << std::endl;
		return static_cast<char*>(::operator new(n));

	}
	void deallocate(char* p, std::size_t n)
	{
		n = align_up(n);
		if (buf_ <= p && p < buf_ + N) {
			if (p + n == ptr_) {
				ptr_ = p;
				std::cout << "Deallocation in the current block" << std::endl;
			}
		}
		else {
			std::cout << "Deallocation in the current block" << std::endl;
			::operator delete(p);
		}
	}
};