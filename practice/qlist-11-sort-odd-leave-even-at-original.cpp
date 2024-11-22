// qlist-11-sort-odd-leave-even-at-original


// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792

////////////////////////////////////////////////////////////////////////////////////////////////////
// this list has a couple of questions
// here is que 11
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
sort all odd elements and leave even elements as it is at their original position
*/

// help : https://www.geeksforgeeks.org/sort-all-even-numbers-in-the-array-without-changing-order-of-odd-elements/

#include <bits/stdc++.h>
using namespace std;

void sortOdd(vector<int>& a) {

	priority_queue<int, vector<int>, greater<int>> pq;

	for (int x: a) {
		if (x & 1 == 1)
			pq.push(x);
	}

	for (int i = 0 ; i < a.size() ; i++) {

		if (a[i] & 1) {
			a[i] = pq.top();
			pq.pop();
		}
	}
}

void merge(vector<int>& a, int s, int mid, int e) {

	int i = s;
	int j = mid + 1;

	vector<int> merged;

    // cout << "merge : " << s << " " << mid << " "  << e << "\n";

	while (i <= mid && j <= e) {

		if (a[i] % 2 == 0) {		// no need to check for even
			i++;
			continue;
		}
		if (a[j] % 2 == 0) {		// no need to check for even
			j++;
			continue;
		}

		if (a[i] <= a[j]) {
			merged.push_back(a[i++]);
		}
		else {
			merged.push_back(a[j++]);
		}
	}

	while (i <= mid) {
	    if (a[i] & 1)
			merged.push_back(a[i]);
		i++;
	}
		
	while (j <= e) {
	    if (a[j] & 1)
			merged.push_back(a[j]);
	    j++;
	}
		

	int idx = 0;
	for (int i = s ; i <= e ; i++) {
		if (a[i] & 1)		// only replace odd
			a[i] = merged[idx++];
	}
}


void mergeSort(vector<int>& a, int s, int e) {

	if (s >= e) 
		return;

	int mid = (s + e) / 2;
	
// 	cout << "mergeSort:  " << s << " " << mid << " " << e << "\n";

	mergeSort(a, s, mid);
	mergeSort(a, mid + 1, e);


	merge(a, s, mid, e);
}

void sortUsingMergeSort(vector<int>& a) {

	int n = a.size();

	mergeSort(a, 0, n - 1);
}

int main() {

	vector<int> a = { 0, 9, 1, 8, 2, 7, 3, 6, 4, 5 };

	cout << "before: ";
	for (int x: a) {
		cout << setw(2) << x << " ";
	}
	cout << "\n";

	// sortOdd(a);

	sortUsingMergeSort(a);

	cout << "after:  ";
	for (int x: a) {
		cout << setw(2) << x << " ";
	}
	cout << "\n";

	return 0;
}

// before:  0  9  1  8  2  7  3  6  4  5 
// after:   0  1  3  8  2  5  7  6  4  9 
