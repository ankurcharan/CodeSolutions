// 1. Two Sum
// https://leetcode.com/problems/two-sum/description/

class Solution {
public:
    vector<int> twoSum(vector<int>& a, int target) {

    	int n = a.size();
		unordered_map<int, int> m;

		for (int i = 0 ; i < n ; i++)
		{
			if (m.find(target - a[i]) != m.end())
			{
				vector<int> ans { m[target - a[i]], i };
				return ans;
			}
			m[a[i]] = i;
		}

		vector<int> ans { -1, -1 };
		return ans;
    }
};