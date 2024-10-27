// https://leetcode.com/discuss/interview-question/4314794/GOOGLE-SDE-2-CODING-ROUND-1%3A-Find-the-in-compatible-pair-of-unit-tests/

#include<bits/stdc++.h>
using namespace std;

// max number of tests
// have to be constant cause bitset only takes constant values
const int N = 100;

// the faulty pair
int x = 0;
int y = 7;

// run in O(n)
bool testRunner(bitset<N>& b) {

	if (b[x] && b[y])
		return false;

	return true;
}

void setBitsInRange(bitset<N>& b, int s, int e, int bit) {

	for (int i = s ; i <= e ; i++) 
		b[i] = bit;
} 

pair<int, int> findPairFinal(int l, int mid, int r) {

    // cout << "pair final: " << l << "-" << mid << "-" << r << "\n";
	bitset<N> b;

	// set bit in right = 1
	setBitsInRange(b, mid + 1, r, 1);

	int firstTest = -1;
	// set the left bit 
	for (int i = l ; i <= mid ; i++) {

		b[i] = 1;
		if (testRunner(b) == false) {
			firstTest = i;
			break;	// found the test from left
		}
        b[i] = 0;
	}

	int secondTest = -1;
	// set right bits = 0;
	setBitsInRange(b, mid + 1, r, 0);
	for (int i = mid + 1 ; i <= r ; i++) {

		b[i] = 1;
		if (testRunner(b) == false) {
			secondTest = i;
			break;
		}
		b[i] = 0;
	}

	return { firstTest, secondTest };
}

pair<int, int> findFaultyPair(int n) {

	bitset<N> b;

	int l = 0;
	int r = n - 1;

	while (l < r) {
        
		int mid = (l + r) / 2;

        cout << '(' << l << ',' << mid << ',' << r << ')' << '\n';
        
		// set bits 0...mid and test
		b.reset();
		setBitsInRange(b, l, mid, 1);

		bool left = testRunner(b);

		// set bits mid+1...e and test
		b.reset();
		setBitsInRange(b, mid + 1, r, 1);
	
		bool right = testRunner(b);

		if (!left) 
			r = mid;
		else if (!right)
			l = mid;
		else {

			// find the faulty pair here
			return findPairFinal(l, mid, r);
		}
	}

	// no pair found
	return { -1, -1 };
}

int main() {

	// no of tests - actual
	int n = 100;

	// faulty pair
	x = 0;
	y = 7;
    

	pair<int, int> p = findFaultyPair(n);
	cout << "pair found: (" << p.first << ", " << p.second << ")";

	return 0;
}