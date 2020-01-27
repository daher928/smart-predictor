#include "Result.h"

Result::Result(int* res) {
	for (int i = 0; i < NUMBERS_COUNT - 1; i++) {
		numbers.push_back(res[i]);
	}
	additional = res[NUMBERS_COUNT - 1];
	sort(numbers.begin(), numbers.end());
}

bool Result::validateResult() {
	bool isValid = true;
	if (this == NULL || this->additional < 1 || this->additional > 6) {
		isValid = false;;
	}
	else {
		for (int number : this->numbers) {
			if (number < 1 || number > 37) {
				isValid = false;;
			}
		}
	}
	if (isValid == false) {
		cout << "INVALID RESULT: " << this << endl;
	}
	return isValid;
}

ostream& Result::operator<<(ostream& os)
{
	for (int i = 0; i < NUMBERS_COUNT - 1; i++)
		os << this->numbers[i] << ',';
	os << this->additional;
	return os;
}

bool Result::operator==(const Result& other) const {
	return (this->numbers == other.numbers) && this->additional == other.additional;
}

bool Result::operator!=(const Result& other) const {
	return !(*this == other);
}