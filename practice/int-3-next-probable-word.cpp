// int-3-next-probable-word
// https://leetcode.com/discuss/interview-experience/5720580/Google-or-SDE(L3)-or-BangaloreHyd-or-Aug-24/


/**

Round 4- this was supposed to be a googliness round as per my understanding, but interviewer took a DSA round


R4- 
	given a vector<vector> sentences, 
	we have to find next most probable word for any given word .

	given sentences = { 
						{ 'i', 'am', 'awesome' },
						{'i', 'am', 'a', 'googler' }
					};
	
	so then func(i) should return 'am'
	
	I asked some questions regarding would it be guaranteed that the word would be 
	in the corpus and that it would have atleast one word next to it.

	was told YES


	made a unordered_map<pair<string,string>,int> pairCount to keep count of each pair in the sentences . 

	It was one -pass then did another pass to find max probable word for each 
	word by checking each pair in pairCount map.. 

	stored these results in another hashmap.


Runtime complexity- 
	O(n* len(word)), 
		n is the number of pairs of words-- 
		if total words are x then pairs would be x-1(including repeated ones as well)
	
	I told the interviewer that i would try to do it in one pass,, 
	was told this was perfect and was given next question.

*/


#include <bits/stdc++.h>
using namespace std;

bool cmp(pair<string, int>& a, pair<string, int>& b) {
    
    return a.second > b.second;
}

string nextProbableWord(vector<vector<string>>& sentences, string first) {

	unordered_map<string, unordered_map<string, int>> f;

	for (vector<string>& s: sentences) {

		int n = s.size();
		for (int i = 1 ; i < n ; i++) {

			f[s[i - 1]][s[i]] += 1;
		}
	}

    unordered_map<string, vector<pair<string, int>>> nprob;
    
	for (auto it: f) {

		cout << it.first << " => "; 
	    for (auto n: f[it.first]) {
            
            nprob[it.first].push_back({ n.first, n.second });
            sort(nprob[it.first].begin(), nprob[it.first].end(), cmp);
            
            if (nprob[it.first].size() > 2) {
                nprob[it.first].pop_back();
            }
            
            cout << "(" << n.first << ", " << n.second << ") ";
        }
        cout << endl;
    }
    
    cout << "\norganized:\n";
    for (auto it: nprob) {
        cout << it.first << "  => ";
        
        for (pair<string, int> f: it.second) {
            cout << "(" << f.first << ", " << f.second << ") ";
        }
        cout << endl;
    }
    
    if (nprob.find(first) == nprob.end())
        return "-1";
    
    vector<pair<string, int>> possibles = nprob[first];
    
    if (possibles[0].first.compare(first) != 0) 
        return possibles[0].first;
    else
        return possibles[1].first;

	return "ankur";
}

int main() {
	
	vector<vector<string>> sentences = { 
						{ "i", "am", "awesome" },
						{"i", "am", "a", "googler" },
                        { "i", "google", "blah", "am", "hey" },
                        { "i", "i", "i", "i", "i", "i", "i" }
					};

	string word = nextProbableWord(sentences, "i");
    cout << "next probable: i: " << word << endl;

	return 0;
}