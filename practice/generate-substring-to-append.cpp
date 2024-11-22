// generate-substring-to-append
// https://leetcode.com/discuss/interview-question/4947264/Google-or-Phone-or-Generate-Substrings-and-Append-Characters

/*

Given a string, your task is to generate a list of substrings such that 
while appending all of the substrings in the list should give back the original string. 
If the resulting substring is not already present in the list, it should be added to the list.


Examples:


Input: "GOOOOOOGLE"
Output: ["G", "O", "OO", "OOO", "GL", "E"]


Input: "GOOOOOOGLEG"
Output: ["G", "O", "OO", "OOO", "GL", "E", "G"]
handling edge case

*/


/*



I totally do not get the question.
Can someone help me with why below is the answer
["G", "O", "OO", "OOO", "GL", "E"]


But something like
["GOOO", "OOO", "GL", "E"] is not?







The question is asking you to start with 1st character and move ahead, 
though it's not written but from examples 
I could understand that we need to start with minimum viable 
substring and then move forward

*/








// INTUITION
/*
Intuition :


Initialise an empty list to store the substrings.
Iterate through each character in the input string.
For each character, check if adding it to the current substring would 
result in a substring not already present in the list. If so, add it to the list.

Return the list of substrings.

*/

#include <bits/stdc++.h>
using namespace std;

vector<string> getSubstrings(string& a) {

	unordered_set<string> s;
    
    vector<string> ans;

	string substring = "";
	for (int i = 0 ; a[i] != '\0' ; i++) {

		substring.push_back(a[i]);
        // cout << substring << " = sub\n";

		if (s.find(substring) == s.end()) {

            ans.push_back(substring);
			s.insert(substring);
			substring = "";
		}
	}

	if (substring.size() != 0) {
        
        if (s.find(substring) != s.end()) {
            ans.back() += substring;
        }
        else
            ans.push_back(substring);
    }
		

	// return vector<string>(s.begin(), s.end());
    
    return ans;
}

int main() {

	string s;
	vector<string> subs;

	s = "GOOOOOOGLE";
	subs = getSubstrings(s);

	cout << s << "  = ";
	for (string x: subs) {
		cout << x << ", ";
	}
	cout << "\n";

	s = "GOOOOOOGLEG";
	subs = getSubstrings(s);

	cout << s << " = ";
	for (string x: subs) {
		cout << x << ", ";
	}
	cout << "\n";
    
    
    s = "GOOOOOOGLEF";
	subs = getSubstrings(s);

	cout << s << " = ";
	for (string x: subs) {
		cout << x << ", ";
	}
	cout << "\n";


	s = "GOOOOOOGLEGOO";
	subs = getSubstrings(s);

	cout << s << " = ";
	for (string x: subs) {
		cout << x << ", ";
	}
	cout << "\n";

	return 0;
}

