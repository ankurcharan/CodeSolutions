// 704. Binary Search
// https://leetcode.com/problems/binary-search/description/

class Solution {
public:
    int search(vector<int>& a, int target) {
  		
  		int n = a.size();

  		int l = 0;
  		int r = n - 1;

  		while (l <= r) {

  			int mid = l + (r - l) / 2;

  			if (a[mid] == target)
  				return mid;
  			else if (a[mid] > target)
  				r = mid - 1;
  			else
  				l = mid + 1;
  		}

  		return -1;
    }
};