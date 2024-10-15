// 1395. Count Number of Teams
// https://leetcode.com/problems/count-number-of-teams/description/


class Solution {

    int solveDPmemo(vector<int>& rating) {

        int n = rating.size();
        int teams = 0;

        vector<vector<int>> incSeq(n, vector<int> (4, -1));
        vector<vector<int>> decSeq(n, vector<int> (4, -1));
        
        for (int start = 0 ; start < n ; start++) {

            teams += countIncSeq(rating, start, 1, incSeq) + 
                    countDecSeq(rating, start, 1, decSeq);
        }

        return teams;
    }

    int countIncSeq(vector<int>& rating, int currIndex, int size, vector<vector<int>> &incSeq) {

        int n = rating.size();
        if (currIndex == n)
            return 0;

        if (size == 3)
            return 1;

        if (incSeq[currIndex][size] != -1)
            return incSeq[currIndex][size];
    
        int teams = 0;
        for (int nextIndex = currIndex + 1 ; nextIndex < n ; nextIndex++) {

            if (rating[nextIndex] > rating[currIndex])
                teams += countIncSeq(rating, nextIndex, size + 1, incSeq);
        }

        return incSeq[currIndex][size] = teams;
    }

    int countDecSeq(vector<int>& rating, int currIndex, int size, vector<vector<int>> &decSeq) {

        int n = rating.size();
        if (currIndex == n)
            return 0;

        if (size == 3)
            return 1;

        if (decSeq[currIndex][size] != -1)
            return decSeq[currIndex][size];
    
        int teams = 0;
        for (int nextIndex = currIndex + 1 ; nextIndex < n ; nextIndex++) {

            if (rating[nextIndex] < rating[currIndex])
                teams += countDecSeq(rating, nextIndex, size + 1, decSeq);
        }

        return decSeq[currIndex][size] = teams;
    }


    int solveDPtabulate(vector<int>& rating) {

        int n = rating.size();

        vector<vector<int>> incSeq(n, vector<int> (4, 0));
        vector<vector<int>> decSeq(n, vector<int> (4, 0));
        
        for (int i = 0 ; i < n ; i++) {
            incSeq[i][1] = 1;
            decSeq[i][1] = 1;
        }

        // fill tables
        // number of items in team
        for (int count = 2 ; count <= 3 ; count++) {

            for (int i = 0 ; i < n ; i++) {
                for (int j = i + 1 ; j < n ; j++) {

                    if (rating[i] < rating[j]) {
                        incSeq[j][count] += incSeq[i][count - 1];
                    }
                    if (rating[i] > rating[j]) {
                        decSeq[j][count] += decSeq[i][count - 1];
                    }
                }
            }
        }


        // sum all results of length 3
        int teams = 0;
        for (int i = 0 ; i < n ; i++) {
            teams += incSeq[i][3] + decSeq[i][3];
        }

        return teams;
    }

    int solveDPOptimized(vector<int> &rating) {

        int n = rating.size();
        int teams = 0;

        for (int mid = 0 ; mid < n ; mid++) {

            int leftSmaller = 0;
            int rightLarger = 0;


            for (int left = mid - 1 ; left >= 0 ; left--) {
                if (rating[left] < rating[mid])
                    leftSmaller++;
            }

            for (int right = mid + 1 ; right < n ; right++) {
                if (rating[mid] < rating[right])
                    rightLarger++;
            }

            // ascending teams
            teams += leftSmaller * rightLarger;

            // descending teams
            int leftLarger = mid - leftSmaller;
            int rightSmaller = n - 1 - mid - rightLarger;

            teams += leftLarger * rightSmaller;
        }

        return teams;
    }


public:
    int numTeams(vector<int>& rating) {
        
        // return solveDPmemo(rating);

        // return solveDPtabulate(rating);

        // return solveDPOptimized(rating);

        // TODO
        // return BITFenwickTreeTODO(rating);
    }
};