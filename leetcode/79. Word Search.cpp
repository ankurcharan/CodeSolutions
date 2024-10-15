// 79. Word Search
// https://leetcode.com/problems/word-search/description/

class Solution {

	int dx[4] = { 0,  0, 1, -1 };
	int dy[4] = { 1 ,-1, 0,  0 };
public:

	bool safeIndex(int i, int j, int n, int m) {
		return i >= 0 && i < n && j >= 0 && j < m;
	}

	bool dfs(int i, int j, int& n, int& m, int curr, int& wordLen, string &word, vector<vector<char>>& board, vector<vector<bool>>& visit) {

		if (curr == wordLen)
			return true;

		if (safeIndex(i, j, n, m) == false)
			return false;

        if (visit[i][j] == true)
            return false;

		if (word[curr] != board[i][j])
			return false;

		visit[i][j] = true;

		for (int z = 0 ; z < 4 ; z++) {

			int nextI = i + dx[z];
			int nextJ = j + dy[z];

			if (dfs(nextI, nextJ, n, m, curr + 1, wordLen, word, board, visit))
				return true;
		}

		visit[i][j] = false;
		return false;
	}


    bool exist(vector<vector<char>>& board, string word) {

		int n = board.size();
		if (n == 0)		return false;

		int m = board[0].size();
		if (m == 0)		return false;

		int wordLen = word.length();
		vector<vector<bool>> visit(n, vector<bool> (m, false));

		for (int i = 0 ; i < n ; i++) {

			for (int j = 0 ; j < m ; j++) {

				if (board[i][j] == word[0]) {

					if (dfs(i, j, n, m, 0, wordLen, word, board, visit)) 
						return true;		// exists
				}
			}
		}

		return false;
    }
};