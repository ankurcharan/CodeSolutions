// 33. Search in Rotated Sorted Array
// https://leetcode.com/problems/search-in-rotated-sorted-array/

class Solution {
public:
	// only work in case of distinct values. 
	// this method won't work if we have duplicate values
    int search(vector<int>& a, int target) {
        
        int l = 0;
        int r = a.size() - 1;

        while (l <= r) {

        	int mid = l + (r - l) / 2;

        	// find key
        	if (a[mid] == target)
        		return mid;

        	// left half sorted
        	if (a[l] <= a[mid]) {

        		if (target >= a[l] && target <= a[mid])
        			r = mid - 1;
        		else
        			l = mid + 1;
        	}
        	// right half sorted
        	else {

        		if (target >= a[mid] && target <= a[r])
        			l = mid + 1;
        		else
        			r = mid - 1;
        	}
        }

        return -1;
    }
};
