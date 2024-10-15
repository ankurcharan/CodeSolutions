// 20. Valid Parentheses
// https://leetcode.com/problems/valid-parentheses/description/


class Solution {
public:
	bool stackSoln(string a) {

		stack<char> s;

		for (char x: a) {

			if (x == '(' || x == '{' || x == '[') {
				s.push(x);
			}
			else if (s.empty()) {
				return false;		// bracket not matched - no open bracket
			}
			else if ((x == ')' && s.top() == '(') || (x == '}' && s.top() == '{') || (x == ']' && s.top() == '[')) {
				s.pop();
			}
			else {
				return false;		// top bracket not matched
			}
		}

		return s.size() == 0;
	}

	bool withoutStack(string s) {

		int i = -1;
		for (char x: s) {

			if (x == '(' || x == '{' || x == '[')
				s[++i] = x;
			else if (i >= 0 && ((s[i] == '(' && x == ')') || (s[i] == '{' && x == '}') || (s[i] == '[' && x == ']')))
				i--;
			else
				return false;		// empty stack or bracket not matched
		}

		return i == -1;		// empty stack
	}

    bool isValid(string s) {
        
        // return stackSoln(s);

        return withoutStack(s);
    }
};