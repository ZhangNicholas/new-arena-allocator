#pragma once
#include <iostream>
#include <string>
#include <vector>

template <
	class T,
	class A = std::allocator<T>
>

struct aIt {
	std::vector<T, A>& vec_;
	int pointer_;

	aIt(std::vector<T, A>& vec) : vec_{ vec }, pointer_{ 0 } {}

	aIt(std::vector<T, A>& vec, int size) : vec_{ vec }, pointer_{ size } {}

	bool operator!=(const aIt<T, A>& other) const {
		return !(*this == other);
	}

	bool operator==(const aIt<T, A>& other) const {
		return pointer_ == other.pointer_;
	}

	aIt& operator++() {
		++pointer_;
		return *this;
	}

	T& operator*() const {
		return vec_.at(pointer_);
	}
};

template<
	class T,
	class Allocator = std::allocator<T>
>
struct aCustomVector {
	std::vector<T, Allocator> vec_;

	aCustomVector() {
		std::vector<T, std::allocator<T>> vec_;
	};

	aCustomVector(Allocator al) : vec_{ al } {
	};

	void push_back(T item) {
		vec_.push_back(item);
	};

	aIt<T, Allocator> begin() {
		return aIt<T, Allocator>(vec_);
	}

	aIt<T, Allocator> end() {
		return aIt<T, Allocator>(vec_, vec_.size());
	}
};