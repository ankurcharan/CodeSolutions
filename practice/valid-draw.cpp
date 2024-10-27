// https://leetcode.com/discuss/interview-question/5004476/Google-L5-Round-1

/*

ontext:
There is a N player tournament. Players have rank 1 to N and each player has a unique rank. Assume that the best player always wins.

The tournament is knockout format. Which means if we have 8 players [a b c d e f g h] with their ranks [1 2 3 4 5 6 7 8], the tournament will look like this:
1st round: [a b] [c d] [e f] [g h]
2nd round: [a c] [e g]
3rd round: [a e]
champion : [a]

We are calling [a b c d e f g h] or [1 2 3 4 5 6 7 8] a "draw" where in the 1st round: first two players meet in the first match, the next two players meet in the second match and so on.

In the 2nd round: in the first match, the winner of the first match of 1st round and the winner of the second match of 1st round will play together. And similarly in the second match,
the winner of the third match of 1st round and the winner of the fourth match of 1st round will play together.

In short: given a draw, if we don't change the order of the players, players will meet in their order on the draw, and of course the winner moves to the next round. The tournament ends when there is only a single player is remaining.

Problem:
A draw is a valid draw when in each round, the best (based on rank) player plays with the worst player, the second best player plays with the second worst player and so on.

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

bool isValidDrawQueue(vector<int>& a) {

	int n = a.size();

	// zero player = no player left, we need 1 player
	// odd number of players aren't allowed
	if (n == 0 || n & 1) {
		return false;
	}

	queue<int> q;
	for (int x: a) {
		q.push(x);
	}

	while (q.size() > 1) {

		int size = q.size(); 

		for (int i = 0 ; i < size ; i += 2) {

			// compare two elements
			int a = q.front();		q.pop();
			int b = q.front();		q.pop();
		
			if (a + b != size + 1)
				return false;

			// add the winner back to queue
			q.push(min(a, b));
		}
	}

	return true;
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

	vector<int> draw1 = { 1, 8, 6, 2, 7, 3, 4, 5 };
	cout << "draw1 -> iterative: " << boolalpha << isValidDrawQueue(draw1) << ", recursive: " << isValidDrawRecursive(draw1) << "\n";

	vector<int> draw2 = { 1, 8, 4, 5, 3, 6, 2, 7 };
	cout << "draw2 -> iterative: " << boolalpha << isValidDrawQueue(draw2) << ", recursive: " << isValidDrawRecursive(draw2) << "\n";
	
	vector<int> draw3 = { 1, 8, 4, 5, 2, 7, 3, 6 };
	cout << "draw3 -> iterative: " << boolalpha << isValidDrawQueue(draw3) << ", recursive: " << isValidDrawRecursive(draw3) << "\n";


	return 0;
}