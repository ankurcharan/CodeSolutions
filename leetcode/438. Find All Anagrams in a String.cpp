// 438. Find All Anagrams in a String
// https://leetcode.com/problems/find-all-anagrams-in-a-string/description/

class Solution {
public:
	bool equalHashmaps(unordered_map<char, int>& sm, unordered_map<char, int>& pm) {

		for (int i = 97 ; i < 123 ; i++) {

            if (sm[i] != pm[i])
                return false;
        }
			
		return true;
	}

    vector<int> findAnagrams(string s, string p) {

		int pn = p.size();
		int sn = s.size();

		if (sn < pn)
			return {};		// not possible

		vector<int> ans;
		unordered_map<char, int> sm;
		unordered_map<char, int> pm;
		
		for (int i = 0 ; i < pn ; i++)
			pm[p[i]]++;

		for (int i = 0 ; i < pn ; i++)
			sm[s[i]]++;

		if (equalHashmaps(sm, pm))
			ans.push_back(0);

		for (int i = pn ; i < sn ; i++) {

			sm[s[i]]++;
			sm[s[i - pn]]--;

			if (equalHashmaps(sm, pm))
				ans.push_back(i - pn + 1);
		}

		return ans;
    }
};



/*

// 438. Find All Anagrams in a String
// https://leetcode.com/problems/find-all-anagrams-in-a-string/

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        
        map<char, int> m;

        int n = s.size();

        int count = p.size();

        vector<int> ans;

        for(int i = 0 ; i < (int)p.size() ; i++)
        	m[p[i]]++;

        int l = 0;
        int r = 0;
        for(int r = 0 ; r < n ; r++)
        {
        	if(m.find(s[r]) != m.end() && m[s[r]])
        	{
        		m[s[r]]--;
        		count--;

        		if(count == 0)
        			ans.push_back(l);
        	}
        	else
        	{
        		while(l < r)
        		{
        			if(m.find(s[l]) != m.end())
        			{
        				count++;
        				m[s[l]]++;
        			}
        			l++;

        			if(m.find(s[r]) != m.end() && m[s[r]])
        			{
        				r--;                // will increase with for loop increment
        				break;
        			}
        		}

        		if(m.find(s[l]) == m.end())
        			l = r + 1;
        	}
        }

        return ans;
    }
};

*/