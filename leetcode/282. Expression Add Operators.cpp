// 282. Expression Add Operators
// https://leetcode.com/problems/expression-add-operators/description/

class Solution {
public:

	void recurse(int index, long long prev, long long curr, long long value, 
		string& s, int& target, vector<string>& ops, vector<string>& expressions) {

		// all digits processed
		if (index == s.length()) {


			if (value == target && curr == 0) {

				string expr = "";
                // ignore first value, that would be "+"
				for (int i = 1 ; i < ops.size() ; i++)
                    expr += ops[i];
				expressions.push_back(expr);

                cout << "expression: " << expr << " : " << value << "\n";
			}

			return;
		}

		// extend curr operand by one digit
		curr = curr * 10 + s[index] - '0';

		string currValueString = to_string(curr);


		// to avoid cases like
		// 1 + 05  OR 1 * 05
		// 05 won't be a valid operand
		if (curr > 0) {

			// no op recursion
			recurse(index + 1, prev, curr, value, s, target, ops, expressions);
		} else {
            // cout << "curr is less than or = to zero \n";
            // cout << s.substr(0, index + 1) << "\n";
            // cout << "prev: " <<  prev << " , curr: " << currValueString << "\n";
        }

		// addition | +
		ops.push_back("+");
		ops.push_back(currValueString);
		recurse(index + 1, curr, 0, value + curr, s, target, ops, expressions);
		ops.pop_back();
		ops.pop_back();

		// can't multiply or substract from empty ops
		// i.e. first operand will be positive value only
		if (ops.size() > 0) {

			// subtraction | -
			ops.push_back("-");
			ops.push_back(currValueString);
			recurse(index + 1, -1 * curr, 0, value - curr, s, target, ops, expressions);
			ops.pop_back();
			ops.pop_back();


			// multiplication | *
			ops.push_back("*");
			ops.push_back(currValueString);
			recurse(index + 1, curr * prev, 0, value - prev + (curr * prev), s, target, ops, expressions);
			ops.pop_back();
			ops.pop_back();
		}
	}

    vector<string> addOperators(string num, int target) {
        
        if (num.length() == 0)
        	return {};

        vector<string> ops;
        vector<string> expressions;
        recurse(0, 0, 0, 0, num, target, ops, expressions);

        return expressions;
    }
};