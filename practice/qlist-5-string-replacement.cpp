// qlist-5-string-replacement
// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792

////////////////////////////////////////////////////////////////////////////////////////////////////
// this list has a couple of questions
// here is que 5
////////////////////////////////////////////////////////////////////////////////////////////////////



/*

Given map {X=>123, Y=456}
Input: %X%_%Y%
Output: 123_456


Given =>  
map {USER=>admin, HOME=>/%USER%/home} 
Input: I am %USER% My home is %HOME% 
Output: I am admin My home is /admin/home


USER= bob
HOME= /home/%USER% should be substituted as : /home/bob 

ex2:
home/ %USER% -> /home/bob
Hello %USER% -> Hello bob!

ex3:
The user %USER% is at 50%% -> The user bob is at 50%


*/






/*
ALSO at


https://leetcode.com/discuss/interview-question/3482596/String-replacement-library

Can anyone provide a java solution for this problem? This was asked to one of my friend in onsite round 
and he said he has applied topological sort for this.


Suppose we are creating a string replacement library. Given a map of string replacements, 
replace the value in the input string


Given map {X=>123, Y=456}
Input: %X%_%Y%
Output: 123_456


Given map {USER=>admin, HOME=>/%USER%/home}
Input: I am %USER% My home is %HOME%
Output: I am admin My home is /admin/home

google


*/

#include <bits/stdc++.h>
using namespace std;

unordered_set<string> getWord(string& value) {

	unordered_set<string> split;

	string word = "";

	int i = 0;
	while (i < value.size()) {

		if (value[i] == '%') {
			
			string temp = "";

			if (i+1 < value.size() && value[i + 1] == '%')
			{
				word += '%';
				i += 2;
				continue;
			}

			i++;
			while (i < value.size() && value[i] != '%') {
				temp += value[i++];
			}

			word += '%' + temp + '%';

			split.insert(temp);
			temp.clear();
		}
		else {
			word += value[i];
		}


		i++;
	}

	// cout << "word: " << word << "\n";

	return split;
}

string replace(string value, unordered_map<string, string>& dict) {

	string temp = "";

	int i = 0;
	int j = 0;

	while (i < value.size()) {

		if (value[i] == '%') {

			i++;
			if (i < value.size() && value[i] == '%') {
				temp += '%';
				i += 1;
				// cout << "percentage escape\n";
				continue;
			}

			int start = i;
			while (i < value.size() && value[i] != '%') {
				// temp += value[i];
				i++;
			}

			// cout << "start: " << start << ", i: " <<  i << " --> ";

			string keySubstringInBetween = value.substr(start, i - start);

			// cout << "keySubstringInBetween: " << keySubstringInBetween << " -- ";

			string replacedWord = dict[keySubstringInBetween];

			// cout << ", replacingWith: " << replacedWord << endl;

			temp += replacedWord;

			i++;
			j += replacedWord.size();
		}
		else {
			temp += value[i];
			i++;
			j++;
		}
	}

	// cout << "finalreturn: " << temp << endl;
	return temp;
}

string escapeSequence(string s) {

	string ans = "";
	for (int i = 0 ; s[i] != '\0' ; i++) {

		if (s[i] == '%' && s[i + 1] == '%') {
			i++;
			ans += '%';
		}
		else
			ans += s[i];
	}

	// cout << "escape: " << s << " to " << ans << "\n";
	return ans;
}

unordered_map<string, string> fillAbsoluteValues(unordered_map<string, string>& replacements) {


	unordered_map<string, vector<string>> g;		// graph

	unordered_map<string, int> indegree;
	unordered_map<string, string> dictionary;		// our final dictionary

	queue<string> q;		// to use in topo


	for (auto it = replacements.begin() ; it != replacements.end() ; it++) {

		string key = it -> first;
		string value = it -> second;

		// cout << "process: " << key << " = " << value << "\n";

		unordered_set<string> undo = getWord(value);

		// // word dependencies printed
		// cout << key << " = ";
		// for (string xx: undo) {
		// 	cout << xx << " + ";
		// }

		// value doesn't depend on any other value
		if (undo.size() == 0) {

			// cout << " <==> push to queue";

			indegree[key] = 0;
			dictionary[key] = escapeSequence(value);
			q.push(key);
		}
		else {

			// cout << "adding required edges";

			for (auto x = undo.begin() ; x != undo.end() ; x++) {

				indegree[key]++;
				g[*x].push_back(key);
			}
		}
		// cout << endl;
	}

	cout << "\n\ngraph: \n";
	for (auto it: g) {
		cout << it.first << " --> ";
		for (string n : it.second) {

			cout <<  n << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "\n\ntopoStart:\n\n";

	// TOPO
	while(!q.empty()) {

		string f = q.front();
		q.pop();

		string value = replacements[f];

		cout << "pop: " << f << " -- " << value << endl;

		// word doesn't already exist in dictionary
		if (dictionary.find(f) == dictionary.end()) {

			cout << "\n\nstarting replace:\n";

			dictionary[f] = replace(value, dictionary);
		}

		for (auto nextkey: g[f]) {

			indegree[nextkey]--;
			if (indegree[nextkey] == 0) {
				cout << "pushing: " << nextkey  << "\n";
				q.push(nextkey);
			}
		}
	}


	cout << "\n\nfinal dictionary:\n";
	for (auto it: dictionary) {
		cout << it.first << " = " << it.second << endl;
	}
	cout << endl;


	return dictionary;
}

int main () {


	/////////////// testcase 1

	// unordered_map<string, string> replacements = {
	// 	{ "X", "123" },
	// 	{ "Y", "456" },
	// 	{ "Z", "%X%789" },
	// 	{ "M", "%%789" },
	// 	{ "N", "%%%%789" },
	// };

	// // cout << "replacements:\n";
	// // for (auto it: replacements) {
	// // 	cout << it.first << " - " << it.second << "\n";
	// // }
	// // cout << "\n\n";

	// unordered_map<string, string> dictionary = fillAbsoluteValues(replacements);

	// string in = "I%X%_%Y%";
	// cout << replace(in, dictionary);



	/////////////////// testcase 2
	unordered_map<string, string> replacements = {
		{ "USER", "admin" }, 
		{ "HOME", "/%USER%/home" }
	};

	// cout << "replacements:\n";
	// for (auto it: replacements) {
	// 	cout << it.first << " - " << it.second << "\n";
	// }
	// cout << "\n\n";

	unordered_map<string, string> dictionary = fillAbsoluteValues(replacements);

	cout << "\n\n";

	string in = "I am %USER% My home is %HOME%";
	cout << replace(in, dictionary) << endl;

	cout << "\n\n";

	string in2 = "The user %USER% is at 50%%";
	cout << replace(in2, dictionary) << endl;



	return 0;
}