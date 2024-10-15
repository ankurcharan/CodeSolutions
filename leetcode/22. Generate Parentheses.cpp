// 22. Generate Parentheses
// https://leetcode.com/problems/generate-parentheses/description/

class Solution {
public:
    void dfs(int n, int open, int close, string& series, vector<string> &ans) {

    	if (open == n && close == n) {
    		ans.push_back(series);
    		return;
    	}

    	if (open < n) {

    		series.push_back('(');
    		dfs(n, open + 1, close, series, ans);
    		series.pop_back();
    	}

    	if (open > close) {
    		series.push_back(')');
    		dfs(n, open, close + 1, series, ans);
    		series.pop_back();
    	}
    }
    

    vector<string> generateParenthesis(int n) {
        
        vector<string> parenthesis;
        string series = "";

        dfs(n, 0, 0, series, parenthesis);

        return parenthesis;
    }
};