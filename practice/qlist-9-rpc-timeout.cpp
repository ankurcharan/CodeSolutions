// qlist-9-rpc-timeout


// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792

////////////////////////////////////////////////////////////////////////////////////////////////////
// this list has a couple of questions
// here is que 9
////////////////////////////////////////////////////////////////////////////////////////////////////



/*

You have a stream of rpc requests coming in. Each log is of the
form {id, timestamp, type(start/end)}. Given a timeout T, 
you need to figure out at the earliest possible time if a request
has timed out.

Eg :

id - time - type
0 - 0 - Start
1 - 1 - Start
0 - 2 - End
2 - 6 - Start
1 - 7 - End

Timeout = 3
Ans : {1, 6} ( figured out id 1 had timed out at time 6 )

*/


/*

https://leetcode.com/discuss/interview-question/924141/google-phone-screen-new-grad

You have a stream of rpc requests coming in. Each log is of the form {id, timestamp, type(start/end)}. 
Given a timeout T, you need to figure out at the earliest possible time if a request has timed out.
Eg :
id - time - type
0 - 0 - Start
1 - 1 - Start
0 - 2 - End
2 - 6 - Start
1 - 7 - End
Timeout = 3
Ans : {1, 6} ( figured out id 1 had timed out at time 6 )


I was able to provide an O(nlogn) solution using maps but the interviewer wanted an O(n) solution. 
I'm thinking maybe using a hashmap with a deque would do it but if anyone else has 
any solutions please share.

*/

#include <bits/stdc++.h>
using namespace std;

enum RPCType {
	START,
	END
};

class RPCTrack {

	// (id, start timestamp)
	list<pair<int, int>> q;
	// (id, iterator to list)
	unordered_map<int, list<pair<int, int>>::iterator> m;

	int timeout;

public:
	RPCTrack(int timeout) {
		this -> timeout = timeout;
	}

	void addRequest(vector<int>& request) {

		int id = request[0];
		int currTime = request[1];

		while (q.front().second < currTime - timeout) {

			pair<int, int> f = q.front();
			q.pop_front();

			cout << f.first << " timed out at " << currTime << "\n";
		}

		if (request[2] == START) {
			q.push_back({ id, currTime });
			m[id] = prev(q.end());
		}
		else {		// END
			q.erase(m[id]);
			m.erase(id);
		}
	}
};

int main() {

	// pair of (id, timestamp, start/end)
	vector<vector<int>> requests = {
		{ 0, 0, START },
		{ 1, 1, START },
		{ 0, 2, END },
		{ 2, 6, START },
		{ 1, 7, END }
	};

	int t = 3;

	RPCTrack rt(t);

	for (vector<int>& x: requests) {

		cout << "adding: " << x[0] << ",  " << x[1] << ", " << x[2] << endl;
		rt.addRequest(x);
	}


	return 0;
}
