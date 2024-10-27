// https://leetcode.com/discuss/interview-question/2006734/google-onsite-l4-rejected



////////////////////////////////
// Fourth Question
////////////////////////////////


// also at: https://leetcode.com/discuss/interview-question/4835565/Google-or-Phone-Interview-or-Banglore-oror-SDE-III-oror-Android-(732024)


/*

We are given on-call rotation schedule for multiple people by: their name, start time and end time of the rotation:
Abby 1 10
Ben 5 7
Carla 6 12
David 15 17
Abby 8 13

Question: Giving a T time, return all people names who are oncall during that time.
So for T = 9; Expected output: [Abby, Carla]

data class Rotation(name: String, start: Int, end: Int)

// O(n)
// T = 9
// filtered in: [Abby, Carla, Abby]
// filtered out: [Ben, David,
// Abby - 1 <= 9, 10 >= 9
// 7 >= 9
// 6 9
// 6 <= 9 T 12 >= 9 T
// 15 <= 9 F
// 8 <= 9 T 13 >= 9 T
fun currentlyOncall(rotations: List<Rotation>, time: Int): Set<String> {
	return rotations.filter { it.start <= time && it.end >= time }.map { it.name }.toSet()
}

Given on-call rotation schedule for multiple people by: their name, start time and end time of the rotation:

Abby 1 10
Ben 5 7
Carla 6 12
David 15 17

Your goal is to return rotation table without overlapping periods representing who is on call during that time. Return "Start time", "End time" and list of on-call people:

1 5 Abby
5 6 Abby, Ben
6 7 Abby, Ben, Carla
7 10 Abby, Carla
10 12 Carla
15 17 David


	|------Abby------|
					|----Carla---|
			|--Ben--|              |-David-|
--1---5---6---7---10---12---15-------17--

// [(1, true, Abby), (5, true, Ben), (7, false, Ben), (10, false, Abby)
//

data class TableRow(start: Int, end: Int, names: List<String>>)

fun createRotationTable(rotations: List<Rotation>): List<TableRow> {
	val intermediate: List<Triple<Int, Boolean, Name>> = rotations.flatMap { listOf(it.start to true to it.name, it.end to false to it.name) }.sortedBy { it.start }
	val result = mutableListOf()
	for (
	return result
}

*/


#include <bits/stdc++.h>
using namespace std;

enum {
	START,      // 0
	END         // 1
};

vector<pair<pair<int, int>, vector<string>>> getSchedule(vector<pair<string, pair<int, int>>>& schedule) {

	int n = schedule.size();

	// vector of 3 items = { time, start/end, index }
	// start/end = 0/1
	vector<vector<int>> scheduleGroup;

	for (int i = 0 ; i < n ; i++) {
		scheduleGroup.push_back({ schedule[i].second.first, START, i });
		scheduleGroup.push_back({ schedule[i].second.second, END, i });
	}

	sort(scheduleGroup.begin(), scheduleGroup.end());

	int sn = scheduleGroup.size();
	cout << "schedules\n";
	for (int i = 0 ; i < sn ; i++)
	{
		cout << "(" << scheduleGroup[i][0] << ", " << scheduleGroup[i][1] << ") ";
	} 
	cout << endl << endl;

	unordered_set<string> oncallNames;

	vector<pair<pair<int, int>, vector<string>>> result;

	int st = -1;
	for (vector<int>& g: scheduleGroup) {

		int ending = g[0];

		// not empty - not the first name
		if (!oncallNames.empty()) {

			result.push_back({ { st, ending }, vector<string>(oncallNames.begin(), oncallNames.end()) });
		}

		// on call started
		if (g[1] == START)
			oncallNames.insert(schedule[g[2]].first);		// add name
		else if (g[1] == END)		// on call ended
			oncallNames.erase(schedule[g[2]].first);

		st = g[0];		// mark as current start 
	}

	return result;
}

vector<string> getPeopleAtTime(vector<pair<string, pair<int, int>>>& schedule, int t) {
	int n = schedule.size();

	// vector of 3 items = { time, start/end, index }
	// start/end = 0/1
	vector<vector<int>> scheduleGroup;

	for (int i = 0 ; i < n ; i++) {
		scheduleGroup.push_back({ schedule[i].second.first, START, i });
		scheduleGroup.push_back({ schedule[i].second.second, END, i });
	}

	sort(scheduleGroup.begin(), scheduleGroup.end());

	int sn = scheduleGroup.size();
	cout << "schedules\n";
	for (int i = 0 ; i < sn ; i++)
	{
		cout << "(" << scheduleGroup[i][0] << ", " << scheduleGroup[i][1] << ") ";
	} 
	cout << endl << endl;


	unordered_set<string> oncallNames;

	for (vector<int>& g: scheduleGroup) {

		if (g[0] > t)
			break;		// break at time just before the time asked

		if (g[1] == START) 
			oncallNames.insert(schedule[g[2]].first);
		else if (g[1] == END)
			oncallNames.erase(schedule[g[2]].first);
	}

	return vector<string>(oncallNames.begin(), oncallNames.end());
}

int main() {

	vector<pair<string, pair<int, int>>> schedule = {
		{ "Abby", { 1, 10 } },
		{ "Ben", { 5, 7 } },
		{ "Carla", { 6, 12 } },
		{ "David", { 15, 17 } },
		{ "Abby", { 8, 13 } }
	};

// 	// q1: Giving a T time, return all people names who are oncall during that time.
// 		// So for T = 9; Expected output: [Abby, Carla]
	int t = 9;
	vector<string> people = getPeopleAtTime(schedule, t);
	cout << "time: " << t << " - ";
	for (string name: people) {
		cout << name << " ";
	}
	cout << endl;

	t = 18;
	people = getPeopleAtTime(schedule, t);
	cout << "time: " << t << " - ";
	for (string name: people) {
		cout << name << " ";
	}
	cout << endl;



	vector<pair<pair<int, int>, vector<string>>> timeSchedules = getSchedule(schedule);

	// printing schedules
	int s = timeSchedules.size();
	for (int i = 0 ; i < s ; i++) {
		cout << setw(2) << timeSchedules[i].first.first << ", " << timeSchedules[i].first.second << " - ";
		for (string name: timeSchedules[i].second) {
			cout << name << " ";
		}
		cout << "\n";
	}

		
		
	return 0;
}
