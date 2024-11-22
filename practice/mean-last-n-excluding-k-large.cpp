// https://leetcode.com/discuss/interview-question/264495/google-onsite-question-mean-of-last-n-integers-in-stream-excluding-k-largest
// mean-last-n-excluding-k-large.cpp

/*

There is a stream of integers. Every time you see a new element in the stream, 
return the mean value of the last N elements, excluding the largest K elements.


Example:
N = 5
K = 2
elements so far = [20, 2, -2, 0, 10, 1, 5, -2, 0]


last N elements: [10, 1, 5, -2, 0]
largest K elements: [10, 5]
result = (1+(-2)+0)/3 = -0.3333333


I could not find a neat approach but only a suboptimal one.

*/

#include<bits/stdc++.h>
using namespace std;

void meanNK(vector<int>& stream, int m, int k) {

	long long int smallerSum = 0;

	unordered_set<int> seen;
	queue<int> window;

	multiset<int> smaller, bigger;

	int streamSize = stream.size();
	for (int i = 0 ; i < streamSize ; i++) {

		int x = stream[i];
        cout << "inserting: " << x << "\n";

        // if (bigger.empty())
        // 	cout << "bigger empty ";
        // if (smaller.empty())
        // 	cout << "smaller empty";
        // cout << endl;

		if (x >= *bigger.begin()) {
			cout << "push to bigger";
			bigger.insert(x);
		} else {
			cout << "push to smaller";
			smaller.insert(x);
			smallerSum += x;
		}
		cout << endl;

		// remove oldest element to make space for new element
		if (window.size() == m) {

			int f = window.front();
			window.pop();

			if (bigger.find(f) != bigger.end()) {
				bigger.erase(bigger.find(f));
			}
			else {
				smaller.erase(smaller.find(f));
			}
		}
        
        
		window.push(x);

        while (bigger.size() > k) {
            
            int x = *bigger.begin();
            bigger.erase(bigger.begin());
            
            smaller.insert(x);
            smallerSum += x;
        }
        
		while (bigger.size() < k && smaller.size() > 0) {

			int x = *smaller.rbegin();
			smaller.erase(prev(smaller.end()));

			smallerSum -= x;
			bigger.insert(x);
		}
        
        cout << "smaller: ";
        for (auto it: smaller) {
            cout << it << " ";
        }
        cout << "\n";
        cout << "bigger: ";
        for (auto it: bigger) {
            cout << it << " ";
        }
        cout << "\n";


		if (seen.find(x) == seen.end()) {

            cout <<  "avg: ";
            if (window.size() < m) {
                cout << -1;
            }
            else {
                cout << (smallerSum / (m - k));
            }
			cout << "\n";
		}
        
        seen.insert(x);
        
        cout << "\n";
	}

}

int main() {

	vector<int> stream = { 20, 2, -2, 0, 10, 1, 5, 0, -2, 0 };
    
	int n = 5;
	int k = 2;
    meanNK(stream, n, k);

	return 0;
}


