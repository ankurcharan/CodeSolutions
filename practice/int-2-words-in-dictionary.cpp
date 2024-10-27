// https://leetcode.com/discuss/interview-question/5898854/L5-Google-or-Interview-Exp.-or-Rejected
// int-2-words-in-dictionary.cpp

/**

Mock Interview 1:

Question: Given a list of words and a target word, 
find if the word exists in the dictionary.

Follow-up: Given a matrix of characters, find all the words that exist in the dictionary. You can’t use the same cell twice for each word.
Solution: Solved using Trie.
Feedback: Strong hire.

*/

#include <bits/stdc++.h>
using namespace std;

class node {
public:
	unordered_map<char, node*> child;
	bool isTerminal;

	node() {
		isTerminal = false;
	}
};

void insert(node* root, string s) {

	for (int i = 0 ; s[i] != '\0' ; i++) {

		if (root -> child.find(s[i]) == root -> child.end())
			root -> child[s[i]] = new node();

		root = root -> child[s[i]];
	}

	root -> isTerminal = true;
}

bool search(node* root, string s) {

	for (int i = 0 ; s[i] != '\0' ; i++) {

		if (root -> child.find(s[i]) == root -> child.end())
			return false;

		root = root -> child[s[i]];
	}

	return root -> isTerminal;
}

bool isPresent(vector<string> dict, string word) {

	// create trie
	node* root = new node();
	for (string& s: dict) {
		insert(root, s);
	}

	// search in trie
	return search(root, word);
}

int main() {

	vector<string> dict = { "hello", "world" };

	cout << "hello:  " << boolalpha << isPresent(dict, "hello") << "\n";
	cout << "hello2: " << boolalpha << isPresent(dict, "hello2") << "\n";
	cout << "hel:    " << boolalpha << isPresent(dict, "hel") << "\n";
	cout << "world:  " << boolalpha << isPresent(dict, "world") << "\n";

	return 0;
}