// 15. 3Sum
// https://leetcode.com/problems/3sum/description/


class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& a) {
        
        int n = a.size();
        sort(a.begin(), a.end());

        set<vector<int> > ans;

        for (int i = 0 ; i < n ; i++) {

            int j = i + 1;
            int k = n - 1;
            while (j < k) {

                int sum = a[i] + a[j] + a[k];

                if (sum == 0) {
                    ans.insert({ a[i], a[j], a[k] });
                    ++j; --k;
                }
                else if (sum < 0) {
                    ++j;
                }
                else {
                    --k;
                }
            }
        }

        vector<vector<int>> out(ans.begin(), ans.end());
        return out;
    }
};