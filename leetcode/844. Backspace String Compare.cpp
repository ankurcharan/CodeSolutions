// 844. Backspace String Compare
// https://leetcode.com/problems/backspace-string-compare/description/

class Solution {
public:
    bool backspaceCompare(string s, string t) {
  		
  		int sn = s.size() - 1;
  		int tn = t.size() - 1;

  		int sSkip = 0;
  		int tSkip = 0;

  		while (sn >= 0 || tn >= 0) {

  			while (sn >= 0) {

  				if (s[sn] == '#')
  					sSkip++;
  				else if (sSkip > 0)
  					sSkip--;
  				else
  					break;
                
                sn--;
  			}

  			while (tn >= 0) {

  				if (t[tn] == '#')
  					tSkip++;
  				else if (tSkip > 0)
  					tSkip--;
  				else
  					break;
  			
                tn--;
            }

  			if (sn >= 0 && tn >= 0 && s[sn] != t[tn]) {
                return false;		// different chars
            }
  		
  			if ((sn >= 0) != (tn >= 0)) {
                return false;		// one string ended, other not
            }
  				

  			sn--;
  			tn--;
  		}     

  		return true;            // all matched
    }
};