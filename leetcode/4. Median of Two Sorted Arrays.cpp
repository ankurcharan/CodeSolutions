// 4. Median of Two Sorted Arrays
// https://leetcode.com/problems/median-of-two-sorted-arrays/description/


class Solution {
public:
    double mergeSort(vector<int>& a, vector<int>& b) {

    	int an = a.size();
    	int bn = b.size();

    	int halfValue = (an + bn) / 2;

    	int m1 = -1;
    	int m2 = -1;

    	int ai = 0;
    	int bi = 0;

    	for (int count = 0 ; count <= halfValue ; count++) {

    		m2 = m1;		// keep track of prev value

    		if (ai < an && bi < bn)
    			m1 = (a[ai] < b[bi]) ? a[ai++] : b[bi++];
    		else if (ai < an)
    			m1 = a[ai++];
    		else if (bi < bn)
    			m1 = b[bi++];
    	}

    	if ((an + bn) & 1)		// odd
    		return m1;
    	else
    		return (m1 + m2) / 2.0;
    }

    double binarySearch(vector<int>& a, vector<int>& b) {

    	int an = a.size();
    	int bn = b.size();

    	if (an > bn) {
    		swap(an, bn);
    		swap(a, b);
    	}

    	int half = (an + bn) / 2;

    	int l = 0;
    	int h = an;

    	while (l <= h) {

    		int midA = l + (h - l) / 2;
    		int midB = half - midA;

    		// left and right partitions of A
			int lA = (midA == 0) ? INT_MIN : a[midA - 1];
			int rA = (midA == an) ? INT_MAX : a[midA];

			// left and right partitions of B
			int lB = (midB == 0) ? INT_MIN : b[midB - 1];
			int rB = (midB == bn) ? INT_MAX : b[midB];

			// check validity of partitions
			if (lA <= rB && lB <= rA)
			{
				// return median

				// odd no of elements
				if ((an + bn) & 1)
					return min(rA, rB);
				// even number of elements
				else
					return (max(lA, lB) + min(rA, rB)) / 2.0;
			}

			if (lA > rB)
				h = midA - 1;
			else
				l = midA + 1;
    	}

    	return 0;
    }


    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        
        // return mergeSort(a, b);

        return binarySearch(a, b);
    }
};