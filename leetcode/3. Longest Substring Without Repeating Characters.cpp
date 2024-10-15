// 3. Longest Substring Without Repeating Characters
// https://leetcode.com/problems/longest-substring-without-repeating-characters/description/

class Solution {
public:
	int withSet(string a) {

		unordered_set<char> s;

		int ans = 0;
		int start = 0;
		for (int i = 0 ; a[i] != '\0' ; i++) {

			// start removing from start
			if (s.find(a[i]) != s.end()) {

				while (s.find(a[i]) != s.end())
					s.erase(a[start++]);
			}

            s.insert(a[i]);
			ans = max(ans, i - start + 1);
		}      

		return ans;
	}

	int withMap(string a) {

        if (a[0] == '\0')
            return 0;

		unordered_map<char, int> m;

		int ans = 1;
		int start = 0;

		for (int i = 0 ; a[i] != '\0' ; i++) {

			if (m.find(a[i]) != m.end())
				start = max(start, m[a[i]] + 1);

			m[a[i]] = i;

			ans = max(ans, i - start + 1);
		}

		return ans;
	}



    int lengthOfLongestSubstring(string s) {
 
		// return withSet(s);

		return withMap(s);
    }
};