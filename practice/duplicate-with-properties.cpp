// https://leetcode.com/discuss/interview-question/5014822/Google-Phone-Screen-(SDE-II-US)

/*

I had my google phone screen today and completely choked.

You're given a list of elements. Each element has a unique id and 3 properties. Two elements are considered as duplicates if they share any
of the 3 properties. Please write a function that takes the input and returns all the duplicates.

Input:
E1: id1, p1, p2, p3
E2: id2, p1, p4, p5
E3: id3, p6, p7, p8

Output: {{id1, id2}, {id3}}

Input:
E1: id1, p1, p2, p3
E2: id2, p1, p4, p5
E3: id3, p5, p7, p8

Output: {{id1, id3, id3}}

Does anyone know how to solve this?

*/


#include<bits/stdc++.h>
using namespace std;

// find parent
string find(string x, unordered_map<string, string>& dsuGroup) {

	while (dsuGroup[x] != x) {
		dsuGroup[x] = dsuGroup[dsuGroup[x]];
	}

	return x;
}

// union the two sets
void dsuUnion(string x, string y, unordered_map<string, string>& dsuGroup) {

    // cout << "union: " << x << ", " << y << "\n";
    
	string px = find(x, dsuGroup);
	string py = find(y, dsuGroup);
    
    // cout << x << " parent: " << px << "\n";
    // cout << y << " parent: " << py << "\n";

	// not in rank
	dsuGroup[px] = py;
}


vector<vector<string>> getDuplicatesDSU(unordered_map<string, vector<string>> m) {

	unordered_map<string, int> dsuSize;
	unordered_map<string, string> dsuGroup;

	// put in own set / group
	for (auto it: m) {

		// every id is in its own set
		// first insert in dsu 
		// ex. id1 = id2
		dsuGroup[it.first] = it.first;

		for (string prop: it.second) {

			// if property is new
			if (dsuGroup.find(prop) == dsuGroup.end())
				// add property to dsu
				dsuGroup[prop] = it.first;
			// property is repeated i.e. seen again
			// which means this prop belongs to someone else too
			else {
				// union the two nodes, where this property belongs
				dsuUnion(it.first, dsuGroup[prop], dsuGroup);
			}
		}
	}

	// find the sets of property in that set
	unordered_map<string, vector<string>> ans;
    for (auto it: m) {
    	// (id1, {id1, id2})
    	// where id1 is the key and id1 and id2 are the 
    	// two common duplicate ids
		ans[dsuGroup[it.first]].push_back(it.first);
	}

    // convert map to required vector
	vector<vector<string>> ansVector;
	for (auto it: ans) {
		ansVector.push_back(it.second);
	}

	return ansVector;
}

int main() {

	unordered_map<string, vector<string>> m = {

		{ "id1", { "p1", "p2", "p3" } },
		{ "id2", { "p1", "p4", "p5" } },
		{ "id3", { "p6", "p7", "p8" } },
	};

	vector<vector<string>> duplicates = getDuplicatesDSU(m);

	// print final sets
    cout << "sets:\n";
	for (vector<string> f: duplicates) {

		for (string x: f) {
			cout << x << " ";
		}
		cout << "\n";
	}
	return 0;
}