// 1235. Maximum Profit in Job Scheduling
// https://leetcode.com/problems/maximum-profit-in-job-scheduling/description/


bool cmp(pair<pair<int, int>, int>& a, pair<pair<int, int>, int>& b) {

	return a.first.second < b.first.second;
}

class Solution {
public:
	// int getMaxProfit(vector<pair<pair<int, int>, int>>& jobs, int n) {

	// 	if (n == 1)
	// 		return jobs[n - 1].second;		// profit of last item


	// 	// exclude curr item
	// 	int excl = getMaxProfit(jobs, n - 1);
		
	// 	// include curr item
	// 	int incl = jobs[n - 1].second;

	// 	// find latest non-conflict after including curr item
	// 	int j = n - 1;
	// 	while (j >= 0)
	// 	{
	// 		if (jobs[j].first.second <= jobs[n - 1].first.first)
	// 			break;
	// 		j--;
	// 	}

	// 	if (j != -1)
	// 		incl += getMaxProfit(jobs, j + 1);

	// 	return max(incl, excl);
	// }

	// int recursiveSoln(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {

	// 	int n = startTime.size();
    // 	if (n == 0)	return 0;

	// 	vector<pair<pair<int, int>, int>> jobs;
	// 	for (int i = 0 ; i < n ; i++) {
	// 		jobs.push_back({ { startTime[i], endTime[i] }, profit[i] });
	// 	}

	// 	// sorted by finish time
	// 	sort(jobs.begin(), jobs.end(), cmp);   
    	
    // 	int maxProfit = getMaxProfit(jobs, n);
    // 	return maxProfit;
	// }

    int dynamicProgrammingSoln(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {

		int n = startTime.size();
    	if (n == 0)	return 0;

		vector<pair<pair<int, int>, int>> jobs;
		for (int i = 0 ; i < n ; i++) {
			jobs.push_back({ { startTime[i], endTime[i] }, profit[i] });
		}

		sort(jobs.begin(), jobs.end(), cmp);

		int dp[n];
		dp[0] = jobs[0].second;	// select 1 only job

		for (int i = 1 ; i < n ; i++) {

			int excl = dp[i - 1];
			
			int incl = jobs[i].second;
			int j = i - 1;
			while (j >= 0) {
				if (jobs[j].first.second <= jobs[i].first.first)
					break;
				j--;
			}
			if (j != -1)
				incl += dp[j];

			dp[i] = max(excl, incl);
		}

		return dp[n - 1];
    }


    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {

    	// return recursiveSoln(startTime, endTime, profit);		// TLE

    	return dynamicProgrammingSoln(startTime, endTime, profit);
    }
};
