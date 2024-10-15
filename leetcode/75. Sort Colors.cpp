// 75. Sort Colors
// https://leetcode.com/problems/sort-colors/description/

class Solution {
public:
	void countMethod(vector<int> &a) {

		
		int zero = 0;
		int one = 0;
		int two = 0;

		int n = a.size();
		for (int i = 0 ; i < n ; i++) {
			
			if (a[i] == 0)
				zero++;
			else if (a[i] == 1)
				one++;
			else if (a[i] == 2)
				two++;
		}

		int i = 0;
		while (i < n && zero--)
			a[i] = 0, i++;
		while (i < n && one--)
			a[i] = 1, i++;
		while (i < n && two--)
			a[i] = 2, i++;
	}

	void dutchNationalFlagAlgorithm(vector<int> &a) {
		
		int n = a.size();

		int l = 0;
		int m = 0;
		int h = n -1;

		while (m <= h) {
			switch(a[m]) {

				case 0: swap(a[l], a[m]);
					l++;
					m++;
					break;

				case 1: m++;
					break;

				case 2: swap(a[m], a[h]);
					h--;
					break;
			}
		}
	}

	void sortColors(vector<int>& nums) {

		// return countMethod(nums);

		return dutchNationalFlagAlgorithm(nums);      
	}
};