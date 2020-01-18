#pragma once

#ifndef RESULT_H
#define RESULT_H

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Result{
	std::vector<int> numbers;
	int plus;
public:
	Result(int a, int b, int c, int d, int e, int f, int plus): plus(plus) {
		numbers.push_back(a);
		numbers.push_back(b);
		numbers.push_back(c);
		numbers.push_back(d);
		numbers.push_back(e);
		numbers.push_back(f);
		sort(numbers.begin(), numbers.end());
	}
	
	void print() {
		for (int n : numbers)
			std::cout << n << ", ";
		cout << plus;
	}

	bool operator==(const Result& other) const {
		return (this->numbers == other.numbers) && this->plus==other.plus;
	}

	bool operator!=(const Result& other) const {
		return !(*this==other);
	}
};

#endif // !RESULT_H
