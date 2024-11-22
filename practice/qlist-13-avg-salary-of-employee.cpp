// qlist-13-avg-salary-or-employee

// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792

////////////////////////////////////////////////////////////////////////////////////////////////////
// this list has a couple of questions
// here is que 13
////////////////////////////////////////////////////////////////////////////////////////////////////




/*

Give the count of managers who has salary less than average salary of direct and indirect employees
Example:
A->B, A->C, A->D, B->E
Salaries
A = 50000
B = 20000
C = 10000
D = 10000
E = 25000
Answer: 1
Explanation: A is the manager of direct employees B, C, D and 
indirect employee E so avg. is 16,250 and B = 20000 < E = 25000 so answer is B

*/


#include <bits/stdc++.h>
using namespace std;

class Node {
public:
	int salary;
	int childCount;
	int sumSalary;

	list<Node*> children;

	Node(int s) {
		this -> salary = s;
		this -> childCount = 0;
	}
};

int countManagerWithLessThanAvgSalary(unordered_map<char, int>& salary, vector<pair<char, char>>& edges) {

	unordered_map<int, Node*> nodes;

	for (auto it: salary) {
		cout << "create: " << it.first << " = " << it.second << endl;
		nodes[it.first] = new Node(it.second);
	}

	return 0;
}


int main() {

	unordered_map<char, int> salary = {
		{ 'a', 50000 },
		{ 'b', 20000 },
		{ 'c', 10000 },
		{ 'd', 10000 },
		{ 'e', 25000 }
	};

	vector<pair<char, char>> edges = { 
		{ 'a', 'b' },  
		{ 'a', 'c' },
		{ 'a', 'd' },
		{ 'b', 'e' } 
	};

	int ans = countManagerWithLessThanAvgSalary(salary, edges); 
	cout << "ans: " << ans << "\n";

	return 0;
}

