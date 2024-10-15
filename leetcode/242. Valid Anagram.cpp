// 242. Valid Anagram
// https://leetcode.com/problems/valid-anagram/description/

class Solution {
public:
    bool isAnagram(string s, string t) {

    	unordered_map<char, int> m;

    	for (int i = 0 ; s[i] != '\0' ; i++)
    		m[s[i]]++;

    	for (int i = 0 ; t[i] != '\0' ; i++) {

    		if (m.find(t[i]) == m.end())
    			return false;

    		m[t[i]]--;

    		if (m[t[i]] == 0)
    			m.erase(t[i]);
    	}      

    	return true;
    }
};