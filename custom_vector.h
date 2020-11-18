#include <iostream>
#include <string>
#include <vector>

template <typename T>
struct It {
	std::vector<T>& vec_;
	int pointer_;

	It(std::vector<T>& vec) : vec_{ vec }, pointer_{ 0 } {}

	It(std::vector<T>& vec, int size) : vec_{ vec }, pointer_{ size } {}

	bool operator!=(const It<T>& other) const {
		return !(*this == other);
	}

	bool operator==(const It<T>& other) const {
		return pointer_ == other.pointer_;
	}

	It& operator++() {
		++pointer_;
		return *this;
	}

	T& operator*() const {
		return vec_.at(pointer_);
	}
};

template <class T>
struct CustomVector {
	std::vector<T> vec_;

	void push_back(T item) {
		vec_.push_back(item);
	};

	It<T> begin() {
		return It<T>(vec_);
	}

	It<T> end() {
		return It<T>(vec_, vec_.size());
	}
};