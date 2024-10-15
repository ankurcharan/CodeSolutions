// 211. Design Add and Search Words Data Structure
// https://leetcode.com/problems/design-add-and-search-words-data-structure/description/

class TrieNode {
public:
	unordered_map<char, TrieNode*> child;
	bool isTerminal;

	TrieNode() {
		isTerminal = false;
	}
};

class WordDictionary {
	TrieNode* root;

	bool recursiveSearch(TrieNode* root, string search, int i) {

		if (i > search.size())	
			return false;

		if (i == search.size())
            return root -> isTerminal;
			

		char x = search[i];

		if (x != '.')
		{
			if (root -> child.find(x) == root -> child.end())
                return false;		// not available
				
			return recursiveSearch(root -> child[x], search, i + 1);
		}
		else {

			for (auto it: root -> child) {
				if (recursiveSearch(it.second, search, i + 1))
					return true;	// got the item
			}
			
			return false;		// not found
		}
	}

public:
    WordDictionary() {
    	root = new TrieNode();      
    }
    
    void addWord(string word) {
        
        TrieNode* curr = root;
        for (char x: word) {

        	if (curr -> child.find(x) == curr -> child.end())
        		curr -> child[x] = new TrieNode();

            curr = curr -> child[x];
        }

        curr -> isTerminal = true;
    }
    
    bool search(string word) {
        
    	return recursiveSearch(root, word, 0);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */