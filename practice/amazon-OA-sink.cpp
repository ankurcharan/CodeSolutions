// amazon-OA-sink


#include <bits/stdc++.h>
using namespace std;

void getSumDiff(vector<int>& a, vector<long long int>& prefix, set<int>& s) {

	int st = -1;

	long long int sum = 0;

	for (int x: s) {

		if (st == -1) {
			if (x != 0)
				sum += prefix[x - 1];
		}
		else {
			sum += prefix[x - 1] - prefix[st];
		}

		st = x;
	}

	cout << "sum: " << sum << endl;
}

void printStuff(vector<int>& a, vector<pair<int, int>>& q) {

	int nq = q.size();
	int n = a.size();

	set<int> s;
	s.insert(n - 1);

	vector<long long int> prefix(n, 0);
	prefix[0] = a[0];
	for (int i = 1 ; i < n ; i++) {
		prefix[i] += prefix[i - 1] + a[i];
	}

	for (int i = 0 ; i < n ; i++) {
		cout << setw(3) << a[i] << " ";
	}
	cout << "\n";
	for (int i = 0 ; i < n ; i++) {
		cout << setw(3) << prefix[i] << " ";
	}
	cout << "\n";

	getSumDiff(a, prefix, s);
	for (int i = 0 ;i < nq ; i++) {
		s.insert(q[i].first);
		s.insert(q[i].second);

		getSumDiff(a, prefix, s);
	}
}

int main() {
	
				   // 0  1  2  3  4   5   6
	vector<int> a = { 2, 5, 6, 8, 9, 11, 15 };
	vector<pair<int, int>> q = { { 3, 4 }, { 1, 5} };

	printStuff(a, q);

	return 0;
}