// 383. Ransom Note
// https://leetcode.com/problems/ransom-note/description/

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        
        unordered_map<char, int> m;

        for (int i = 0 ; magazine[i] != '\0' ; i++) {
        	m[magazine[i]]++;
        }

        for (int i = 0 ; ransomNote[i] != '\0' ; i++) {
        	m[ransomNote[i]]--;

        	if (m[ransomNote[i]] < 0)
        		return false;		// in-sufficient chars
        }

        return true;		// all chars found
    }
};