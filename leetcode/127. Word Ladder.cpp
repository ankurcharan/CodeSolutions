// 127. Word Ladder
// https://leetcode.com/problems/word-ladder/description/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        
        // (word, distance)
        queue<pair<string, int>> q;
    	unordered_set<string> visit;

    	// create dict
    	// wordList.erase(beginWord);
    	unordered_set<string> dict;
    	for (int i = 0 ; i < wordList.size() ; i++) {
    		dict.insert(wordList[i]);
    	}

    	// 1 cause shortest transformation = [beginWord]
    	q.push({ beginWord, 1 });

    	while (!q.empty()) {

    		pair<string, int> f = q.front();
    		q.pop();

    		if (f.first.compare(endWord) == 0)
    			return f.second;

    		string word = f.first;
    		int wordLength = word.length();

    		for (int i = 0 ; i < wordLength ; i++) {

                char original = word[i];

    			for (int j = 'a' ; j <= 'z' ; j++) {
    				word[i] = j;		// one char changed

    				if (dict.find(word) != dict.end()) {

    					dict.erase(word);
    					q.push({ word, f.second + 1 });
    				}
    			}

                word[i] = original;
    		}
    	}

    	return 0;		// no transformation possible
    }
};