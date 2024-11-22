// 3016. Minimum Number of Pushes to Type Word II
// https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/description/


class Solution {
public:
    int minimumPushes(string word) {
  		
  		unordered_set<char> c;
  		for (int i = 0 ; word[i] != '\0' ; i++) {
  			c.insert(word[i]);
  		}

  		int presses = 1;
  		int uniqueChars = c.size();
  		while (uniqueChars >= 8) {

  			
  		}
    }
};