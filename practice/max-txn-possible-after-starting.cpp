// Consider a bank with some intial amount of money. 
// Consider an array which represents
// list of transactions which are going to come
// through customers. + means deposit - means
// withdrawl. Bank can choose from which
// customer they want to start serving the
// customers and they can refuse any number of
// customers. But once they start they have to
// serve till the time its impossible to serve
// the customers. Maximize the total customers
// bank can serve.
 
// Example
// Initial Amount = 1
// Customer transactions = [1, -3, 5, -2, 1]
// answer = 3

// { -990, 10, 10, -40, 10, 10, -10, -10, 5, -2, 1 }

// 11
// -990 10 10 -40 10 10 -10 -10 5 -2 1
// 1000

// 5
// 1 -3 5 -2 1
// 1

#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pb push_back

int findMaxLength(vi a, int n, int balance)
{
	int maxLen = 0;

	int i = 0;
	int j = 0;
	int sum = balance;
	while(j < n)
	{
		sum += a[j];

		if (sum >= 0)
		{
			maxLen = max(maxLen, j - i + 1);
		}
		else
		{
			while(sum < 0)
			{
				sum -= a[i];
				i++;
			}
			maxLen = max(maxLen, j - i + 1);
		}

		j++;
	}

	cout << "start: " << i << endl;

	return maxLen;
}

int main()
{
	int n = 5;
	// cin >> n;

	vi a = { 1, -3, 5, -2, 1 };
	// for(int i = 0 ; i < n ; i++)
	// {
	// 	int x; cin >> x;
	// 	a.pb(x);
	// }

	int balance = 1;
	// cin >> balance;

	int res = findMaxLength(a, n, balance);
	cout << "max len: " << res << endl;

	return 0;
}