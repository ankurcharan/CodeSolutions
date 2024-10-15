// 224. Basic Calculator
// https://leetcode.com/problems/basic-calculator/description/

class Solution {
public:
    int calculate(string s) {
  	
  		stack<int> st;

  		int ans = 0;
  		int sign = 1;	// positive

  		for (int i = 0 ; s[i] != '\0' ; i++) {

  			if (isdigit(s[i])) {

  				long long int x = 0;
  				int j = i;
  				while (s[j] != '\0' && isdigit(s[j])) {
  					x = x * 10 + (s[j] - '0');
  					j++;
  				}

  				ans += (sign * x);
  				i = j - 1;		// i will get incremented and start from where s[j] != digit
  			}
  			else if (s[i] == '+')
  				sign = 1;
  			else if (s[i] == '-')
  				sign = -1;			// negative number
  			else if (s[i] == '(') {

  				st.push(ans);		// push number
  				st.push(sign);		// push sign
  				ans = 0;
  				sign = 1;		// back to positive number
  			}
  			else if (s[i] == ')') {

  				// get the answer in the bracket
  				int popped_sign = st.top();		st.pop();
                ans *= popped_sign;
  				int popped_ans  = st.top();		st.pop();
                ans += popped_ans;
  			}
  		}      

  		return ans;
    }
};