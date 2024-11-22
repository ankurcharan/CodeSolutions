// https://leetcode.com/discuss/interview-question/4878435/Google-Telephonic-PhoneScreen-Interview-question
// frog-jump-LR

// https://leetcode.com/discuss/interview-question/4878435/Google-Telephonic-PhoneScreen-Interview-question


/*

Hi ,


I gave my first Technical Phone Screening round on 6th March 2024,
Can't reveal the exact questions,


Question is about a frog which can go left or right with with maximum 
possible step be l for left and r for right, i.e. 
frog can move right 0 or 1, or 2 or ... r times, given start and destination, find minimum steps to reach.

Something related to making maximum number using digits(1 to 9) 
where using a digit has some associated cost(can be different for dif digits), 
and we have fixed money we can use.
But I don't know why my recruiter is taking too long to respond. 
Not even replying ? Is it normal, it's my first time giving Interview out of college,
Exp: 8 Months in SWE


UPD: Just got the mail for next round of interviews. 
(alwasys use google-candidate-feedback in case of delay from any side, thank me later)

*/






////////////////////////////
////////////////////////////
///// FIRST QUESTION ///////
////////////////////////////
////////////////////////////


#include<bits/stdc++.h>
using namespace std;

// curr, numOfSteps
unordered_map<int, int> dp;

int getMinSteps(int start, int end, int l, int r) {

    // cout << "start: " << start << ", end: " << end << "\n";
    
	if (start == end)
		return 0;

	unordered_set<int> visited;
	visited.insert(start);

	// (num, steps)
	queue<pair<int, int>> q;
	q.push({ start, 0 });

	while (!q.empty()) {

		pair<int, int> f = q.front();
		q.pop();
        
        cout << "pop: " << f.first << " in " << f.second << " steps\n"; 

		if (f.first == end) {
			return f.second;
		}

		for (int i = 1 ; i <= l && f.first - i >= 0 ; i++) {

            if (visited.find(f.first - i) == visited.end()) {
                
                // cout << "push minus: " << f.first-i << "\n";
                q.push({ f.first - i, f.second + 1 });
                visited.insert(f.first - i);    
            }            
            
		}
		for (int i = 1 ; i <= r ; i++) {
		
			// not int overflow
			if (start > 0 && i > 0 && start <= INT_MAX - i) {
                
                if (visited.find(f.first + i) == visited.end()) {
                    
                    
                    // cout << "push add: " << f.first+i << "\n";
                    q.push({ f.first + i, f.second + 1 });
                    visited.insert(f.first + i);    
                }   
			}
		}
	}

	// not possible
	return -1;
}

int main() {

	int start = 10;
	int end = 99;

	int l = 1;
	int r = 10000;
    
    cout << "start: " << start << ", end: " << end << "\n";

	int ans = getMinSteps(start, end, l, r);

	cout << "ans: " << ans << "\n";


	return 0;
}