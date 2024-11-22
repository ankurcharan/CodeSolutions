// amazon-OA-servers


#include <bits/stdc++.h>
using namespace std;

int findMinTime(int total, vector<int>& servers) {

	int n = servers.size();
	if (n == 0 || n == 1)
		return 0;

	sort(servers.begin(), servers.end());

	int ans = INT_MAX;

	// [ 2, 4, 6, 9 ]
	for (int i = 0 ; i < n ; i++) {

		cout << i << " -> " << servers[i] << " => ";

		cout << "clockwise: ";

		// clockwise
		if (i == 0) {
			cout << ((servers[n - 1] - servers[i])) << " ";
			ans = min(ans, (servers[n - 1] - servers[i]));
		}
		else {
			cout << (total - (servers[i] - servers[i - 1])) << " ";
			ans = min(ans, n - (servers[i] - servers[i - 1]));
		}

		cout << ", \n";

	}

	return ans;
}

int main() {
	

	int n = 5;
	vector<int> servers = { };

	// int n = 5;
	// vector<int> servers = { 1 };

	// int n = 5;
	// vector<int> servers = { 1, 5 };

	// int n = 10;
	// vector<int> servers = { 2, 4, 6, 9 };

	// int n = 10;
	// vector<int> servers = { 10, 1, 9 };

	// int n = 128;
	// vector<int> servers = { 2, 5, 72, 98 };

	// int n = 172895;
	// vector<int> servers = { 1, 3296, 72345, 7 };

	int ans = findMinTime(n, servers);
	cout << "ans: " << ans << "\n";

	return 0;
}