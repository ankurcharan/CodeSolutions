// 11. Container With Most Water
// https://leetcode.com/problems/container-with-most-water/description/

class Solution {
public:
	int twoPointer(vector<int> &h) {

		int l = 0; 
        int r = h.size() - 1;

        int ans = 0;

        while (l < r) {

        	ans = max(ans, min(h[l], h[r]) * (r - l));

        	if (h[l] <= h[r])
        		l++;
        	else
        		r--;
        }

        return ans;
	}

	int bruteforce(vector<int> &h) {

		int n = h.size();
		if (n == 0)
			return 0;

		int ans = 0;

		for (int i = 0 ; i < n ; i++) {
			for (int j = i + 1 ; j < n ; j++) {
				ans = max(ans, min(h[i], h[j]) * (j - i));
			}
		}

		return ans;
	}

    int maxArea(vector<int>& h) {
        
        // return bruteforce(h);		// TLE

        return twoPointer(h);
    }
};