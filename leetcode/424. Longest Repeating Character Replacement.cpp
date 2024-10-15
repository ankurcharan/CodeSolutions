// 424. Longest Repeating Character Replacement
// https://leetcode.com/problems/longest-repeating-character-replacement/description/

class Solution {
public:
	int findMaxLengthAfterReplacement(string &s, int n, int k, char x) {

		int l = 0;
		int r = 0;

		int differentCharsInWindow = 0;
		int maxLength = 0;

		while (r < n) {

			if (s[r] != x)
				differentCharsInWindow++;

			while (differentCharsInWindow > k)
			{
				if (s[l] != x)
					differentCharsInWindow--;
				l++;
			}

			maxLength = max(maxLength, r - l + 1);
			r++;
		}

		return maxLength;
	}


    int characterReplacement(string s, int k) {
		
		int n = s.length();
		if (k >= n)
			return n;

		int maxLength = 0;
		for (int i = 0 ; i < 26 ; i++) {

			maxLength = max(maxLength, findMaxLengthAfterReplacement(s, n, k, i + 'A'));
		}      

		return maxLength;
    }
};