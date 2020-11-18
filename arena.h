#pragma once
#include <cstddef>

template <std::size_t N>
class arena
{
	static const std::size_t alignment = 16;
	alignas(alignment) char buf_[N];
	char* ptr_;

	std::size_t align_up(std::size_t n) {
		return n + (alignment - 1) & ~(alignment - 1);
	}

public:
	arena() : ptr_{ buf_ } {
		std::cout << "Arena in size of " << N << " bytes initiated at address: "<< &buf_<< std::endl;
	}
	arena(const arena&) = delete;
	arena& operator=(const arena&) = delete;
	
	char* allocate(std::size_t n)
	{
		n = align_up(n);
		if (buf_ + N - ptr_ >= n)
		{
			char* r = ptr_;
			ptr_ += n;
			std::cout << "Allocating in the current block " << n << " bytes"<< std::endl;
			return r;
		}
		std::cout << "New block of " << n << " was allocated" << std::endl;
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