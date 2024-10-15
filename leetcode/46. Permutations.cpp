// 46. Permutations
// https://leetcode.com/problems/permutations/description/

class Solution {
public:
    void permute(vector<int>& nums, int l, int r, vector<vector<int>>& ans) {

    	if (l == r) {
    		ans.push_back(nums);
    		return;
    	}

    	for (int i = l ; i <= r ; i++) {

    		swap(nums[l], nums[i]);
    		permute(nums, l + 1, r, ans);
    		swap(nums[l], nums[i]);
    	}
    }


    vector<vector<int>> permute(vector<int>& nums) {
        
        vector<vector<int>> ans;

        permute(nums, 0, nums.size() - 1, ans);

        return ans;
    }
};