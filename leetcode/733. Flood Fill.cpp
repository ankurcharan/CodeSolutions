// 733. Flood Fill
// https://leetcode.com/problems/flood-fill/description/

class Solution {
public:
	int dx[4] = { 1, -1, 0,  0 };
	int dy[4] = { 0,  0, 1, -1 };

	bool validIndex(int i, int j, int n, int m) {

		return i >= 0 && i < n && j >= 0 && j < m;
	}

	void floodFill(vector<vector<int>>& image, int currX, int currY, int &n, int &m, int prevColor, int color) {

		if (!validIndex(currX, currY, n, m))
			return;

		if (image[currX][currY] != prevColor)
			return;

		image[currX][currY] = color;

		for (int i = 0 ; i < 4 ; i++) {

			int nextX = currX + dx[i];
			int nextY = currY + dy[i];

            floodFill(image, nextX, nextY, n, m, prevColor, color);
		}
	}

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {


    	int n = image.size();
    	if (n == 0)	return {};
    	int m = image[0].size();
    	if (m == 0)	return {};

        if (image[sr][sc] == color)
            return image;

		floodFill(image, sr, sc, n, m, image[sr][sc], color);    

		return image;  
    }
};