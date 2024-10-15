// 1684. Count the Number of Consistent Strings
// https://leetcode.com/problems/count-the-number-of-consistent-strings/description

class Solution {
public:
    int hashset(string allowed, vector<string>& words) {

    	unordered_set<char> s;

  		for (int i = 0 ; allowed[i] != '\0' ; i++)
  			s.insert(allowed[i]);

  		int n = words.size();
  		int ans = n;
  		for (int i = 0 ; i < n ; i++) {

  			for (int j = 0 ; words[i][j] != '\0' ; j++) {

  				if (s.find(words[i][j]) == s.end()) {
  					ans--;
  					break;
  				}
  			}
  		}

  		return ans;
    }
    

    int bitManipulation(string allowed, vector<string>& words) {

    	// 26 chars - so can use 32-bit int to find the set bits = allowed chars
    	int allowedBits = 0;

    	for (int i = 0 ; allowed[i] != '\0' ; i++)
    		allowedBits = allowedBits | (1 << (allowed[i] - 'a'));

        int n = words.size();       // no of string
    	int consistentCount = n;    // all assumed consistent

    	for (int i = 0 ; i < n ; i++) {

    		for (int j = 0 ; words[i][j] != '\0' ; j++) {

    			// if set or not
    			int bit = (allowedBits >> (words[i][j] - 'a')) & 1;

    			// not allowed
    			if (bit == 0) {
    				consistentCount--;
    				break;
    			}
    		}
    	}

    	return consistentCount;
    }


    int countConsistentStrings(string allowed, vector<string>& words) {
  		
  		// return hashset(allowed, words);

  		return bitManipulation(allowed, words);
    }
};