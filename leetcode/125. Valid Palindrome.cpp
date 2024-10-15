// 125. Valid Palindrome
// https://leetcode.com/problems/valid-palindrome/

bool ignoreThis(char x)
{
	if((x >= 'A' && x <= 'Z') || (x >= '0' && x <= '9') || (x >= 'a' && x <= 'z'))
		return false;
	return true;
}
bool equalIgnoreCase(char x, char y)
{
	if(x == y)	return true;
    
    if(x >= 'A' && x <='Z') 
        x = x + 32;
    if(y >= 'A' && y <= 'Z')
        y = y + 32;
    if(x == y)  return true;
	return false;
}

class Solution {
public:
    bool isPalindrome(string s) 
    {
    	
    	int i = 0;
    	int j = s.length() - 1;

    	while(i <= j)
    	{   
    		if(ignoreThis(s[i]))
    			i++;
    		else if(ignoreThis(s[j]))
    			j--;
    		else if(equalIgnoreCase(s[i], s[j]))
    			i++, j--;
    		else
    			return false;
    	}

    	return true;
    }
};