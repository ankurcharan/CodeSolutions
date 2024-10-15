// 78. Subsets
// https://leetcode.com/problems/subsets/description/

class Solution {
public:
	void getSubsets(vector<int>& a, int curr, int n, vector<int>& currSubset, vector<vector<int>>& powerSet) {

		if (curr == n) {
			powerSet.push_back(currSubset);
			return;
		}

		getSubsets(a, curr + 1, n, currSubset, powerSet);

		currSubset.push_back(a[curr]);
		getSubsets(a, curr + 1, n, currSubset, powerSet);
		currSubset.pop_back();
	}

    vector<vector<int>> recursion(vector<int>& nums) {

    	vector<vector<int>> powerSet;
        vector<int> currSubset;

        getSubsets(nums, 0, nums.size(), currSubset, powerSet);
    
        return powerSet;
    }

    vector<vector<int>> bitmasking(vector<int>& a) {

    	int n = a.size();
    	int numOfSubsets = pow(2, n);

    	vector<vector<int>> powerSet;

    	for (int i = 0 ; i < numOfSubsets ; i++) {

			// string bitmask = bitset<32>(i | (1 << n)).to_string().substr(1);
			bitset<32> b(i | (1 << n));

    		vector<int> currSubset;
    		for (int z = 0 ; z < 32 && z < n ; z++) {

    			if (b.test(z))
    				currSubset.push_back(a[z]);
    		}

    		powerSet.push_back(currSubset);
    	}

    	return powerSet;
    }	


    vector<vector<int>> subsets(vector<int>& nums) {
        
        // return recursion(nums);

        return bitmasking(nums);
    }
};