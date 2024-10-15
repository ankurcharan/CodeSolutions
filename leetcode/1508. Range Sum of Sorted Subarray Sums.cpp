// 1508. Range Sum of Sorted Subarray Sums
// https://leetcode.com/problems/range-sum-of-sorted-subarray-sums/editorial/


long int MOD = 1e9 + 7;

class Solution {

	int binarySearchAndSlidingWindow(vector<int>& a, int n, int left, int right) {

		long result = (sumOfFirstK(a, n, right) - sumOfFirstK(a, n, left - 1)) % MOD;
		
		// ensure non-negative value
		return (result + MOD) % MOD;
	}

	long long sumOfFirstK(vector<int>& a, int n, int k) {

		int minSum = *min_element(a.begin(), a.end());
		int maxSum = accumulate(a.begin(), a.end(), 0);

		int left = minSum;
		int right = maxSum;

		while (left <= right) {

			int mid = left + (right - left) / 2;

			if (countAndSum(a, n, mid).first >= k)
				right = mid - 1;
			else
				left = mid + 1;
		}

		pair<int, long long> countNSum = countAndSum(a, n, left);
		int count = countNSum.first;
		long long sum = countNSum.second;

		return sum - left * (count - k);
	}

	// count subarray with sum <= target and their total sum
	// count of subarray, total sum
	pair<int, long long> countAndSum(vector<int>& a, int n, int target) {

		int count = 0;
		long long currentSum = 0;
		long long totalSum = 0;
		long long windowSum = 0;

		for (int j = 0, i = 0 ; j < n ; j++) {

			currentSum += a[j];
			windowSum += a[j] * (j - i + 1);

			while (currentSum > target) {
				windowSum -= currentSum;
				currentSum -= a[i++];
			}

			count += j - i + 1;
			totalSum += windowSum;
		}

		return { count, totalSum };
	}

	int bruteforce(vector<int>& a, int n, int left, int right) {

		long long sum = 0;

		vector<long long> subarraySum;

		for (int i = 0 ; i < n ; i++) {

			sum = 0;
			for (int j = i ; j < n ; j++) {

				sum += a[j];
				subarraySum.push_back(sum);
			}
		}

		sort(subarraySum.begin(), subarraySum.end());

		int ans = 0;
		for (int i = left - 1 ; i < right ; i++) {

			ans += subarraySum[i];
		}

		return ans;
	}

public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        
    	return bruteforce(nums, n, left, right);

        // return binarySearchAndSlidingWindow(nums, n, left, right);
    }
};