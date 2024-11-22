// largest-files-under-path
// https://leetcode.com/discuss/interview-question/5920301/Google-New-Grad-2025-or-Interview-or-Tech-%2B-Googleyness




// It was a long question but had simple implementation, Google intentionally makes 
// such description to confuse candidates, I'll try to write as much as I remember.


// Input: given a URI e.g. /google/storage/var 
// you need to return the list of 10 largest files inside the folder as {sz, url}

// Output:
// 1008372 /google/storage/var/music.mp4
// 313236 /google/storage/var/www/img.jpg
// 253964 /google/storage/var/log/voice.mp3
// 192544 /google/storage/var/lib.txt
// 152628 /google/storage/var/spool.mp4
// 152508 /google/storage/var/spool/squid/noice.png
// 136524 /google/storage/var/spool/squid/00.txt
// 95736 /google/storage /var/log/mrtg.log
// 74688 /google/storage/var/log/squid/color.txt
// 62544 /google/storage/var/cache.txt


// You have two helper functions which computes in O(1)


// helper.sz(str). takes the string as input if it is a file it returns the size of the file otherwise -1
// helper.list(str) takes a string as input if it is a folder it returns a list of all the directories inside it 
// (all the folders and imidiate files). 

// If str is a file it returns null.
// I wrote a recursive code using these helper functions, then we discussed the time and space complexity.


// Follow Up
// Now you need to return the 10 largest folders
// size of folder = sum of all the imidiate files inside that folder


// Wrote the recursive code for this one, but it had some issues, we were out of time so moved on to googleyness.



#include<bits/stdc++.h>
using namespace std;


enum FType
{
	I_FILE,
	I_DIRECTORY
};

class Node {
public:
	string name;
	FType type;
	int size;

	unordered_map<string, Node*> children;

	Node(string name, FType t, int size) {
		this -> name = name;
		this -> type = t;
		this -> size = size;
	}
};

void print(Node* root, string path) {

	if (root == NULL)
		return;

	string x = path + "/" + root -> name;
	cout << x << " : " <<  root -> size << endl;

	for (auto it: root -> children) {
		print(it.second, x);
	}
}

class cmp {
public:
	bool operator()(pair<int, string>& a, pair<int, string>& b) {

		return a.first > b.first;
	}
};

void traverseLargest(Node* root, int k, priority_queue<pair<int, string>, vector<pair<int, string>>, cmp>& largestFiles) {

	if (root == NULL)
		return;


	// cout << "name: " << root -> name << " " << root -> type << " " << root -> size << " \n";
	if (root -> type == I_FILE && (largestFiles.size() < k || largestFiles.top().first < root -> size)) {

		// this is bigger
		// cout << "found\n";

		if (largestFiles.size() == k)
			largestFiles.pop();

		largestFiles.push({ root -> size, root -> name });
	}

	for (auto it: root -> children) {

		traverseLargest(it.second, k, largestFiles);
	}
}

void traverseLargestFolders(Node* root, int k, priority_queue<pair<int, string>, vector<pair<int, string>>, cmp>& largestFolders) {

	if (root == NULL)
		return;

	
	long long int folderSize = 0;
	for (auto it: root -> children) {

		if (it.second -> type == I_DIRECTORY)
			traverseLargestFolders(it.second, k, largestFolders);
		else 
			folderSize += it.second -> size;
	}
	
	cout << "name: " << setw(5) << root -> name << " " << root -> type << " " << root -> size << " " << folderSize << "\n";

	if (root -> type == I_DIRECTORY && (largestFolders.size() < k || largestFolders.top().first < folderSize)) {

		if (largestFolders.size() == k)
			largestFolders.pop();

		largestFolders.push({ folderSize, root -> name });
	}
}



void mainQuestion(Node* root) {

	string s = "/google/storage/var"; 

	vector<string> path;

	stringstream ss(s);
	string token;
	while (getline(ss, token, '/')) {
		path.push_back(token);
	}

	// traverse path
	bool nodePresent = true;
	for (int i = 2 ; i < path.size() ; i++) {

		if (root -> children.find(path[i]) == root -> children.end()) {
			nodePresent = false;
			break;
		}

		// cout << root -> name << " ";

		root = root -> children[path[i]];
	}
	cout << endl;

	cout << "start: " << root -> name << "\n\n";

	// print(root, "");

	priority_queue<pair<int, string>, vector<pair<int, string>>, cmp> largestFiles;
	traverseLargest(root, 5, largestFiles);


	priority_queue<pair<int, string>, vector<pair<int, string>>, cmp> largestFolders;
	traverseLargestFolders(root, 6, largestFolders);

	cout << "\n\ntop k files:\n";
	while (largestFiles.empty() == false) {
		cout << largestFiles.top().first << " " << largestFiles.top().second << "\n";
		largestFiles.pop();
	}

	cout << "\n\ntop k folders:\n";
	while (largestFolders.empty() == false) {
		cout << largestFolders.top().first << " " << largestFolders.top().second << "\n";
		largestFolders.pop();
	}
}

int main() {

	// create directories
	Node* root = new Node("google", I_DIRECTORY, -1);
	root -> children["storage"] = new Node("storage", I_DIRECTORY, -1);
	root -> children["storage"] -> children["var"] = new Node("var", I_DIRECTORY, -1);

	Node* var = root -> children["storage"] -> children["var"];

	var -> children["music.mp4"] = new Node("music.mp4", I_FILE, 1008372);
	var -> children["lib.txt"] = new Node("lib.txt", I_FILE, 192544);
	var -> children["spool.mp4"] = new Node("spool.mp4", I_FILE, 152628);
	var -> children["cache.txt"] = new Node("cache.txt", I_FILE, 62544);

	var -> children["www"] = new Node("www", I_DIRECTORY, -1);
	var -> children["log"] = new Node("log", I_DIRECTORY, -1);
	var -> children["spool"] = new Node("spool", I_DIRECTORY, -1);

	var -> children["www"] -> children["img.jpg"] = new Node("img.jpg", I_FILE, 313236);

	var -> children["log"] -> children["voice.mp3"] = new Node("voice.mp3", I_FILE, 253964);
	var -> children["log"] -> children["mrtg.log"] = new Node("mrtg.log", I_FILE, 95736);

	var -> children["log"] -> children["squid"] = new Node("squid", I_DIRECTORY, -1);

	Node* logSquid = var -> children["log"] -> children["squid"];
	logSquid -> children["color.txt"] = new Node("color.txt", I_FILE, 74688);

	var -> children["spool"] -> children["squid"] = new Node("squid", I_DIRECTORY, -1);

	var -> children["spool"] -> children["squid"] -> children["noice.png"] = new Node("noice.png", I_FILE, 152508);
	var -> children["spool"] -> children["squid"] -> children["00.txt"] = new Node("00.txt", I_FILE, 136524);


	// print(root, "");

	// main question
	mainQuestion(root);

	return 0;
}
