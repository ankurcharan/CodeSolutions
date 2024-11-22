// https://leetcode.com/problems/longest-increasing-subsequence-ii/description/


#include <bits/stdc++.h>
using namespace std;

int query(vector<int>& tree, int i, int l, int r, int ql, int qr) {

	if (l > qr || r < ql)
		return INT_MIN;

	if (l >= ql && r <= qr) {
		return tree[i];
	}

	int mid = (l + r) / 2;

	int left = query(tree, 2 * i + 1, l, mid, ql, qr);
	int right = query(tree, 2 * i + 2, mid + 1, r, ql, qr);

	return max(left, right);
}

void update(vector<int>& tree, int i, int pos, int val, int l, int r) {

	if (pos < l || pos > r)
		return;

	if (l == r) {
		tree[i] = max(tree[i], val);
		return;
	}

	int mid = (l + r) / 2;

	update(tree, 2 * i + 1, pos, val, l, mid);
	update(tree, 2 * i + 2, pos, val, mid + 1, r);

	tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
}

int segmentTree(vector<int> a, int k) {

	int m = *max_element(a.begin(), a.end());

	int size = 4 * m;

	// cout << "max: " << m << "\n";
	// cout << "size: " << size << "\n";

	vector<int> tree(size + 1, 0);

	int ans = 0;
	for (int x: a) {

		int l = x - k;
		int r = x - 1;

		int q = query(tree, 0, 0, m, l, r);

		q += 1;

		update(tree, 0, x, q, 0, m);

		ans = max(ans, q);
	}

	return ans;
}

int main() {

	vector<int> a1 = { 4,2,1,4,3,4,5,8,15 };
	int k1 = 3;

	int ans1 = segmentTree(a1, k1);	
	cout << "ans1 : " << ans1 << "\n";



	vector<int> a2 = { 7,4,5,1,8,12,4,7 };
	int k2 = 5;

	int ans2 = segmentTree(a2, k2);	
	cout << "ans2 : " << ans2 << "\n";



	vector<int> a3 = { 1,5 };
	int k3 = 1;

	int ans3 = segmentTree(a3, k3);	
	cout << "ans3 : " << ans3 << "\n";




	vector<int> a4 = { 1,100,500,100000,100000 };
	int k4 = 100000;

	int ans4 = segmentTree(a4, k4);	
	cout << "ans4 : " << ans4 << "\n";

	return 0;
}