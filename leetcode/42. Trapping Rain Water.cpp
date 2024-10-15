// 42. Trapping Rain Water
// https://leetcode.com/problems/trapping-rain-water/description/

class Solution {
public:
	int twoPointer(vector<int>& height) {

        int l = 0;
        int r = height.size() - 1;

        int lmax = 0;
        int rmax = 0;

        int ans = 0;

        while (l <= r) {

        	if (height[l] <  height[r]) {

        		ans += max(0, lmax - height[l]);
        		lmax = max(lmax, height[l]);
        	    l++;
            }
        	else {

        		ans += max(0, rmax - height[r]);
        		rmax = max(rmax, height[r]);
        	    r--;
            }
        }

        return ans;
	}

	int stackAns(vector<int>& height) {

		int ans = 0;
		stack<int> s;

		int n = height.size();
		for (int i = 0 ; i < n ; i++) {

			while (!s.empty() && height[s.top()] < height[i]) {

				int topHeight = height[s.top()];
				s.pop();

				// popped bars have no left booundary 
				// stack does not have any bars
				if (s.empty()) {
					break;
				}

				int dist = i - s.top() - 1;
				int minHeight = min(height[s.top()], height[i]) - topHeight;
				ans += dist * minHeight;
			}

			s.push(i);
		}

		return ans;
	}

	int horizontalScan(vector<int>& height) {

		int totalBlocks = 0;
		int n = height.size();
		int maxHeight = 0;

		for (int ht: height) {
			maxHeight = max(maxHeight, ht);
			totalBlocks += ht;
		}

		int totalWater = 0;
		int left = 0;
		int right = n - 1;

		for (int i = 1 ; i <= maxHeight ; i++) {

			while (height[left] < i)
				left++;

			while (height[right] < i)
				right--;

			totalWater += (right - left + 1);
		}

		totalWater -= totalBlocks;

		return totalWater;
	}

    int trap(vector<int>& height) {
        
        // return twoPointer(height);

        // return stackAns(height);

        return horizontalScan(height);	// O(1) space -- O(n) time
    }
};