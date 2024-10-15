// 49. Group Anagrams
// https://leetcode.com/problems/group-anagrams/description/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& a) {

    	map<map<char, int>, vector<string>> groupedAnagrams;

    	int n = a.size();

    	for (int i = 0 ; i < n ; i++)
    	{
    		map<char, int> m;
    		for (int j = 0 ; a[i][j] != '\0' ; j++)
    		{
    			m[a[i][j]]++;
    		}

    		groupedAnagrams[m].push_back(a[i]);
    		m.clear();
    	}

    	vector<vector<string>> ans;
    	for (auto it: groupedAnagrams) {
    		ans.push_back(it.second);
    	}

    	return ans;
    }
};