// 2407. Longest Increasing Subsequence II
// https://leetcode.com/problems/longest-increasing-subsequence-ii/description/

class Solution {
public:
    void print(vector<int>& a) {

        int n = a.size();
        cout << "seg: ";
        for (int i = 0 ; i < n ; i++) {
            cout << setw(2) << a[i] << " ";
        }
        cout << "\n";
    }

    int bruteforce(vector<int>& a, int k) {

        int m = *max_element(a.begin(), a.end());

        // cout << "max: " << m << endl;

        vector<int> seg(m + 2, 0);

        // cout << "idx: ";
        // for (int i = 0 ; i < m + 1 ; i++) {
        //     cout << setw(2) << i << " ";
        // }
        // cout << "\n";

        int ans = 0;
        for (int i = 0 ; i < a.size() ; i++) {

            int l = max(0, a[i] - k);
            int r = a[i];

            // cout << l << ", " << r << "\n";

            int res = 0;
            for (int j = l ; j < r ; j++) {
                res = max(res, seg[j]);
            }

            seg[a[i]] = max(seg[a[i]], res + 1);
            ans = max(ans, seg[a[i]]);

            // print(seg);


            // if (seg.size() > 100000) {

            //     vector<int> idx = { 1, 100, 500, 100000, 100000 };
            //     cout << seg.size() << " = seg size\n";
            //     for (int xx: idx) {
            //         // cout << xx << " ";
            //         cout << setw(2) << seg[xx] << " ";
            //     }
            //     cout << "\n";
            // }
        }

        return ans;
    }

    int query(int i, int ql, int qr, int l, int r, vector<int>& tree) {

        
        if (l > qr || r < ql) {
            cout << "out of range: ";
            cout << "i: " << i << ", l: " << l << ", r: " << setw(2) << r << "\n";
            return INT_MIN;
        }

        if (l >= ql && r <= qr) {

            cout << "i: " << i << ", l: " << l << ", r: " << setw(2) << r << ", ql: " << ql << ", qr: " << qr;
            cout << ", ret: " << i << endl;
            return tree[i];
            // return 1;
        }

        cout << "l: " << l << ", r: " << setw(2) << r << ", ql: " << ql << ", qr: " << qr << " == " << i << " = " << (2 * i + 1) << ", " << (2 * i + 2) << "\n";

        int mid = (l + r) / 2;

        int left =  query(2 * i + 1, ql, qr, l, mid, tree);
        int right = query(2 * i + 2, ql, qr, mid + 1, r, tree);

        return max(left, right);
    }

    void update(int i, int l, int r, int pos, int val, vector<int>& tree) {

        // out of range
        if (pos < l || pos > r)
            return;

        if (l == r) {
            tree[i] = max(tree[i], val);
            return;
        }

        int mid = (l + r) / 2;
        update(2 * i + 1, l, mid, pos, val, tree);
        update(2 * i + 2, mid + 1, r, pos, val, tree);

        tree[i] = max(tree[2 * i + 1], tree[2* i + 2]);
    }

    int segmentTree(vector<int>& a, int k) {

        int n = 1e5 + 1;
        int size = ceil(log2(n));
        size = (2 * pow(2, size)) - 1;

        n = *max_element(a.begin(), a.end()) + 1;
        size = 4 * (*max_element(a.begin(), a.end()) + 1) + 1;

        cout << size << " =size\n";

        vector<int> tree(size, 0);

        int ans = 0;

        for (int x: a) {

            int l = max(0, x - k);
            int r = x - 1;

            int current = query(0, l, r, 0, n, tree) + 1;

            update(0, 0, n - 1, x, current, tree);

            ans = max(ans, current);
        }

        return ans;
    }

    int lengthOfLIS(vector<int>& nums, int k) {

        // bruteforce TLE
        // return bruteforce(nums, k);

        return segmentTree(nums, k);
    }
};

/**



const int N = 1e5 + 1;

class Solution {
public:
    array<int, 2*N> seg{};

    void print() {

        for (int i = 0 ; i < 10 ; i++) {
            cout << setw(2) << seg[i] << " ";
        }
        cout << endl;
    }

    void update(int pos, int val) {

        pos += N;
        seg[pos] = val;

        cout << "before: ";
        print();

        while (pos > 1) {

            pos >>= 1;
            seg[pos] = max(seg[2 * pos], seg[2 * pos + 1]);
        }

        cout << "after:  ";
        print();
    }

    // query max [lo, hi]
    int query(int lo, int hi) {

        lo += N;
        hi += N;

        int res = 0;

        while (lo < hi) {

            if (lo & 1) {
                res = max(res, seg[lo++]);
            }
            if (hi & 1) {
                res = max(res, seg[--hi]);
            }

            lo >>= 1;
            hi >>= 1;
        }

        return res;
    }


    int lengthOfLIS(vector<int>& a, int k) {
        
        cout << "index:  ";
        for (int i = 0 ; i < 10 ; i++) {
            cout << setw(2) << i << " ";
        }
        cout << endl;

        int n = a.size();
        int ans = 0;

        for (int i = 0 ; i < n ; i++) {

            int l = max(0, a[i] - k);
            int r = a[i];

            cout << i << ", a[i]: " << a[i] << ", l: " << l << ", r: " << r << endl;

            // best result for current element
            int result = query(l, r) + 1;

            ans = max(result, ans);

            // update result
            update(a[i], result);
        }

        return ans;
    }
};



*/