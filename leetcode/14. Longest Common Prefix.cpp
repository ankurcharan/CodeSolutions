// 14. Longest Common Prefix
// https://leetcode.com/problems/longest-common-prefix/description/

class Solution {
public:
    string longestCommonPrefix(vector<string>& a) {
  		
  		int n = a.size();
  		if (n == 0 || a[0][0] == '\0')
  			return "";			// no string prefix


  		string ans = "";
  		for (int i = 0 ; a[0][i] != '\0' ; i++)
  		{
  			int currChar = a[0][i];
  			bool found = false;

			bool notMatch = false;
  			for (int j = 0 ; j < n ; j++)
  			{
  				if (a[j][i] == '\0' || a[j][i] != currChar)
  				{
  					notMatch = true;
  				}
  			}

  			if (!notMatch)
  				ans += currChar;
  			else
  				break;
  		}

  		return ans;
    }
};