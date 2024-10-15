// 2028. Find Missing Observations
// https://leetcode.com/problems/find-missing-observations/description/

class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {

		int m = rolls.size();

		int sum = accumulate(rolls.begin(), rolls.end(), 0);      
		int reqdSum = (mean * (m + n)) - sum;

		if (reqdSum < n || reqdSum > (6 * n))
			return {};		// not possile

		int distributedValue = reqdSum / n;
		int remaining = reqdSum % n;

		vector<int> elements (n, distributedValue);
		for (int i = 0 ; i < remaining ; i++)
			elements[i]++;

		return elements; 
    }
};