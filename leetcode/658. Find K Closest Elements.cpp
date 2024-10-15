// 658. Find K Closest Elements
// https://leetcode.com/problems/find-k-closest-elements/description/



int pole = -1;

class cmp {
public:
    bool operator()(int a, int b) {

        if (abs(a - pole) == abs(b - pole)) {
            return a > b;       // a should be smaller if diff is same
        }

        return abs(a - pole) > abs(b - pole);       // smaller diff comes first
    }
};


class Solution {
public:
    vector<int> findClosestElements(vector<int>& a, int k, int x) {
        
        pole = x;
        int n = a.size();
        priority_queue<int, vector<int>, cmp> p;
        
        for (int i = 0 ; i < n ; i++) {
            p.push(a[i]);
        }

        // while (!p.empty()) {
        //     cout << p.top() << " ";
        //     p.pop();
        // }
        // cout << "\n";

        vector<int> ans;
        while (k-- && p.empty() == false) {
            ans.push_back(p.top());
            p.pop();
        }

        sort(ans.begin(), ans.end());

        return ans;
    }
};