// https://leetcode.com/discuss/interview-question/4820505/Google-question/

/*
questions[
{id:1, tags: ["MAC", "VSCODE"]},
{id:2, tags: ["PY", "AI"]}
{id:3, tags: ["JAVA", "OS"]}
{id:4, tags: ["PY", "NW"]}
]

Volunteer[
{id: "1", tags:["PY",""NW], name: "A"},
{id: "2", tags:["AI"], name: "B"},
{id: "3", tags:["JAVA","NW], name: "C"},
{id: "4", tags:["JAVA","NW"], name: "D"}
]

Assign question to volunteers such that each question is assigned to at most one 
volunteer based on tags match.

One volunteer can take at most one question and maximise 
the question assigned to volunteer.

for this example
A can take question 4(PY match)
B can take question 2(AI match)
C can take question 3(Java match)
Question one no one can take as not match.

*/


#include<bits/stdc++.h>
using namespace std;

void printGraph(unordered_map<int, unordered_set<int>> g) {

	for (auto it: g) {

		cout << setw(2) << it.first << " -> ";
		for (int x: it.second) {
			cout << x << ", ";
		}
		cout << "\n";
	}
} 

void printMapStringVectorInt(unordered_map<string, vector<int>> m) {

	for (auto it: m) {

		cout << it.first << " -> ";
		for (int x: it.second) {
			cout << x << ", ";
		}
		cout << "\n";
	}
}

unordered_map<int, unordered_set<int>> createGraph(unordered_map<int, vector<string>>& questions, unordered_map<int, vector<string>>& volunteers) {

	unordered_map<string, vector<int>> questionsForTag;
	for (auto it: questions) {
		for (string tag: it.second) {
			questionsForTag[tag].push_back(it.first);
		}
	}

	// cout << "questionsForTag\n";
	// printMapStringVectorInt(questionsForTag);

    // cout << "volunteer size: " << volunteers.size() << "\n";
    
	unordered_map<string, vector<int>> volunteersForTag;
	for (auto it: volunteers) {
		for (string tag: it.second) {
			volunteersForTag[tag].push_back(it.first);
		}
	}

	// cout << "volunteersForTag\n";
	// printMapStringVectorInt(volunteersForTag);

	// create edges i.e. graph final
	unordered_map<int, unordered_set<int>> g;

	for (auto it: volunteersForTag) {

		string tag = it.first;
		vector<int> volunteersIds = it.second;
        
        // cout << "tag: " << tag << "\n";
        // cout << "volunteers: ";
        // for (int i = 0 ; i < volunteersIds.size() ; i++)
        //     cout << volunteersIds[i] << " ";
        // cout << "\n";
        
		vector<int> questionsIds = questionsForTag[tag];
	
		// add edges from all volunteers to all questions 
		for (int x = 0 ; x < volunteersIds.size() ; x++) {
			for (int y = 0 ; y < questionsIds.size() ; y++) {

				// directed edge from volunteer=x to question=y
				g[volunteersIds[x]].insert(questionsIds[y]);
			}
		}
	}


	// return created graph
	return g;
}

bool bpm(unordered_map<int, unordered_set<int>>& g, int s, int n, vector<bool>& visit, vector<int>& assign) {

    cout << "volunt: " << s << "\n";
    
	for (int q: g[s]) {

		if (!visit[q]) {
			visit[q] = true;		// mark question visited

            if (q < 5)
            cout << "que: " << q << " -> " << assign[q] << "\n";
            else 
                cout << "Q: " << q;
            
			if (assign[q] == -1 || bpm(g, assign[q], n, visit, assign))
			{
                cout << "assign: "  << q << " to: " << s << "\n";
				assign[q] = s;
				return true;
			}
		}
	}

	return false;
}


int findMaxMatch(unordered_map<int, vector<string>>& questions, int numQuestions,
	unordered_map<int, vector<string>>& volunteers, int numVolunteer) {

    unordered_map<int, unordered_set<int>> g = createGraph(questions, volunteers);

	// // print graph
	// printGraph(g);
    
    // questions assigned to which volunteer
	vector<int> assign(numQuestions + 1, -1);
	int ans = 0;		// count of assignments

	for (int i = 1 ; i <= numVolunteer ; i++) {

		vector<bool> visit(numQuestions + 1, false);

		if (bpm(g, i, numQuestions, visit, assign))
			ans++;

        // cout << "\nend\n\n\n";
    }

    // cout << "assignments: \n";
    // for (int i = 0 ; i <= numQuestions ; i++)
    //     cout << setw(2) << i << " ";
    // cout << "\n";
    // for (int i = 0 ; i <= numQuestions ; i++) 
    //     cout << setw(2) << assign[i] << " ";


	return ans;
}


int main() {

	int numQuestions;
	cin >> numQuestions;

	unordered_map<int, vector<string>> questions;

	for (int i = 0 ; i < numQuestions ; i++) {

		int id;
		cin >> id;

		int numTags;
		cin >> numTags;

		vector<string> tags(numTags);
		for (int i = 0 ; i < numTags ; i++) {
			cin >> tags[i];
		}
	
		questions[id] = tags;
	}


	int numVolunteer;
	cin >> numVolunteer;

	unordered_map<int, vector<string>> volunteers;

	for (int i = 0 ; i < numVolunteer ; i++) {

		int id;
		cin >> id;

		int numTags;
		cin >> numTags;

		vector<string> tags(numTags);
		for (int i = 0 ; i < numTags ; i++) {
			cin >> tags[i];
		}
        
        volunteers[id] = tags;
	}

	int ans = findMaxMatch(questions, numQuestions, volunteers, numVolunteer);

	cout << "max matching: " << ans << "\n";

	return 0;
}