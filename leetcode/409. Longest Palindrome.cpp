// 409. Longest Palindrome
// https://leetcode.com/problems/longest-palindrome/description/

class Solution {
public:
    int longestPalindrome(string s) {
        
        unordered_map<char, int> m;

        for (int i = 0 ; s[i] != '\0' ; i++)
        	m[s[i]]++;

        int ans = 0;
        bool odd = false;
        for (auto& f: m) {

            // cout << f.first << " ,  " << f.second << endl;
            
            odd = odd | f.second & 1;

        	ans += f.second & 1 ? f.second - 1 : f.second;
        }

        if (odd)
        	ans++;

        return ans;
    }
};