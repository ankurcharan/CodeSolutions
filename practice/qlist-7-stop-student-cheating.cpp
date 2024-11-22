// qlist-7-stop-student-cheating
// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792


// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792

////////////////////////////////////////////////////////////////////////////////////////////////////
// this list has a couple of questions
// here is que 7
////////////////////////////////////////////////////////////////////////////////////////////////////



/*


A number of students are taking exams in a room. 
Students sitting adjacent to each other and taking the same exam can cheat. 
Arrange the students so that cheating opportunities are minimized. I was free to choose input format.

I chose the input to be a list of length n, denoting n students. 
The element at index i would indicate the exam student i is taking.

For example, [1,2,3,1,2,2]

Student 0 is taking exam 1
Student 1 is taking exam 2
Student 2 is taking exam 3
Student 3 is taking exam 1
Student 4 is taking exam 2
Student 5 is taking exam 2

Output would be a list with the students re-arranged. 
An acceptable output for the above case would be [1,2,3,2,1,2].



follow up: arrange with max distance


*/


#include <bits/stdc++.h>
using namespace std;

class cmp {
public: 
    bool operator()(pair<int, int>& a, pair<int, int>& b) {
        
        if (a.first == b.first) {
            return a.second > b.second;
        }
        
        return a.first < b.first;
    }
};

vector<int> arrangeStudentsNotTogether(vector<int>& s) {

	unordered_map<int, int> f;

	for (int x: s) {
		f[x]++;
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
	for (auto it: f) {
		pq.push({ it.second, it.first });
	}

	vector<int> order;
	pair<int, int> last = { -1, 0 };

	while (!pq.empty()) {
		
		pair<int, int> top = pq.top();
		pq.pop();

        // cout << top.first << " = " << top.second << "\n";
        
		order.push_back(top.second);
		top.first--;

		if (last.first > 0) {
			pq.push(last);
		}

		last = top;
	}

	return order;
}



bool arrayComparator(pair<int, int>& a, pair<int, int>& b) {
    
    if (a.second == b.second) {
        return a.first < b.first;
    }
    return a.second > b.second;
}

vector<int> arrangeStudentsMaxDistance(vector<int>& a) {
    
    unordered_map<int, int> f;
    for (int x: a) {
        f[x]++;
    }
    
    vector<pair<int, int>> v;
    for (auto it: f) {
        v.push_back(it);
    }
    
    sort(v.begin(), v.end(), arrayComparator);
    
    cout << "\nnums and elements\n";
    for (int i = 0 ; i < v.size() ; i++) {
        cout << v[i].first << " " << v[i].second << "\n";
    }
    cout << "\n";
    
    vector<int> orderMax;
    int idx = 0;
    int n = v.size();
    while (orderMax.size() < a.size()) {
        
        cout << "orderMaxSize: " << orderMax.size() << "\n";
        
        if (v[idx].second == 0) {
            // idx = 0;
            idx = (idx + 1) % n;
            continue;
        }
        
        orderMax.push_back(v[idx].first);
        v[idx].second--;
        
        idx = (idx + 1) % n;
    }
    
    return orderMax;
}

int main() {


// 	vector<int> s = { 1, 2, 3, 1, 2, 2 };
// 	for (int x: s) {
// 		cout << x << " ";
// 	}
// 	cout << endl;
    
//     vector<int> order = arrangeStudentsNotTogether(s);
//     for (int x: order) {
//         cout << x << " ";
//     }
//     cout << endl;
    
    
    
    
    
    
    
    vector<int> s = { 1, 2, 3, 1, 2, 4 };
	for (int x: s) {
		cout << x << " ";
	}
	cout << endl;
    
    vector<int> order = arrangeStudentsNotTogether(s);
    for (int x: order) {
        cout << x << " ";
    }
    cout << endl;
    
    vector<int> orderMax = arrangeStudentsMaxDistance(s);
    for (int x: orderMax) {
        cout << x << " ";
    }
    cout << endl;

	return 0;
}
