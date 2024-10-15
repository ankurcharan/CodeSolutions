// 36. Valid Sudoku
// https://leetcode.com/problems/valid-sudoku/description/

class Solution {
public:
	bool bruteforce(vector<vector<char>>& board) {

		for (int i = 0 ; i < 9 ; i++) {

			for (int j = 0 ; j < 9 ; j++) {

				if (board[i][j] == '.')
					continue;

				// check in row
				for (int col = 0 ; col < 9 ; col++)
				{
					if (j != col && board[i][col] == board[i][j])
						return false;
				}

				// check in col
				for (int row = 0 ; row < 9 ; row++)
				{
					if (i != row && board[row][j] == board[i][j])
						return false;
				}

				// check in 3x3 box
				int startRow = i / 3 * 3;
				int startCol = j / 3 * 3;

                // cout <<"i: " << i << " j: " << j << " --> startRow: " << startRow << ", startCol: " << startCol << endl;

				for (int x = 0 ; x < 3 ; x++) {
					for (int y = 0 ; y < 3 ; y++) {

						if (x + startRow != i && y + startCol != j && board[x + startRow][y + startCol] == board[i][j])
							return false;
					}
				}
			}
		}   

		return true;
	}

    bool hashingSet(vector<vector<char>>& board) {

    	unordered_set<char> rows[9];
    	unordered_set<char> cols[9];
    	unordered_set<char> boxes[9];

    	for (int i = 0 ; i < 9 ; i++) {

    		for (int j = 0 ; j < 9 ; j++) {

    			if (board[i][j] == '.')
    				continue;

    			int boxIndex = (i / 3) * 3 + (j / 3);
    		
    			if (rows[i].count(board[i][j]) || cols[j].count(board[i][j])
    				|| boxes[boxIndex].count(board[i][j]))
    				return false;

    			rows[i].insert(board[i][j]);
    			cols[j].insert(board[i][j]);
    			boxes[boxIndex].insert(board[i][j]);
    		}
    	}

    	return true;
    }


    bool isValidSudoku(vector<vector<char>>& board) {

		// return bruteforce(board);		// beats 72%

		return hashingSet(board);			// beats 85%
    }
};