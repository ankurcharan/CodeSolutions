// 54. Spiral Matrix
// https://leetcode.com/problems/spiral-matrix/description/

class Solution {
public:
	vector<int> naive(vector<vector<int>>& matrix) {

		int n = matrix.size();
        if (n == 0)	return {};

        int m = matrix[0].size();
        if (m == 0)	return {};

        vector<vector<bool>> visit(n, vector<bool> (m, false));
        vector<int> ans;

        // R, D, L, U = right, down, left, up
        int dx[] = { 0, 1,  0, -1 };
        int dy[] = { 1, 0, -1,  0 };

        // current row/col
        int r = 0;
        int c = 0;

        int di = 0; 		// R = right

        for (int i = 0 ; i < (n * m) ; i++) {

        	ans.push_back(matrix[r][c]);

        	visit[r][c] = true;

        	int nextR = r + dx[di];
        	int nextC = c + dy[di];

        	if (nextR >= 0 && nextR < n && nextC >= 0 && nextC < m
        		&& visit[nextR][nextC] == false)
        	{
        		r += dx[di];	// same as nextR
        		c += dy[di];	// same as nextC
        	}
        	else
        	{
        		di = (di + 1) % 4;

        		r += dx[di];		// move to new direction
        		c += dy[di];
        	}
        }

        return ans;
	}

    vector<int> boundaryTraversal(vector<vector<int>>& matrix) {

    	int n = matrix.size();
    	if (n == 0)	return {};

    	int m = matrix[0].size();
    	if (m == 0)	return {};

    	vector<int> ans;

    	int top = 0;
    	int bottom = n - 1;
    	int left = 0;
    	int right = m - 1;

    	while (top <= bottom && left <= right) {

    		// print left to right
    		for (int i = left ; i <= right ; i++) {
    			ans.push_back(matrix[top][i]);
    		}
    		top++;	// increase top so it is not processed again

    		// print top to down
    		for (int i = top ; i <= bottom ; i++) {
    			ans.push_back(matrix[i][right]);
    		}
    		right--;		// right row not used

    		// print right to left
    		if (top <= bottom) {
    			for (int i = right ; i >= left ; i--) {
	    			ans.push_back(matrix[bottom][i]);
	    		}
	    		bottom--;
    		}

    		// print bottom to top
    		if (left <= right) {
    			for (int i = bottom ; i >= top ; i--) {
	    			ans.push_back(matrix[i][left]);
	    		}
	    		left++;
    		}
    	}

    	return ans;
    }



    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        
    	// return naive(matrix);

    	return boundaryTraversal(matrix);
    }
};