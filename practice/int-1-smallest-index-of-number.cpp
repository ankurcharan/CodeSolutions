// int-1-smallest-index-of-number

// https://leetcode.com/discuss/interview-question/2006734/google-onsite-l4-rejected

////////////////////////////////
// Second Question
////////////////////////////////



/*
Implement a NumberContainer class.


class NumberContainer {

  val indexToNumber = mutableMapOf<Int, Int>()
  val numberToIndexes = mutableMapOf<Int, PriorityQueue<Int>>()

  // n == count of indexes
  // m == count of numbers
  // O(n) + O(logn)
  fun insertOrReplace(index: Int, number: Int) {
    if (index in indexToNumber) {
      val oldNumber = indexToNumber.getValue(index)
      numberToIndexes.getValue(oldNumber).remove(index)
    }
    indexToNumber[index] = number
    numberToIndexes.getOrPut(number) { PriorityQueue() } += index
  }

  // O(1)
  fun findSmallestIndex(number: Int): Int {
    return numberToIndexes[number]?.poll() ?: -1
  }

  // O(n)
  fun deleteNumber(number: Int) {
    if (number !in numberToIndexes) return
    for (index in numberToIndexes.getValue(number)){
      indexToNumber -= index
    }
    numberToIndexes -= number
  }
}

*/







// MY UNDERSTANDING
// you are given number and an index with it. 
// if there is a number at an index, you replace it. 
// for a given number, you have 


#include <bits/stdc++.h>
using namespace std;

class NumberContainer {

	unordered_map<int, int> indexToNumber;
	unordered_map<int, set<int>> numberToIndex;

public:

	void print() {

		cout << "indexToNumber\n";
		for (auto it: indexToNumber) {
			cout << it.first << " " << it.second << "\n";
		}
		cout << "numberToIndex\n";
		for (auto it: numberToIndex) {
			cout << it.first << " = ";
			for (auto x: it.second) {
				cout << x << ", ";
			}
			cout << "\n";
		}
		cout << "\n";
	}

    // O(log n)
	void insertOrReplace(int index, int number) {
        
        cout << "inserting: index: " << index << ", number: " << number << "\n";

		auto idxNumIterator = indexToNumber.find(index);            // O(1)
		if (idxNumIterator != indexToNumber.end()) {

            int numberAtThisIndex = (*idxNumIterator).second;       
            numberToIndex[numberAtThisIndex].erase(index);          // O(log n)
            
            if (numberToIndex[numberAtThisIndex].size() == 0)
                this -> deleteNumber(numberAtThisIndex);                // O(1)
		}

		indexToNumber[index] = number;
		numberToIndex[number].insert(index);            // O(log n)

		print();
	}

    // O(1)
	int findSmallestIndex(int number) {

        return *numberToIndex[number].begin();
	}

    // O(n)
	void deleteNumber(int number) {
        
        auto numberIdxIterator = numberToIndex.find(number);        // O(1)
        // number don't exists anyways
        if (numberIdxIterator == numberToIndex.end())
            return;

        for (int index: numberToIndex[number]) {            // O(n)
            indexToNumber.erase(index);
        }
        numberToIndex.erase(numberIdxIterator);             // O(1)
	}
};


int main() {

	NumberContainer nc;

	nc.insertOrReplace(1, 2);
	nc.insertOrReplace(2, 2);
	nc.insertOrReplace(2, 3);
	nc.insertOrReplace(4, 5);
    nc.insertOrReplace(4, 2);
    
    nc.deleteNumber(5);
    
    cout << "smallest 2: " << nc.findSmallestIndex(2) << "\n";
    cout << "smallest 3: " << nc.findSmallestIndex(3) << "\n";

	return 0;
}