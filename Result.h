#pragma once

#ifndef RESULT_H
#define RESULT_H

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

constexpr int NUMBERS_COUNT = 7;

class Result {
	std::vector<int> numbers;
	int additional;
public:
	Result(int* res);
	ostream& operator<<(ostream& os);
	bool operator==(const Result& other) const;
	bool operator!=(const Result& other) const;
	bool validateResult();
};

#endif // !RESULT_H
