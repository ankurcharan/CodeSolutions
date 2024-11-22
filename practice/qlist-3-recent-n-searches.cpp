// qlist-3-recent-n-searches.cpp


// https://leetcode.com/discuss/interview-question/4831503/google-questions/2291792

////////////////////////////////////////////////////////////////////////////////////////////////////
// this list has a couple of questions
// here is que 1
////////////////////////////////////////////////////////////////////////////////////////////////////

/*

Design a search data structure to store and display recent searches. If
a user just clicks the search bar without typing anything, it should
return the N most recent searches. Given a search string it should save
the search and also return the N most recent searches

*/

// very LRU cache





// https://leetcode.com/discuss/interview-experience/4630516/Google-or-L4-or-Seattle-or-January-2024-Hiring-Freeze

/*

Status: 3 YOE, B.S CS @ Average public school
Position: Software Engineer III, Google Cloud (L4)
Location: Seattle, WA, Mountain View, CA
Date: January 2024


This was my second time interviewing at Google. 
I once again got the interview through a cold application and heard back a few weeks later. 
I scheduled the TPS for about 4 weeks after the inital email since the EOY holiday break got in the way.


I prepped using Grind 75, Neetcode.io, Sean Prashad's Leetcode patterns list, and 
Leetcode's Google tagged questions list. Did around 150 problems, pretty much all easies and mediums.


Technical Phone Screen (TPS):


Design a search data structure to store and display recent searches. If a user just clicks the 
search bar without typing anything, it should return the N most recent searches. 
Given a search string it should save the search and also return the N most recent searches


After some clarification, this boiled down to implementing two functions:


addSearch(String search)
getRecentSearches()
given a number N which represented how many recent searches to return


My initial thoughts were to store the search strings in a List or Map when the addSearch() 
function was called and to pull the last N items from the List or Map when getRecentSearches() was called. 
However after thinking about runtime and clarifying that duplicates could move the position of 
the stored search string from the back of the list to the front made me realize that this problem was 
very similar to LRU Cache where we would need to maintain a HashMap of search string -> a Node 
that contained the string and prev/next pointers. 
I would also need a Doubly Linked List to store the order of the searches and edit the 
ordering of the list in O(1) time. After discussing this approach with the interviewer he seemed to be 
pleased with the solution.


class Node{
	String val;
	Node prev;
	Node next;

	public Node(String val){
		this.val = val;
	}
}

// S: O(unique strings)
class SearchDS{
	int N;
	Map<String, Node> map;
	Node left;
	Node right;

	public SearchDS(int num){
		this.N = num;
		map = new HashMap<>();
		left.next = right;
		right.next = left;
	}

	//R : O(1)
	public void addSearch(String s){
		if(!map.containsKey(s)){
			map.put(s, new Node(s));
		}else{
			remove(map.get(s));
		}

		insert(map.get(s));
	}

	// R: O(N)
	public List<String> getRecentSearches(){
		List<String> res = new ArrayList<>();
		Node curr = this.right;
		int iter = this.N - 1;

		while(iter >= 0 && curr != left){
			res.add(curr.val);
			iter--;
			curr = curr.prev;
		}

		return res;
	}

	//remove node from DLL
	public void remove(Node n){
		Node prv = n.prev;
		Node nxt = n.next;

		prv.next = nxt;
		nxt.prev = prv;
	}

	//add Node at right
	public void insert(Node n){
		Node prv = right.prev;
		Node nxt = right;

		prv.next = n;
		nxt.prev = n;
		n.prev = prv;
		n.next = nxt;
	}
}

If you look at the code, it is 98% the same as LRU cache, except the Node stores a single String 
rather than <Integer,Integer> KV pair.


Runtime:


addSearch(): O(1) to update map and fix a nodes place in the DLL
getRecentSearches: O(N) will iterate through N number of nodes in the DLL
Space:


O(number of unique strings): Map and DLL will contain number of unique strings searched


*/

#include <bits/stdc++.h>
using namespace std; 

class Search {

	int capacity;

	list<string> q;
	unordered_map<string, list<string>::iterator> m;


public:

	void printLastNRecent() {
		cout << "queue: ";
		for (auto x: q) {
			cout << x << " ";
		}
		cout << "\n";
	}

	Search(int s) {
		this -> capacity = s;
	}

	void add (string s) {

		if (m.find(s) != m.end()) {

			q.erase(m[s]);
			q.push_back(s);
			m[s] = prev(q.end());
		}
		else {

			if (q.size() == capacity) {

				m.erase(q.front());
				q.erase(q.begin());
			}
		
			q.push_back(s);
			m[s] = prev(q.end());
		}
	}
};

int main () {

	int n = 5;

	vector<string> searches = {
		"a",
		"b",
		"a",
		"c",
		"d",
		"e",
		"f",
		"b",
		"b",
		"f"
	};

	Search s(n);
	for (string x: searches) {
		cout << "add: " << setw(3) << x << " -- ";
		s.add(x);			// add the value
		s.printLastNRecent();	// print last N recent
	}

	return 0;
}

