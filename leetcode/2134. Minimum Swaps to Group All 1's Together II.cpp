// 2134. Minimum Swaps to Group All 1's Together II
// https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/description/


class Solution {
	int minSwapHelper(vector<int>& a, int x) {

		int n = a.size();

		vector<int> rightSum(n + 1, 0);

		// suffix sum array for counting opp values
		// x ^ 1
		// i.e. 0 ^ 1 = 1 and 
		// 		1 ^ 1 = 0
		// OR
		// x = 1 - x
		// x = 1 - 0 = 1
		// x = 1 - 1 = 0

		// count opp values
		for (int i = n - 1 ; i >= 0 ; i--) {

			rightSum[i] = rightSum[i + 1];
			if (a[i] == (x ^ 1)) {
				rightSum[i]++;
			}
		}

        // for (int i = 0 ; i < n ; i++) {
        //     cout << setw(2) << a[i] << " ";
		// }
        // cout << endl;
        // for (int i = 0 ; i < n ; i++) {
        //     cout << setw(2) << rightSum[i] << " ";
		// }
        // cout << endl;

		// total opp values in array
		// 0's if 1 
		// 1's if 0
		int totalSwapsNeeded = rightSum[0];

		// swaps in segment
		int currentSwapCount = 0;
		int minSwapsAns = totalSwapsNeeded - rightSum[n - totalSwapsNeeded];
        // cout << "minSwapsAns: " << minSwapsAns << endl;

		// find min swaps by sliding potential block of grouped value = x
		for (int i = 0 ; i < totalSwapsNeeded ; i++) {

			if (a[i] == (x ^ 1))
				currentSwapCount++;

			int remaining = (totalSwapsNeeded - i - 1);

			int requiredSwaps = ((i + 1) - currentSwapCount) + (remaining - rightSum[n - remaining]);

			minSwapsAns = min(minSwapsAns, requiredSwaps);
		}

		return minSwapsAns;
	}

	int suffixSum(vector<int>& a) {

        // cout << "zero\n"; 
		int zeroSwap = minSwapHelper(a, 0);
        // cout << "one\n";
        int onesSwap = minSwapHelper(a, 1);
		
		return min(zeroSwap, onesSwap);
	}

	int slidingWindow(vector<int>& a) {

		int minSwapsAns = INT_MAX;

		int totalOnes = accumulate(a.begin(), a.end(), 0);

		int onesCount = a[0];
		int end = 0;

		// sliding window
		for (int start = 0 ; start < a.size() ; start++) {

			// remove element from sliding window
			if (start != 0)
				onesCount -= a[start - 1];

			while (end - start + 1 < totalOnes) {
				end++;
				onesCount -= a[end % a.size()];
			}

			minSwapsAns = min(minSwapsAns, totalOnes - onesCount);
		}

		return minSwapsAns;
	}

public:
    int minSwaps(vector<int>& nums) {
        
        // return suffixSum(nums);

        return slidingWindow(nums);
    }
};