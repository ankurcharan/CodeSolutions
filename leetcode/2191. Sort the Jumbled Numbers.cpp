// 2191. Sort the Jumbled Numbers
// https://leetcode.com/problems/sort-the-jumbled-numbers/

class Solution {
public:
    vector<int> oneSortedStringMapping(vector<int>& mapping, vector<int>& nums) {

        vector<pair<int, int>> storePairs;
        int n = nums.size();

        for (int i = 0 ; i < n ; i++) {

            // int to string
            string number = to_string(nums[i]);
            string formed = "";
            for (int j = 0 ; number[j] != '\0' ; j++) {
                formed += (to_string(mapping[number[j] - '0']));
            }

            cout << number << " -> " << formed << endl;

            // string to int
            int mapped = stoi(formed);

            // push pair to array
            storePairs.push_back({ mapped, i });
        }

        // sort in non-decreasing / increasing order
        sort(storePairs.begin(), storePairs.end());

        vector<int> ans;
        for (auto pair: storePairs)
            ans.push_back(nums[pair.second]);

        return ans;
    }

    vector<int> twoSortedNumberDigitChange(vector<int>& mapping, vector<int>& nums) {

        vector<pair<int, int>> storePairs;
        int n = nums.size();

        for (int i = 0 ; i < n ; i++) {

            int mappedValue = 0;
            int temp = nums[i];

            // start making change
            int place = 1;  // unit's place
            if (temp == 0) {
                storePairs.push_back({ mapping[0], i });
                continue;
            }

            while (temp != 0) {
                mappedValue = place * mapping[temp % 10] + mappedValue;
                place *= 10;
                temp /= 10;
            }

            storePairs.push_back({ mappedValue, i });
        }

        // sort in non-decreasing / increasing order
        sort(storePairs.begin(), storePairs.end());

        vector<int> ans;
        for (auto pair: storePairs)
            ans.push_back(nums[pair.second]);

        return ans;
    }

    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        
        return oneSortedStringMapping(mapping, nums);

        return twoSortedNumberDigitChange(mapping, nums);
    }
};