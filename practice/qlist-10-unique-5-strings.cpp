// qlist-10-unique-5-strings

// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792

////////////////////////////////////////////////////////////////////////////////////////////////////
// this list has a couple of questions
// here is que 5
////////////////////////////////////////////////////////////////////////////////////////////////////



/*

https://leetcode.com/discuss/interview-question/4223234/5-unique-strings/




Give a list of string, where every string in the list is of size 5.
Return the list of 5 string such that all the characters in each of the strings are unique
i.e if we combine all the strings(not nnecessary) we will have 25 unique characters)
eg

Input explanation
List of string with length of 5 each
input = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "zabcd", "apple", "zebra", "ocean", "quick", 
			"world", "jumps", "foxes", "liver"]


all the 5 string have unique character for both of the way
ouput = ["abcde", "fghij", "klmno", "pqrst", "uvwxy"] or ["fghij", "klmno", "pqrst", "uvwxy", "zabcd"]


Got the intution of using with subsequence which will take TC : O(2^n)
Looking for optimal approach

*/

#include <bits/stdc++.h>
using namespace std;

bool getUniqueString(vector<string> in, int i, int n, unordered_set<char>& c, vector<string>& ans) {

	// got to your end
	if (ans.size() == 5) {
		return true;
	}

	// no more strings
	if (i == n) {
		return false;
	}

	bool currIncluded = true;
	for (int x = 0 ; x < 5 ; x++) {

		int curr = in[i][x];
		if (c.count(curr) == 0) {
			c.insert(curr);
		} 
		else {

			currIncluded = false;
			// undo your stuff
			for (x = x - 1 ; x >= 0 ; x--) {
				c.erase(in[i][x]);
			}
			break;
		}
	}

	bool transitiveAns = false;

	if (currIncluded) {

		ans.push_back(in[i]);
		transitiveAns = getUniqueString(in, i + 1, n, c, ans);

		if (transitiveAns)
			return true;		// found ans
		else {

			// undo changes
			for (int x = 0 ; x < 5 ; x++) {
				c.erase(in[i][x]);
			}
			ans.pop_back();
		}
	}

	// no included ans

	transitiveAns = getUniqueString(in, i + 1, n, c, ans);
	return transitiveAns;
}

int main() {

	//// testcase 1
	vector<string> in = {
		"abcde", "fghij", "klmno", "pqrst", "uvwxy", "zabcd", "apple", 
		"zebra", "ocean", "quick", "world", "jumps", "foxes", "liver"
	};

	// //// testcase 2
	// vector<string> in = {
	// 	"aabcde", "fghij", "klmno", "pqrst", "uvwxy", "zabcd", "apple", 
	// 	"zebra", "ocean", "quick", "world", "jumps", "foxes", "liver"
	// };

	unordered_set<char> c;

	int n = in.size();
	vector<string> ans;
	bool solved = getUniqueString(in, 0, n, c, ans);

	if (solved == false) {
		cout << "no solution\n";
		return 0;
	}

	for (string x: ans) {
		cout << x << " ";
	}
	cout << endl;

	return 0;
}




