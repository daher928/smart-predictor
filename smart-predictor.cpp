// smart-predictor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "csv.h"
#include <fstream>
#include <vector>
#include "Result.h"

#define ARCHIVE_FILENAME "Lotto.csv"


bool checkIfExists(std::vector<Result>* arr, Result* res) {
    if (arr == NULL || res == NULL) {
        return false;
    }

    if (std::find((*arr).begin(), (*arr).end(), *res) != (*arr).end()) {
        cout << "EXISTS: ";
        res->print();
        return true;
    }
    
    return false;
}

void readArchive(std::vector<Result>* arr) {
    cout << "Reading archive ..." << endl;
    io::CSVReader<7> in("Lotto.csv");
    in.read_header(io::ignore_no_column, "1", "2", "3", "4", "5", "6", "+");
    int a, b, c, d, e, f, plus;
    while (in.read_row(a, b, c, d, e, f, plus)) {
        Result* res = new Result(a, b, c, d, e, f, plus);
        if (!res->validateResult() || checkIfExists(arr, res)) {
            continue;
        }
        (*arr).push_back(*res);
    }
    std::cout << "Done.\n" << "History size=" << arr->size() << endl;
}
int main() {
    std::vector<Result> resultsHistory;

    readArchive(&resultsHistory);
    
    while (true) {
        cout << "Enter your guess: ";
        int arr[7] = {-1,-1,-1,-1,-1,-1,-1};
        for (int i = 0; i < 7; ++i)
        {
            int a;
            cin >> a;
            arr[i] = a;
        }

        Result *res = new Result(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6]);
        if (!res->validateResult())
            continue;
        cout << (checkIfExists(&resultsHistory, res)? "EXISTS" : "DOESN'T EXIST") << endl;
    }
    
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
