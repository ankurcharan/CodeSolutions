// 692. Top K Frequent Words
// https://leetcode.com/problems/top-k-frequent-words/

class cmp {
public:
    bool operator()(pair<int, string>& a, pair<int, string>& b) {

        if (a.first == b.first) {
            return a.second.compare(b.second) > 0;
        }
        return a.first < b.first;
    }
};

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {

        unordered_map<string, int> m;
        int n = words.size();

        for (int i = 0 ; i < n ; i++)
            m[words[i]]++;

        priority_queue<pair<int, string>, vector<pair<int, string>>, cmp> pq;

        for (auto it: m) {
            // cout << it.second << " - " << it.first << "\n";
            pq.push({ it.second, it.first });
        }

        vector<string> ans;

        while (k > 0 && !pq.empty()) {
            ans.push_back(pq.top().second);
            pq.pop();
            k--;
        }

        return ans;
    }
};