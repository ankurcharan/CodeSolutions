// 128. Longest Consecutive Sequence
// https://leetcode.com/problems/longest-consecutive-sequence/description/

class Solution {
public:
	int longestConsecutive(vector<int>& a) {
		
		int n = a.size();
		vector<int> dp(n, 1);

		int ans = 0;

		unordered_set<int> s;
		for (int i = 0 ; i < n ; i++) { 
			s.insert(a[i]);
		}

		for (int i = 0 ; i < n ; i++) {

			if (s.find(a[i] - 1) == s.end())  {   // no smaller element

				int x = a[i];
				while (s.find(x) != s.end()) {
					x++;
				}

				ans = max(ans, x - a[i]);
			}
		}

		return ans;
	}
};