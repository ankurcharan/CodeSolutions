// 373. Find K Pairs with Smallest Sums
// https://leetcode.com/problems/find-k-pairs-with-smallest-sums/description/


class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& a, vector<int>& b, int k) {
        
        if (k == 0)
        	return {};

        vector<vector<int>> pairs;  

        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> mh;

        int na = a.size();
        int nb = b.size();
    
    	pairs.push_back({ a[0], b[0] });
		mh.push({ a[0] + b[0], { 0, 0 } });

        while (k-- && !mh.empty()) {

        	pair<int, pair<int, int>> f = mh.top();
        	mh.pop();

        	int i = f.second.first;
        	int j = f.second.second;
        	pairs.push_back({ a[i], b[j] });

        	if (i + 1 < n) {
        		mh.push({ a[i + 1], b[j], { i + 1, j } });
        	}

        	if (j + 1 < m) {
        		mh.push({ a[i] + b[j + 1], { i, j + 1 } });
        	}
        }

        return pairs;
    }
};