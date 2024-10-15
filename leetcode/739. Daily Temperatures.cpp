// 739. Daily Temperatures
// https://leetcode.com/problems/daily-temperatures/

#define F first
#define S second

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        
        int n = temperatures.size();

        // (temp, index)
        stack<pair<int, int>> s;

        vector<int> ans(n, 0);

        for (int i = 0 ; i < n ; i++) {

            while (!s.empty()) {

                if (s.top().F < temperatures[i]) {
                    pair<int, int> f = s.top();
                    s.pop();

                    ans[f.S] = i - f.S;
                }
                else
                    break;
            }

            s.push({ temperatures[i], i });
        }

        return ans;
    }
};