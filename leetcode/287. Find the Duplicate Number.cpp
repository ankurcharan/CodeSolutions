// 287. Find the Duplicate Number
// https://leetcode.com/problems/find-the-duplicate-number/

class Solution {

	void print(vector<int>& a) {

        int n = a.size();
		for (int i = 0 ; i < n ; i++) {
			cout << setw(3) << a[i] << " ";
		}
		cout << "\n";
	}

public:
    int findDuplicate(vector<int>& nums) {
        
        int n = nums.size();

        // cout << "before: ";
        // print(nums);

        for (int i = 0 ; i < n ; i++) {

            int k = nums[i];
            nums[k % (n + 1)] += n + 1;
        }

        // cout << "after:  ";
        // print(nums);

        // cout << "check:  ";

        for (int i = 0 ; i < n ; i++) {
            
            // cout << setw(3) << (nums[i] / (n + 1)) << " ";
            if (nums[i] / (n + 1) >= 2)
                return i;
        }
        // cout << "\n";

        return -1;
    }
};