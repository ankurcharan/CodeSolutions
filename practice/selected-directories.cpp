// https://leetcode.com/discuss/interview-question/5039879/Google-Onsite-Interview

/*

I recently had a google interview, and I was asked the below question, let me know if you get it.

Basically I needed to implement cli.

I was given (as strings) as directories e.g.
/a/b/x.txt
/a/b/p.txt
/a/c
/a/d/y.txt
/a/d/z.txt

Also, I was given the selected directories e.g.
/a/d/y.txt
/a/d/z.txt
/a/b/p.txt

My output should be
/a/d
/a/b/p.txt

/a/d
is the answer because it has 2 txt files (y and z), and both are selected.
/a/b/p.txt
is the answer because another file in the directory i.e. /a/b/x.txt is not selected, if it was selected, answer would have been /a/b

Basically, if all items are selected in a particular directory, we need to return the just prev directory.

I tried solving it, assuming the directories to be a tree, and used dfs. I messed up really bad.
How can we solve this problem? If possible, can someone code it up?

*/


#include<bits/stdc++.h>
using namespace std;

vector<string> getTokens(string s) {

    stringstream ss(s);
    string token;
    vector<string> tokens;

    while(getline(ss, token, '/')) {
        tokens.push_back(token);
    }

    return tokens;
}

class TrieNode {
public:
    string name;
    bool selected;
    int childCount;
    unordered_map<string, TrieNode*> child;

    TrieNode(string name) {
        this -> selected = false;
        this -> name = name;
        childCount = 0;
    }
};

void insertIntoTrie(TrieNode* root, vector<string>& tokens, int i) {
    
    // cout << root -> name << "(" << root-> childCount << ")" " -- ";
    
    if (i == tokens.size()) {

        // here root node is the last node of the path. 
        // so you return from here
        
        // cout << "\n";
        return;
    }
    
    // keep track of the immediate child of the node
    if (root -> child.find(tokens[i]) == root -> child.end()) {
        root -> child[tokens[i]] = new TrieNode(tokens[i]);
        root -> childCount++;
    }
        
    // add into trie
    insertIntoTrie(root -> child[tokens[i]], tokens, i + 1);
}

bool searchTrie(TrieNode* root, vector<string>& tokens, int i) {
    
    // cout << "searchTrie: " << root -> name <<" -- " << root -> childCount << "\n";
    if (i == tokens.size()) {
    
        // mark the current node as selected and return true
        // so the parent can reduce the count of unselected nodes in its tree
        
        // cout << "searchTrie:revert: " << root -> name <<" -- " << root -> childCount << "\n";
        root -> selected = true;
        return true;
    }
    
    // if path is not available, then you don't have to select
    // and reduce from the parent node
    if (root -> child.find(tokens[i]) == root -> child.end())
        return false;
    
    // traverse path
    bool f = searchTrie(root -> child[tokens[i]], tokens, i + 1);
    
    // if the child returns true
    // it means child node was marked as selected
    // so reduce the count of unselected node
    if (f) {
        root -> childCount--;
    }
    
    // cout << "searchTrie:revert: " << root -> name <<" -- " << root -> childCount << "\n";
    
    // if unselected node becomes zero 
    // then mark the current node as selected and return true, for the parent
    // to proceed as needed
    // other false. 
    if (root -> childCount == 0) {
        root -> selected = true;
        return true;
    }
    else 
        return false;
    
}


void getSelectedNodes(TrieNode* root, vector<string>& path, vector<string>& selectedPaths) {

    
    // if current node is selected, add path to ans
    // and no need to proceed further to the 
    if (root -> selected) {
    
        // from the nodes in path, generate the path to current node's children
        string generatedPath = "";
        for (string x: path) {
            cout << x << " ";
            generatedPath += "/" + x;
        }
        // add path to curr node
        selectedPaths.push_back(generatedPath);
            
        // return. no need to proceed further
        return;
    }
    
    for (auto it: root -> child) {

        // add node to the path
        path.push_back(it.first);
        
        // traverse entire trie
        getSelectedNodes(it.second, path, selectedPaths);
        
        // backtrack
        path.pop_back();
    }
}


vector<string> getSelected(vector<string>& dirs, vector<string>& selected) {

    TrieNode* root = new TrieNode("//");
    
    // insert the directories in trie
    for (int i = 0 ; i < dirs.size() ; i++) {
        
        vector<string> tokens = getTokens(dirs[i]);

        // // printing the tokens generated
        // cout << "tokens size: " << tokens.size() << ": ";
        // for (string x: tokens) {
        // cout << x << " ";
        // }
        // cout << "\n";
        
        // pass index as 1 because dir = "/a/b/c" 
        // so the tokens come out as "", "a", "b", "c"
        // the first token is always empty. so you start from the second token
        insertIntoTrie(root, tokens, 1);
    }
        
    // mark the nodes selected
    for (int i = 0 ; i < selected.size() ; i++) {
        
        cout << "selecting: " << selected[i] << "\n";
        vector<string> tokens = getTokens(selected[i]);
        
        // search and mark node. start from one for same reason.
        searchTrie(root, tokens, 1);
        cout << "\n";
    }
    
    // getting selected paths
    vector<string> path;            // curr node of the path
    vector<string> selectedPaths;   // string of all selected paths
    getSelectedNodes(root, path, selectedPaths);
    
    cout << "selectedPaths size: " << selectedPaths.size() << "\n";
    
    // if selected path size if 1 and the first node is empty which is the root node
    // that means all paths are selected from the root node "/"
    if (selectedPaths.size() == 1 && selectedPaths[0].empty())
        cout << "/";
    else 
        for (int i = 0 ; i < selectedPaths.size() ; i++) 
            cout << selectedPaths[i] << " \n";
    cout << "\n";

    return {};
}

int main() {

    vector<string> directories  = { "/a/b/x.txt", "/a/b/p.txt", "/a/c", "/a/d/y.txt", "/a/d/z.txt", "/b/x" };
    vector<string> selected     = { "/a/d/y.txt", "/a/d/z.txt", "/a/b", "/a/c", "/b" };

    vector<string> selectedShorts = getSelected(directories, selected);
    
    return 0;
}