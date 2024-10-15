// 152. Maximum Product Subarray
// https://leetcode.com/problems/maximum-product-subarray/description/

class Solution {

	int minMaxProduct(vector<int>& a) {

		int n = a.size();

		long long int currMin = a[0];
		long long int currMax = a[0];
		long long int maxProd = a[0];

		for (int i = 1 ; i < n ; i++) {

			long long tempMax = max({ a[i] * 1LL, a[i] * currMax, a[i] * currMin });
			long long tempMin = min({ a[i] * 1LL, a[i] * currMax, a[i] * currMin });

			currMax = tempMax;
			currMin = tempMin;

			maxProd = max(maxProd, currMax);
		}

		return maxProd;
	}

	int traverseBothDirections(vector<int>& a) {

		int n = a.size();

		long long int maxProd = INT_MIN;

		long long int l2r = 1;
		long long int r2l = 1;

		for (int i = 0 ; i < n ; i++) {

			if (l2r == 0) 
				l2r = 1;
			if (r2l == 0)
				r2l = 1;

			l2r = l2r * a[i];
			r2l = r2l * a[n - i - 1];

			maxProd = max({ maxProd, l2r, r2l }); 
		}

		return maxProd;
	}

public:
    int maxProduct(vector<int>& nums) {
        
        // return minMaxProduct(nums);
  		
  		return traverseBothDirections(nums);
    }
};