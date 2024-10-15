// 189. Rotate Array
// https://leetcode.com/problems/rotate-array/description/

class Solution {
public:
	void rotate(vector<int>& a, int k) {

		int n = a.size();
		k = k % n;

		// reverse entire array
		reverse(a.begin(), a.end());

		// reverse first k 
		reverse(a.begin(), a.begin() + k);

		// reverse last (n-k)
		reverse(a.begin() + k, a.end()); 
	}
};