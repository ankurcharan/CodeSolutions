// https://leetcode.com/discuss/interview-question/4799918/Interview-Experience
// maybe-amazon-OA



/**
 * 
Question 1:

Given a string, you have to return the first word in the string having the most number of repeating characters.

Example:

"Today is the greatest day ever!"

Answer:

"greatest."

Both "greatest" and "ever" have the same number of repeating characters, 
at a maximum of 2 (e's & t's in "greatest" and 2 e's in "ever"). 
However, "greatest" occurs first, so "greatest" will be the answer.

Approach:

To obtain each specific word in the string, you can traverse by segmenting words on punctuation. 
I used stringstream in C++. 
Then, I used a map for each word to track the frequency of characters, then have a 
global maximum variable and a string called the result word. 
Normal traversal over stringstream and hashing to get the first word in the string having the 
most number of repeating characters.

Overall Approach: StringStream + hashing.

Time complexity: O(n*m)

Space Complexity: O(m)

Where n is the length of the string, and m is the length of the largest word in the string.

I accomplished all this in 10-15 minutes.

 * 
 * **/

#include <bits/stdc++.h>
using namespace std;

// int getFreq(string& a) {

// 	unordered_map<char, int> f;

// 	for (int i = 0 ; a[i] != '\0' ; i++) {
// 		f[a[i]]++;
// 	}

// 	int ans = -1;
// 	for (auto it: f) {
// 		if (it.second > ans) {
// 			ans = it.second;
// 		}
// 	}

// 	return ans;
// }

// string mostRepeatingCharacterWord(string a) {

// 	// // // ###### STRINGSTREAM

// 	// stringstream s(a);
// 	// string token;
// 	// while (getline(s, token, " ")) {
// 	// 	cout << token << "\n";
// 	// }

// 	// while (s >> token) {
// 	// 	cout << token << "\n";
// 	// }


// 	// // // ####### COMMON THINGS

// 	int maxFreq = -1;
// 	string ansWord = "";

// 	// // // ###### CHAR ARRAY

// 	char* s = new char[a.size() + 1];
// 	strcpy(s, a.c_str());			// copies string in char array

// 	// cout << "string: " << s << "\n";		// print string

// 	char* token = strtok(s, " !");
// 	while (token != NULL) {

// 		int l = strlen(token);
// 		string word = "";					// string word(token); || string word = token;
// 		word.assign(token, token + l);
// 		// cout << word << "\n";

// 		int currFreq = getFreq(word);
// 		if (currFreq > maxFreq) {
// 			maxFreq = currFreq;
// 			ansWord = word;
// 		}

// 		token = strtok(NULL, " !");
// 	}


// 	return ansWord;
// }

// int main() {

// 	string a = "Today is the greatest day ever!";

// 	string word = mostRepeatingCharacterWord(a);
// 	cout << word << endl;

// 	return 0;
// }



















/**
 * 
Question 2:

Given an array, return true or false.

Condition:

True -> If there exists a combination that sums to the maximum element in the 
array without using the maximum element.

False -> Otherwise.

Example: [1,3,4,5,12]

Answer: True.
(3,4,5 -> 12)

This problem is similar to the Target Sum problem 
on LeetCode with a modification.

Approach:

Get the maximum element in the array and form a new array/vector without the maximum element. 
After this, apply a recursive approach to 
find the subsequence with the target sum.

Overall Approach: 
Find the maximum + get the new vector without the maximum + Recursion + dynamic programming (target*n).

Time Complexity: O(n*maximum_element)

Space Complexity: O(n*maximum_element)
 * /
 * 
 */

bool sumExist(vector<int>& a, int idx, int sum, int required) {

	if (idx >= a.size())
		return false;

	if (sum == required)
		return true;

	bool ans = sumExist(a, idx + 1, sum, required);
	if (a[idx] != required) {
		ans = ans || sumExist(a, idx + 1, sum + a[idx], required);
	}

	return ans;
}

bool combinationMaxWithoutMaximum(vector<int>& a) {

	int n = a.size();

	if (n == 0 || n == 1)
		return false;

	int m = a[0];
	for (int& x: a)
		m = max(m, x);

	return sumExist(a, 0, 0, m);
}

void print(string term, vector<int>& a) {
	cout << term << ": ";
	for (int& x: a) {
		cout << x << " ";
	}
	cout << endl;
}
void print(vector<vector<int>> dp) {

	int n = dp.size();
	int m = dp[0].size();

	for (int i = 0 ; i < n ; i++) {
		for (int j = 0 ; j < m ; j++) {
			cout << setw(2) << dp[i][j] << " ";
		}
		cout << endl;
	}
}

int countPro = 0;
int ways(vector<int>& a, int idx, int sum, int target, vector<vector<int>>& dp) {

	if (idx == a.size()) {

		if (sum == target)
			return 1;
		return 0;
	}

	if (dp[idx][sum] != -1)
		return dp[idx][sum];

	countPro++;

	int incl = ways(a, idx + 1, sum + a[idx], target, dp);
	int excl = ways(a, idx + 1, sum         , target, dp);

	return dp[idx][sum] = incl + excl;
}

int numberOfWays(vector<int> &a, int &m) {

	print("a: ", a);

	int n = a.size();

	int total = accumulate(a.begin(), a.end(), 0);

	vector<vector<int>> dp(n, vector<int>(total + 1, -1));
	print(dp);

	countPro = 0;


	int ans = ways(a, 0, 0, m, dp);
	cout << endl;
	print(dp);

	cout << "count: " << countPro << "\n";

	return ans;
}

int main() {

	// testcase-1 
	// ans = true
	vector<int> a = { 1, 3, 4, 5, 11, 6, 12 };

	bool ans = combinationMaxWithoutMaximum(a);
	cout << boolalpha << "ans: " << ans << "\n";


	int m = *max_element(a.begin(), a.end());
	vector<int> withoutMax;
	for (int& x: a) {
		if (x != m)
			withoutMax.push_back(x);
	}

	// follow-up maybe
	// no of ways to get the required sum
	int noOfWays = numberOfWays(withoutMax, m);
	cout << "noOfWays: " << noOfWays << endl;


	return 0;
}