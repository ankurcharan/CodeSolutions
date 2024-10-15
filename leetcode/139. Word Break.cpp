// 139. Word Break
// https://leetcode.com/problems/word-break/



class TrieNode {
public:
    bool isWord;
    unordered_map<char, TrieNode*> child;
    TrieNode() {
        isWord = false;
    }
};


class Solution {
public:
    bool bfs(string s, vector<string>& wordDict) {

        // init dict
        unordered_set<string> dict(wordDict.begin(), wordDict.end());

        // if index if visited or not
        vector<bool> seen(s.size(), false);

        // bfs queue
        queue<int> q;
        q.push(0);
        seen[0] = true;

        while (!q.empty()) {

            int startIndex = q.front();
            q.pop();

            if (startIndex == s.size())     // reached end
                return true;

            for (int end = startIndex + 1 ; end <= s.size() ; end++) {

                if (seen[end])      // index already visited
                    continue;

                string newWordSubstring = s.substr(startIndex, end - startIndex);
                if (dict.find(newWordSubstring) != dict.end()) {
                    seen[end] = true;
                    q.push(end);
                }
            }
        }

        return false;   // no path
    }

    bool dp(int i, string& s, vector<string>& dict, vector<int>& memo) {

        // true of all empty strings
        if (i < 0) {
            // cout << "i:  " << i << "\n";
            return true;        // you have reached the end
        }  

        if (memo[i] != -1)
            return memo[i];

        for (string word: dict) {

            int currSize = word.size();

            // cout << i << " -> " << word  << " - " << currSize << "\n";

            if (i - currSize + 1 < 0)
                continue;       // longer word

            // exact length word

            // get substring if it matches with the word
            if (s.substr(i - currSize + 1, currSize) == word && dp(i - currSize, s, dict, memo)) {
                memo[i] = 1;
                return true;
            }
        }

        memo[i] = 0;        // false
        return false;
    }

    bool topDownDP(string s, vector<string>& wordDict) {

        vector<int> memo(s.size(), -1);

        return dp(s.size() - 1, s, wordDict, memo);
    }

    bool bottomUpDP(string s, vector<string>& dict) {

        vector<bool> dp(s.size(), false);

        for (int i = 0 ; i < s.size() ; i++) {

            for (string word: dict) {

                // out of bound case
                if (i < word.length() - 1) {
                    continue;
                }

                if (i == word.length() - 1 || dp[i - word.length()]) {

                    if (s.substr(i - word.length() + 1, word.length()) == word) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }

        return dp[s.size() - 1];
    }

    bool trie(string s, vector<string>& dict) {

        TrieNode* root = new TrieNode();

        // all dict to trie
        for (string word: dict) {

            TrieNode* curr = root;
            for (char c: word) {

                if (curr -> child.find(c) == curr -> child.end())
                    curr -> child[c] = new TrieNode();

                curr = curr -> child[c];
            }

            // mark as word
            curr -> isWord = true;
        }


        // same dp
        vector<bool> dp(s.size(), false);

        for (int i = 0 ; i < s.size() ; i++) {

            // if starting or previous word is reached
            if (i == 0 || dp[i - 1]) {

                TrieNode* curr = root;
                // traverse trie
                for (int j = i ; j < s.size() ; j++) {

                    char c = s[j];

                    // no word found
                    if (curr -> child.find(c) == curr -> child.end())
                        break;

                    curr = curr -> child[c];

                    if (curr -> isWord) {
                        dp[j] = true;
                    }
                }
            }
        }

        return dp[s.size() - 1];
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        
        // return bfs(s, wordDict);        // O (n^3 + mk)
    
        // return topDownDP(s, wordDict);

        // return bottomUpDP(s, wordDict);

        return trie(s, wordDict);
    }
};