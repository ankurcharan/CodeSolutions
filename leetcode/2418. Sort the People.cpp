// 2418. Sort the People
// https://leetcode.com/problems/sort-the-people/

class cmp {
public:
	bool operator()(pair<string, int> a, pair<string, int> b) {
		return a.second < b.second;
	}
}

class Solution {
public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        
        int n = names.size();
        if (n == 0)	return {};

        vector<pair<string, int>> a;

        for (int i = 0 ; i < n ; i++) {
        	a.push_back({  names[i], heights[i] });
        }

        sort(a.begin(), a.end(), cmp);

        vector<string> ans;
        for (int i = 0 ; i < n ; i++) {
        	ans.push_back(a[i].first);
        }

        return ans;
    }
};