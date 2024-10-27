

#include<bits/stdc++.h>
using namespace std;




int query(int l, int r, string& s) {

    for(int i = l ; i <= r ; i++)
        if(s[i] == '1')
            return 1;

    return 0;
}

vector<int> iterativeBinarySearch(string& s) {

	int n = s.size();
    if (query(0, n - 1, s) == 0) {
    	cout << "no set bits\n";
    	return {};
    }

    vector<int> indexes;
    

    int i = 0;
    while(i < n && query(i, n - 1, s) != 0) {

        int l = i;
        int r = n - 1;
        int ans = -1;

         while(l <= r) {

            int mid = (l + r) / 2;

            cout << "l: " <<  l << ", r: " << r << ", mid: " << mid << "\n";

            // bit present in left, move left
            if(query(l, mid, s) == 1) {
                ans = mid;
                r = mid - 1;
            }
            // move right
            else 
            	l = mid + 1;
        }

        // print bit position
        // cout << ans << " " << endl;
        indexes.push_back(ans);

        // se window to the next position
        i = ans + 1;
    }

    return indexes;
}


void recurse(string& s, int l, int r, vector<int>& indexes) {

	if (l == r) {

		if (query(l, r, s) == 1) {
			indexes.push_back(l);
		}
		return;
	} 

	if (l > r)
		return;

	int mid = (l + r) / 2;

	if (query(l, mid, s) == 1)
		recurse(s, l, mid, indexes);
	if (query(mid + 1, r, s) == 1)
		recurse(s, mid + 1, r, indexes);
}

vector<int> recursiveFindIndexes(string &s) {

	vector<int> indexes;
	recurse(s, 0, s.size() - 1, indexes);

	return indexes;
}

vector<int> stackRecursion(string &s) {

	int n = s.size();

	if (query(0, n - 1, s) == 0)
		return {};

	vector<int> indexes;

	stack<pair<int, int>> t;
	t.push({ 0, n - 1 });

    while (!t.empty()) {

		pair<int, int> f = t.top();
		t.pop();
        
        cout << f.first << ", " << f.second << "\n";

		if (f.first == f.second) {

			if (query(f.first, f.second, s) == 1) {
				indexes.push_back(f.first);
			}
			continue;
		}

		// if (query(f.first, f.second, s) == 0)
		// 	continue;

		int mid = (f.first + f.second) / 2;

        if (query(mid + 1, f.second, s) == 1)
			t.push({ mid + 1, f.second });
		if (query(f.first, mid, s) == 1)
			t.push({ f.first, mid });
	}

	return indexes;
}

int main() {

	string s = "01100000001";
	// string s = "000000000000";
	// string s = "";

	// vector<int> ans = recursiveFindIndexes(s);

	vector<int> ans = stackRecursion(s);
	
	// vector<int> ans = iterativeBinarySearch(s);


	cout << "bits: ";
	for (int x: ans)
		cout << x << " ";
	cout << endl;
	

    return 0;
}