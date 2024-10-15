// 525. Contiguous Array
// https://leetcode.com/problems/contiguous-array/description/

class Solution {
public:
    int findMaxLength(vector<int>& a) {
        
        unordered_map<int, int> m;
        int n = a.size();

        int ans= 0;
        int sum = 0;
        for (int i = 0 ; i < n ; i++) {

        	sum += (a[i] == 1) ? 1 : -1;

        	if (sum == 0)
        		ans = max(ans, i + 1);
			
			if (m.find(sum) == m.end())
        		m[sum] = i;
        	else
        		ans = max(ans, i - m[sum]); 
        }

        return ans;
    }
};