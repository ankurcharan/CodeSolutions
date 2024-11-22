// merge-meetings
// https://leetcode.com/discuss/interview-question/6058077/Google-or-L4-or-On-site-or-Bangalore

/*

I was being asked this question today on On-Site Round 2 for 
L4 position of Google Software Engineer. 
Tried applying basic scheduling algorithm to schedule the meetings and 
exclude the part where it is 'Do Not Schedule'.


Although I missed covering a few edge cases. 
Couldn't think of any other solution. 
Any other alternative solutions?


Question:
	You have a list of meetings in your calendar with a start and end time.
	You are very busy, so meetings can overlap.
	You also have one "Do Not Schedule" interval during which you don't attend any meeting.
	Any meeting schedule that overlaps with a DNS slot is automatically 
	cut such that it does not overlap with the DNS slot anymore.

Output:
	Return a list of non-overlapping time intervals when you are in a meeting.


	Meeting  | ____    _______________    ___
	         |  _____         ________          __
	DNS      |             xxxx
	-------------------------------------------------> t
	RES.     | ______  ____xxxx_______    ___   __

	Sample input (for simplicity, all intervals include the left point and exclude the right point):


Meetings: 
	[(1, 7), (5, 10), (12, 30), (22, 30), (40, 50), (60, 70)]
DNS: 
	(18, 25)

Sample output: 
	[(1, 10), (12, 18), (25, 30), (40, 50), (60, 70)]

*/


#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> mergeMeetins(vector<pair<int, int>>& meetings, pair<int, int>& dnd) {

	int n = meetings.size();
	if (n == 0)
		return {};

	sort(meetings.begin(), meetings.end());

    vector<pair<int, int>> mergedMeetings;
    
	for (int i = 0 ; i < n ; i++) {

		int st  = meetings[i].first;
		int end = meetings[i].second;

		while (i < n-1 && end >= meetings[i + 1].first) {
			end = meetings[i + 1].second;
			i++;
		}
        
        mergedMeetings.push_back({ st, end });
	}
    
    cout << "meetings:\n";
    for (pair<int, int>& m: mergedMeetings) {
        cout << m.first << ", " << m.second << "\n";
    }
    cout << "\n\n";
    
    // remove dnd
    vector<pair<int, int>> ans;
    for (int i = 0 ; i < mergedMeetings.size() ; i++) {
        
        // (start after end of dnd) || (end befoe start of dnd)
        if ((mergedMeetings[i].first > dnd.second) || (mergedMeetings[i].second < dnd.first))
            ans.push_back(mergedMeetings[i]);
        else {
            
            // cout << i << "  check\n";
            
            //     18 25 
            // 12          30
            
            if (dnd.first > mergedMeetings[i].first) 
                ans.push_back({ mergedMeetings[i].first, dnd.first - 1 });
            
            if (dnd.second < mergedMeetings[i].second) {
                ans.push_back({ dnd.second + 1, mergedMeetings[i].second });
            }
        }
    }

	return ans;
}

int main() {
	
	// vector<pair<int, int>> meetings = {
	// 	{ 1, 7 }, { 5, 10 }, { 12, 30 }, { 22, 30 }, { 40, 50 }, { 60, 70 }
	// };
    
	vector<pair<int, int>> meetings = {
		{ 1, 7 }, { 5, 10 }, { 12, 30 }, { 22, 30 }, { 40, 50 }, { 45, 70 }
	};
    
	// vector<pair<int, int>> meetings = {
	// 	{ 1, 7 }, { 5, 10 }, { 12, 20 }, { 22, 30 }, { 40, 50 }, { 45, 70 }
	// };

	pair<int, int> dns = { 18, 25 };
    // pair<int, int> dns = { 28, 32 };

	vector<pair<int, int>> merged = mergeMeetins(meetings, dns);
	for (pair<int, int>& f: merged) {
		cout << f.first << ", " << f.second << "\n";
	}

	return 0;
}