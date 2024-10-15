// 1894. Find the Student that Will Replace the Chalk
// https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/description/


class Solution {
public:
	int prefixSum(vector<int>& chalk, int k) {

        if (chalk.size() == 0)
            return 0;

        long long int sum = 0;
        for (int i = 0 ; i < chalk.size() ; i++) {

            sum += chalk[i];
            if (sum > k)
                break;
        }

    	k = k % sum;
        
        for (int i = 0 ; i < chalk.size() ; i++) {

            if (k < chalk[i])
                return i;

            k = k - chalk[i];
        }

        return 0;   // got at first place if sum < k
	}

	int binarySearch(vector<int> chalk, int k) {

		int n = chalk.size();

		if (n == 0)
			return 0;

		vector<int> prefixSum(k, 0);
		
		prefixSum[0] = chalk[0];
		for (int i = 1 ; i < n ; i++)
			prefixSum[i] = prefixSum[i - 1] + chalk[i];

		long long sum = prefixSum[n - 1];

		k = k % sum;		// remaining chalk

		return binarySearchIndex(prefixSum, k);
	}

	int binarySearchIndex(vector<int> prefixSum, int k) {

		int l = 0;
		int h = prefixSum.size();

		while (l < h) {

			int mid = l + (h - l)/2;

			if (prefixSum[mid] <= k)
				l = mid + 1;
			else
				h = mid;
		}

		return h;
	}

    int chalkReplacer(vector<int>& chalk, int k) {

    	return prefixSum(chalk, k);

    	// return prefixSum(chalk, k);
    }
};

