// https://leetcode.com/discuss/interview-question/4978447/Google-coding-interview-experience
// https://leetcode.com/discuss/interview-question/4947290/google-phone-maximum-total-score

/*

Given a sequence of stones with non-negative integers, calculate the maximum possible score 
starting from the beginning to end. You can jump any number of positions from each position. 
The score is calculated as the destination stone_value * number_of_jump_positions. 
Essentially the first value in the array doesn't matter as you always jump from beginning 
and only the destination stone value is considered in the score computation. 
You need to solve it in less than O(n^2) time.


I could come up with O(n^2) solution but couldn't solve it in less than that time complexity. 
Any ideas leetcoders?


For example,
Test case 1: Stones = [1, 2, 3, 4, 5], Maximum total score = 20 #you jump to ast position, so the score would be 5 * 4 = 20
Test case 2: Stones = [5, 4, 3, 2, 1], Maximum total score = 10 #you jump one position from beginning to end, so the score would be 4+3+2+1=10
Test case 3: Stones = [2, 4, 6, 8, 10], Maximum total score = 40
Test case 4: Stones = [3, 5, 2, 8, 1], Maximum total score = 25
Test case 5: Stones = [1, 1, 1, 1, 1], Maximum total score = 4
Test case 6: Stones = [5, 3, 5, 3, 5], Maximum total score = 20

*/


#include<bits/stdc++.h>
using namespace std;

int getMaxScore(vector<int>& a) {

	int n = a.size();

	vector<int> rightMaxIndex(n);
	rightMaxIndex[n - 1] = n - 1;
	int maxStoneIndex = n - 1;		// initially take right most element as max

	for (int i = n - 2 ; i >= 0 ; i--) {

		rightMaxIndex[i] = maxStoneIndex;

		if (a[i] > a[maxStoneIndex]) {
			maxStoneIndex = i;
		}
	}

	// printing right max index
	for (int i = 0 ; i < n ; i++) {
		cout << rightMaxIndex[i] << " ";
	}
	cout << "\n";


	int totalScore = 0;
	// current index
	int idx = 0;
	// stop at index = n - 1
	while (idx < n - 1) {

		int nextIndex = rightMaxIndex[idx];

		int jumpScore = (nextIndex - idx) * a[nextIndex];
		totalScore += jumpScore;

		idx = nextIndex;
	}

	return totalScore;
} 

int main() {

	vector<int> a = { 1, 2, 3, 4, 5 };
	cout << "a: " << getMaxScore(a) << "\n";

	vector<int> b = { 5, 4, 3, 2, 1 };
	cout << "b: " << getMaxScore(b) << "\n";

	vector<int> c = { 2, 4, 6, 8, 10 };
	cout << "c: " << getMaxScore(c) << "\n";

	vector<int> d = { 3, 5, 2, 8, 1 };
	cout << "d: " << getMaxScore(d) << "\n";

	vector<int> e = { 1, 1, 1, 1, 1 };
	cout << "e: " << getMaxScore(e) << "\n";

	vector<int> f = { 5, 3, 5, 3, 5 };
	cout << "f: " << getMaxScore(f) << "\n";
}