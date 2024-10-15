// 84. Largest Rectangle in Histogram
// https://leetcode.com/problems/largest-rectangle-in-histogram/description/

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        
        int n = heights.size();

        stack<int> s;
        int maxArea = 0;

        int i = 0;
        while (i < n) {

        	// only heights in increasing order gets pushed to stack
        	if (s.empty() || heights[s.top()] <= heights[i]) {
        		
                s.push(i);
        		i++;
        	}
        	else {		// current height is less than the stack top height

        		// pop the stack top
        		int t = s.top();
        		s.pop();

        		// calculate the area with popped 
        		int topArea = heights[t] * (s.empty() ? i : i - s.top() - 1);
        		maxArea = max(maxArea, topArea);
        	}
        }

        // op remaining bars
        while (s.empty() == false) {

        	int t = s.top();
        	s.pop();

        	// calculate the height from popped index
        	// right index would be curr index (in this case = n)
        	// and left index = s.top() cause stack is in increasing order
        	int topArea = heights[t] * (s.empty() ? i : i - s.top() - 1);
        	maxArea = max(maxArea, topArea);
        }

        return maxArea;
    }
};