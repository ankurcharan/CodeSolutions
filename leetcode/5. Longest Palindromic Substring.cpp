// 5. Longest Palindromic Substring
// https://leetcode.com/problems/longest-palindromic-substring/description/

class Solution {
public:
    string longestPalindrome(string s) {

    	int maxLength = INT_MIN;
    	int start = -1;

		for (int i = 0 ; s[i] != '\0' ; i++)
		{
			int x = 0;
			while (i - x >= 0 && s[i + x] != '\0' && s[i-x] == s[i+x])
				x++;

			int len = (x - 1) * 2 + 1;
			if (len > maxLength) {
				maxLength = len;
				start = i - x + 1;
			}

            x = 0;
            while ((i - x) >= 0 && s[i + x + 1] != '\0' && s[i - x] == s[i + x + 1])
                x++;
            
            len = x * 2;
            if (len > maxLength) {
				maxLength = len;
				start = i - x + 1;
			}
        }      

		if (start != -1)
			return s.substr(start, maxLength);

		return "";		// no match - only in case of empty string
    }
};