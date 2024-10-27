// https://leetcode.com/discuss/interview-question/4874329/Google-onsite-Interview-question

/*

Consider a bank with some intial amount of money. Consider an array which represents list of transactions
which are going to come through customers. + means deposit - means withdrawl. 
Bank can choose from which customer they want to start serving the customers 
and they can refuse any number of customers. But once they start they have to 
serve till the time its impossible to serve the customers. 
Maximize the total customers bank can serve.


Example :
Bank has 1 unit of money intially.
Customer transactions : [1, -3, 5, -2, 1]


answer = 3


Bank starts with customer with deposit of 5
1+ 5 = 6
6 - 2 = 4
4 + 1 =5


If bank starts at in index 0 can only serve 1 customer
1+1 =2
2-3 = -1 not possible


*/

#include<bits/stdc++.h>
using namespace std;

int getStartIndex(vector<int> t) {

	int balance = 1;		// init balance is 1 

	int n = t.size();

	int start = 0;

	for (int i = 0 ; i < n ; i++) {

		balance += t[i];

		while (balance < 0 && start <= i) {
			balance -= t[start++];
		}
	}

	return start;
}


int main() {

	vector<int> txnA = { 1, -3, 5, -2, 1 };
	int startIndexA = getStartIndex(txnA);

	cout << "startIndexA: " << startIndexA << "\n";
    
    vector<int> txnB = { -1, -3, -5, -2, -1 };
	int startIndexB = getStartIndex(txnB);

	cout << "startIndexB: " << startIndexB << "\n";
    
    vector<int> txnC = { -1, -3, -5, -2, -21 };
	int startIndexC = getStartIndex(txnC);

	cout << "startIndexC: " << startIndexC << "\n";

	return 0;
}