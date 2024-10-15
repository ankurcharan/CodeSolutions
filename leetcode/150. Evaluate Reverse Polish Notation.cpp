// 150. Evaluate Reverse Polish Notation
// https://leetcode.com/problems/evaluate-reverse-polish-notation/description/

class Solution {
public:
	bool isOp(string a) {
		return a == "+" || a == "-" || a == "*" || a == "/";
	}

	int stackAns(vector<string>& tokens) {

		stack<int> s;

		int n = tokens.size();

		for (int i = 0 ; i < n ; i++) {

			if (isOp(tokens[i])) {

				int b = s.top();
				s.pop();

				int a = s.top();
				s.pop();

				if (tokens[i] == "+")
					s.push(a + b);
				else if (tokens[i] == "-")
					s.push(a - b);
				else if (tokens[i] == "*")
					s.push(a * b);
				else if (tokens[i] == "/")
					s.push(a / b);		// divide by zero won't be given
			}
			else {
				s.push(stoi(tokens[i]));
			}
		}

		return s.top();
	}

	int spaceOptimzed(vector<string> tokens) {

		int n = tokens.size();
		int i = 0;
		int lastNum = -1;	// last number seen

		for (int i = 0 ; i < n ; i++) {

			if (isOp(tokens[i])) {

				int a = stoi(tokens[lastNum - 1]);
				int b = stoi(tokens[lastNum]);

				if (tokens[i] == "+") {
					tokens[lastNum - 1] = to_string(a + b);
				}
				else if (tokens[i] == "-") {
					tokens[lastNum - 1] = to_string(a - b);
				}
				else if (tokens[i] == "*") {
					tokens[lastNum - 1] = to_string(a * b);
				}
				else if (tokens[i] == "/") {
					tokens[lastNum - 1] = to_string(a / b);
				}

				lastNum--;
			}
			else {
				tokens[++lastNum] = tokens[i];
			}
		}

		return stoi(tokens[lastNum]);
	}

    int evalRPN(vector<string>& tokens) {
        
        // return stackAns(tokens);

        return spaceOptimzed(tokens);		// without stack
    }
};