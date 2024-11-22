// https://leetcode.com/discuss/interview-question/5004476/Google-L5-Round-1

/*

ontext:
There is a N player tournament. Players have rank 1 to N and each player has a unique rank. Assume that the best player always wins.

The tournament is knockout format. Which means if we have 8 players 
[a b c d e f g h] with their ranks [1 2 3 4 5 6 7 8], 

the tournament will look like this:
1st round: [a b] [c d] [e f] [g h]
2nd round: [a c] [e g]
3rd round: [a e]
champion : [a]

We are calling [a b c d e f g h] or [1 2 3 4 5 6 7 8] a 
"draw" where in the 1st round: first two players meet in the first match, 
the next two players meet in the second match and so on.

In the 2nd round: in the first match, 
the winner of the first match of 1st round and the winner of the second match of 1st round will play together. 
And similarly in the second match,
the winner of the third match of 1st round and the winner of the fourth match of 1st round will play together.

In short: given a draw, if we don't change the order of the players, 
players will meet in their order on the draw, and of course the winner moves to the next round. 
The tournament ends when there is only a single player is remaining.

Problem:
A draw is a valid draw when in each round, 
the best (based on rank) player plays with the worst player, 
the second best player plays with the second worst player and so on.

Problem 1:
Given a draw, find out whether it is a valid draw.

Round 1: [1,8,6,2,7,3,4,5] -> valid (maybe given wrong in test case, should be invalid)
Round 2: [1,2,3,4] -> invalid

Round 1: [1,8,4,5,3,6,2,7] -> valid
Round 2: [1,4,3,2] -> valid
Round 3: [1,2] -> valid

Round 1: [1,8,4,5,2,7,3,6] -> valid
Round 2: [1,4,2,3] -> valid
Round 3: [1,2] -> valid

*/


/*
// LOGIC


// Check from line1 to line 4 for easy understanding.  
line 4 : // x  x  x  x  x  x  x  1 = Winner.
    
line 3 : // x  x  x  1  x  x  x  2 = depth = 1, Round 3, length = 3 (1,2) + 1
line 2 : // x  1  x  4  x  2  x  3 = depth = 2, Round 2, length = 5 (1,4,2,3) + 1
line 1 : // 1, 8, 5, 4, 2, 7, 6, 3 = depth = 3, Round 1, length = 9 (1....8) + 1

*/


#include<bits/stdc++.h>
using namespace std;

void print(vector<int>& series) {
    
    int n = series.size();
    for (int i = 0 ; i < n ; i++) {
        cout << setw(2) << series[i] << " ";
    }
    cout << endl;
}

bool isValidDrawQueue(vector<int>& a) {

	int n = a.size();

	// zero player = no player left, we need 1 player
	// odd number of players aren't allowed
	if (n == 0 || n & 1) {
		return false;
	}

	queue<int> q;
	for (int x: a) {
		// cout << "push: " << x << endl;
		q.push(x);
	}

	cout << endl;
	print(a);


	while (q.size() > 1) {

		int size = q.size(); 
		cout << "size: " << size << endl;

		for (int i = 0 ; i < size ; i += 2) {

			// compare two elements
			int a = q.front();		q.pop();
			int b = q.front();		q.pop();
		
			cout << "pop: " << a << ", " << b << "\n";

			if (a + b != size + 1) {
				// cout << "test: " << a << ", " << b << endl;
				return false;
			}

			// add the winner back to queue
			q.push(min(a, b));
		}
	}

	return true;
}

vector<int> arrangeDraw(int n) {

	queue<int> q;
	q.push(1);

	while (q.size() < n) {

		int qs = q.size();
		int nqs = qs * 2;

        cout << qs << " -- " << nqs << endl;

		while (qs--) {

			int f = q.front();
			q.pop();

			q.push(f);
			q.push(nqs + 1 - f);
		}

		cout << q.size() << " ";
	}
	cout << "\n";
    
    vector<int> ans;
    while (!q.empty()) {
        ans.push_back(q.front());
        q.pop();
    }

	return ans;
}


bool isValidDrawRecursive(vector<int>& a) {

	int n = a.size();

	// only one player and 1 wins
	if (n == 1 && a[0] == 1)
		return true;

	// odd players
	if (n & 1)		return false;

	int sum = a[0] + a[1];

	vector<int> next;
	for (int i = 0 ; i < n ; i += 2) {

		if (a[i] + a[i + 1] != sum) {
			return false;
		}

		next.push_back(min(a[i], a[i + 1]));
	}

	return isValidDrawRecursive(next);
}

int main() {

	// vector<int> draw1 = { 1, 8, 6, 2, 7, 3, 4, 5 };
	// cout << "draw1 -> iterative: " << boolalpha << isValidDrawQueue(draw1) << ", recursive: " << isValidDrawRecursive(draw1) << "\n";

	// vector<int> draw2 = { 1, 8, 4, 5, 3, 6, 2, 7 };
	// cout << "draw2 -> iterative: " << boolalpha << isValidDrawQueue(draw2) << ", recursive: " << isValidDrawRecursive(draw2) << "\n";
	
	// vector<int> draw3 = { 1, 8, 4, 5, 2, 7, 3, 6 };
	// cout << "draw3 -> iterative: " << boolalpha << isValidDrawQueue(draw3) << ", recursive: " << isValidDrawRecursive(draw3) << "\n";

	// cout << "\n\n\n\n";





    // wrong way below 



// 1 16  5 12  3 14  6 11  2  15 7  10 4  13  8 9
// 1     5     3     6     2     7     4     8
// 1           3           2           4
// 1                       2
// 1  


// 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
// 1     3     5     7     9     11    13    15
// 1           5           9           13
// 1                       9 
// 1


	// the correct way
        
    // 1 16 8 9 4 13 5 12 2 15 7 10 3 14 6 11
    // 1    8   4    5    2    7    3    6
    // 1        4         2         3
    // 1                  2
    // 1
    

    // 1 8 4 5 2 7 3 6
    // 1   4   2   3
    // 1       2
    // 1

    // wrong way below 

    // 
    // 1 8 3 6 2 7 4 5
    // 1   3   2   4
    // 1       2
    // 1
    
    // 1 8 2 7 3 6 4 5
    // 1   2   3   4   
    // 1       3      
    // 1


	// follow up 
	// arrange draw
	int n = 16;
	vector<int> series = arrangeDraw(8);
    cout << "\n\nseries: ";
	for (int& x: series) {
		cout << x << " ";
	}
	cout << "\n";
    
    cout << "valid draw -> iterative: " << boolalpha << isValidDrawQueue(series) << ", recursive: " << isValidDrawRecursive(series) << "\n";


	return 0;
}