// 238. Product of Array Except Self
// https://leetcode.com/problems/product-of-array-except-self/

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& a) {
        
        int n = a.size();

        vector<int> ans(n, 0);

        if (n == 0)
            return ans;

        ans[0] = 1;     // left product 
        for (int i = 1 ; i < n ; i++)
        {
            // curr product = left product * left element
            ans[i] = ans[i - 1] * a[i - 1];
        }
        int right = 1;
        for (int i = n - 1 ; i >= 0 ; i--)
        {
            ans[i] = ans[i] * right;
            right = right * a[i];
        }

        return ans;
    }
};