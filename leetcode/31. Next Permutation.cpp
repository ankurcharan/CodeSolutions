// 31. Next Permutation
// https://leetcode.com/problems/next-permutation/description/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        
        if (nums.size() < 2)
            return;

        // you have to use the (i) and (i + 1)
        int i = nums.size() - 2;
        while (i >= 0 && nums[i] >= nums[i + 1])
        	i--;

        // if not, you're at the last permtuation
        // then you have descending order array
        // reverse to come back to original array
        if (i >= 0) {

        	int j = nums.size() - 1;
        	// find first element which is bigger than curr element
        	while (nums[j] <= nums[i]) {
        		j--;
        	}

        	// a bigger element will definitely exist
        	// because of the loop breaking condition previously
        	swap(nums[i], nums[j]);
        }

        // reverse the elements to the right to sorting order 
        reverse(nums.begin() + i + 1, nums.end());
    }
};