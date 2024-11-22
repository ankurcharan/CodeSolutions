// int-3-highest-anagram
// https://leetcode.com/discuss/interview-experience/5720580/Google-or-SDE(L3)-or-BangaloreHyd-or-Aug-24/

/**

Round 2 -
	we have a dictionary of words and a 
	function which gives hash of these words and 

	another function which gives 
	score = sum of diff of adjacent characters in a string 

	and implement another function which gives the anagram of the given word with highest score.
	
	Hash of all anagrams is same.


######################
CODE
######################


class Solution
{
	public:
	vectorwords = { "cat", "tac", "dog", "god", "cow" }; 	//given
	
	string getHash(string word);//some hidden implementation =O(1)
	
	int getScore(string word) // sum of diff of adjacent characters in a string=O(len(word))
	{
		//had to write code here
	}
	string findAnagram(string word) //it will return highest score anagram of word -though not word
	{
		//had to write code here
	}
}


Solution-
	unordered_map<int, vector<pair<string, int>>> info;
	
	a precomputation method in which we traverse words array and 
	for each word we calculate hash which would be a 
	key in unordered_map info and for each key we store anagram with score, 

	for each hash - we store 2 anagrams that have the highest score in the sorted order.
	
	This would take O(N*len(word)) as for each word we calculate its score .

	then findAnagram(word) would take O(1) // for hash calculation - 
	then using info we return the anagram with the highest 
	
	score if its equal to word , 
	then we return the second anagram with second highest score for its hash.
*/


#include <bits/stdc++.h>
using namespace std;

int getScore(string s) {

	int ans = 0;

	if (s[0] == '\0')
		return 0;

	for (int i = 1 ; s[i] != '\0' ; i++) {
		ans += abs(s[i] - s[i - 1]);
	}

	return ans;
}

bool sortIncreasedScore(pair<string, int>& a, pair<string, int>& b) {
	return a.second > b.second;
}

void preprocess(vector<string>& words, unordered_map<string, vector<pair<string, int>>>& m) {

	// unordered_map<string, vector<pair<string, int>>> m;

	for (string w: words) {

		string b = w;
		sort(w.begin(), w.end());

		m[w].push_back({ b, getScore(b) });

		sort(m[w].begin(), m[w].end(), sortIncreasedScore);

		if (m[w].size() > 2)
			m[w].pop_back();
	}
}

string getHighestAnagram(unordered_map<string, vector<pair<string, int>>>& m, string w) {

	string b = w;
	sort(w.begin(), w.end());

	if (m.find(w) == m.end())
		return "-1";

	if (m[w][0].first.compare(b) != 0)
		return m[w][0].first;
	else if (m[w].size() > 1)
		return m[w][1].first;
	else
		return "-1";
}

int main() {
	
	vector<string> words = { "cat", "tac", "act", "dog", "dgo", "gdo", "cow" }; 

	unordered_map<string, vector<pair<string, int>>> m;
	preprocess(words, m);

	cout << "printing\n\n";
	for (auto it: m) {
		cout << it.first << " => ";
		for (auto x: it.second) {

			cout << "(" << x.first << ", " << x.second << ") ";
		}
		cout << "\n";
	}

	cout << "\n\n";

	string dgohana = getHighestAnagram(m, "dgo");
	cout << "dgohana: " << dgohana << endl;
	string doghana = getHighestAnagram(m, "dog");
	cout << "doghana: " << doghana << endl;

	return 0;
}