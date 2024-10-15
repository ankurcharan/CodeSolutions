// 1310. XOR Queries of a Subarray
// https://leetcode.com/problems/xor-queries-of-a-subarray/description

class Solution {
public:
    vector<int> xorQueries(vector<int>& a, vector<vector<int>>& queries) {
        
        for (int i = 1 ; i < a.size() ; i++)
        	a[i] = a[i] ^ a[i - 1];

        vector<int> ans;

        int n = queries.size();
        for (int i = 0 ; i < n ; i++) {

            // cause then we can get the previous index
            if (queries[i][0] > 0)
                ans.push_back(a[queries[i][0] - 1] ^ a[queries[i][1]]);
            else 
                ans.push_back(a[queries[i][1]]);
        }

        return ans;
    }
};