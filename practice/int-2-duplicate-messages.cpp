// int-2-duplicate-messages
// https://leetcode.com/discuss/interview-question/5898854/L5-Google-or-Interview-Exp.-or-Rejected


/**
 * 

Round 3:

Question: 
	You are receiving signals from a robot at different timestamps 
	(in non-decreasing order). There could be duplicate messages. 
	Print only the messages that are unique in the last 10 seconds.

Follow-up: 
	Classify duplicate messages as bugs. 
		Don’t print a message if it’s repeated within the 10 seconds window (future or Past).

Input:
	[
		{ timeStamp: 1, message: "Hello" }, 
		{ timeStamp: 2, message: "Hello" }, 
		{ timeStamp: 8, message: "Hey" }, 
		{ timeStamp: 12, message: "Hello" }
	]

Output: 
	Hello Hey Hello

Follow-up Output: 
	Hey Hello (First "Hello" is excluded due to duplicates within a 10-second window).

Solution: 
	Solved both the main problem and follow-up. 
	I thought it went well, but the feedback was that my approach wasn’t optimized, 
	and they were looking for more scalable solutions.


Feedback: Lean not hire.

 * 
 */

#include <bits/stdc++.h>
using namespace std;

void printIfUniqueInLast10Secs(vector<pair<int, string>>& messages) {

	unordered_map<string, int> latestTime;

	for (int i = 0 ; i < messages.size() ; i++) {

		// first time seen
		if (latestTime.find(messages[i].second) == latestTime.end() 

			// last timestamp is more than 10 seconds
			|| (latestTime[messages[i].second] < messages[i].first - 10 + 1)) {

			cout << messages[i].second << " ";
		}

		// update latest timestamp
		latestTime[messages[i].second] = messages[i].first;
	}

	cout << "\n";
}

void printIfUniqueInLast10SecsWithMemoryRelease(vector<pair<int, string>>& messages) {

	queue<pair<int, string>> mq;
	unordered_map<string, int> mc;

	for (int i = 0 ; i < messages.size() ; i++) {

		mq.push(messages[i]);

		mc[messages[i].second]++;
	
		// remove message later 10 second window
		while (mq.front().first < messages[i].first - 10 + 1) {

			pair<int, string> f = mq.front();
			mq.pop();

			mc[f.second]--;
		}

		if (mc[messages[i].second] == 1)
			cout << messages[i].second << " ";	
	}
}

void printIfUniqueInPlusMinus10Secs(vector<pair<int, string>>& messages) {

	// queue<pair<int, string>> mq;

	unordered_map<string, int> mc;

	int l = 0;
	int r = 0;
	int i = 0;

	for (int i = 0 ; i < messages.size() ; i++) {

		// remove messages older than 10 seconds
		while (l < messages.size() && messages[l].first < messages[i].first - 10 + 1) {

			mc[messages[l].second]--;
			l++;
		}

		// add messages in next 10 second window
		while (r < messages.size() && messages[r].first < messages[i].first + 10 - 1) {

			mc[messages[r].second]++;
			r++;
		}

		if (mc[messages[i].second] == 1)
			cout << i << " - " << messages[i].second << "\n";
	} 
}



int main() {

	// (timestamp, messages)
	vector<pair<int, string>> messages = {
		{ 1, "Hello" }, 
		{ 2, "Hello" }, 
		{ 8, "Hey" }, 
		{ 12, "Hello" }
	};

	// // this does not release memory 
	// printIfUniqueInLast10Secs(messages);

	// // first question only implemented with queue for releasing memory
	// printIfUniqueInLast10SecsWithMemoryRelease(messages);

	// follow up withing +- 10 sec window
	printIfUniqueInPlusMinus10Secs(messages);

	return 0;
}