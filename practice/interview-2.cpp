
/*

you are given winds in array if int

N = 7;
A = [ 10, 20, 0, 30, 5, 0, 10 ];
K = 3;

k = init energy
you can choose to rest or work on a particular day 

if you work, your energy goes -1
if you rest, your energy goes +1

you cannot work with energy = 0;

if you work, your dist += a[i];

find max distance we can travel

*/


#include <bits/stdc++.h>
using namespace std;

// int maxDistance(vector<int> winds, int k) {

// 	int n = winds.size();
// 	if (n == 0)
// 		return 0;

// 	vector<vector<int>> dp(n, vector<int>(k + 1, 0));

// 	dp[0][k] = 0;
// 	for (int i = 0 ; i < n ; i++) {

// 		for (int j = 0 ; j <= k ; j++) {

// 			dp[i][j] = max(dp[i - 1][j - 1] + winds[i], dp[i - 1][j + 1]);
// 		}
// 	}

// 	for (int i = 0 ; i < n ; i++) {

// 		for (int j = 0 ; j <= k ; j++) {

// 			cout << dp[i][j] << " "; // = max(dp[i - 1][j - 1] + winds[i], dp[i - 1][j + 1]);
// 			cout << endl;
// 		}
// 	}

// 	return -1;
// }

// int main() {
	
// 	vector<int> winds = { 10, 20, 0, 30, 5, 0, 10 };
// 	int k = 3;

// 	int ans = maxDistance(winds, k);
// 	cout << "maxDistance: " << ans << " \n";

// 	return 0;
// }

























// /t(e)(i) = max(A[i] +t(e-1)(i-1), t(max(e+1,k))(i-1))


int helper(int e, int i,int maxEnergy, vector<int>& days, vector<vector<int>>& dp) {

	if(i == -1 || e ==-1) {
		return 0;
	}
	if(dp[i][e] != -1) {
		return dp[i][e];
	}

	int notMoving = helper(min(e + 1, maxEnergy), i - 1, maxEnergy, days, dp);

	int moving = days[i] + helper(e - 1, i - 1, maxEnergy, days, dp);
	
	return dp[i][e] = max(notMoving, moving);
}


int maxDistance(int k, vector<int>& days) {
	
	int n = days.size();
	vector<vector<int>> dp(n, vector<int>(k + 1, -1));
	
	return helper(k, n - 1, k, days, dp);
}


int maxDistanceIterative(int k, vector<int>&days) {

	int n = days.size();
	vector<vector<int>> dp(n, vector<int>(k+1, 0));
	
	for(int i = 0; i < n ; i++) {
		for(int j = 0 ; j < k + 1 ; j++) {

			if(i == 0) {
			
				dp[i][j] = days[i];
			
			} else if(j == 0) {
			
				dp[i][j] = max(dp[i - 1][min(j + 1, k)], days[i]);
			
			} 
			else {

				int notMoving = dp[i - 1][min(j + 1, k)];
				int moving = days[i] + dp[i - 1][j - 1];
 
				dp[i][j] = max(notMoving, moving);
			}
		}
	}
	
	return dp[n - 1][k];
}

int maxDistanceOptimized(int k, vector<int>&days) {

	int n = days.size();

	vector<int> curr(k + 1, 0);

	for(int i = 0 ; i < n ; i++) {

		vector<int> prev = curr;
		
		for(int j = 0 ; j < k + 1 ; j++) {
	
			// if first day
			if(i == 0) {
		
				// you work and move the distance it is on first day
				curr[j] = days[i];
	
			} else if(j == 0) {
		
				// if it is zero energy at the end of the day
				// you either rest the previous day
				// or you work today and make the current work
				curr[j] = max(prev[min(j+1, k)], days[i]);
	
			} else {

				int notMoving = prev[min(j+1, k)];
				int moving = days[i] + prev[j-1];
				curr[j] = max(notMoving, moving);
			}
		}
	}

	return curr[k];
}


int main()
{
	int k = 3;
	vector<int> days = { 10, 20, 0, 30, 5, 0, 10 };

	// cout<<maxDistance(k, days)<<endl;
	// cout<<maxDistanceIterative(k, days)<<endl;
	cout<<maxDistanceOptimized(k, days);
	return 0;
}
















/**




// you are given winds in array if int
// 
// N = 7;
// A = [ 10, 20, 0, 30, 5, 0, 10 ];
// K = 3;
// 
// k = init energy
// you can choose to rest or work on a particular day 

// if you work, your energy goes -1
// if you rest, your energy goes +1

// you cannot work with energy = 0;

// if you work, your dist += a[i];

// find max distance we can travel



#include <bits/stdc++.h>
using namespace std;

int maxDistance(vector<int> winds, int k) {

	int n = winds.size();
	if (n == 0)
		return 0;

	vector<vector<long long int>> dp(n + 1, vector<long long int>(k + 1, 0));

	dp[0][k] = 0;
	for (int i = 0 ; i <= n ; i++) {

		for (int j = 0 ; j <= k ; j++) {

            if (i == 0 || j == 0) {
                dp[i][k] = 0;
                continue;
            }
                
            long long int zero = 0;
            
            if (j != k)
                dp[i][j] = max(dp[i - 1][j - 1], winds[i - 1] + dp[i - 1][j + 1]);
		}
	}

	for (int i = 0 ; i < n ; i++) {

		for (int j = 0 ; j <= k ; j++) {

			cout << setw(2) << dp[i][j] << " "; // = max(dp[i - 1][j - 1] + winds[i], dp[i - 1][j + 1]);
		}
        cout << endl;
	}

	return -1;
}

int main() {
	
	vector<int> winds = { 10, 20, 0, 30, 5, 0, 10 };
	int k = 3;

	int ans = maxDistance(winds, k);
	cout << "maxDistance: " << ans << " \n";

	return 0;
}





*/