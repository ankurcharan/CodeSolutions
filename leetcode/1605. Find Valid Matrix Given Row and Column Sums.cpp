// 1605. Find Valid Matrix Given Row and Column Sums
// https://leetcode.com/problems/find-valid-matrix-given-row-and-column-sums/

class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        
        int n = rowSum.size();
        int m = colSum.size();

        vector<int> currRowSum(n, 0);
        vector<int> currColSum(m, 0);

        vector<vector<int>> matrix (n, vector<int> (m, 0));

        for (int i = 0 ; i < n ; i++) {
            for (int j = 0 ; j < m ; j++) {

                matrix[i][j] = min(rowSum[i] - currRowSum[i], colSum[j] - currColSum[j]);

                currRowSum[i] += matrix[i][j];
                currColSum[j] += matrix[i][j];
            }
        }

        for (int i = 0 ; i < n ; i++) {
            for (int j = 0 ; j < m ; j++) {

                cout << setw(4) << matrix[i][j] << " ";;
            }
            cout << endl;
        }
        cout << endl;


        return matrix;
    }
};