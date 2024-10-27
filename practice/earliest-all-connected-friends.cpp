// earliest-all-connected-friends.cpp

/*

Here we have an event log file which is produced by the Friends service like below:

1648305616 Alice and Bob become friends
1648305678 Charlie and Dan become friends
1648306171 Bob and Charlie become friends
1648306237 Alice and Erin become friends
...
Given a list of all users and the logs above, find the earliest time 
when everyone became reachable to every other person through the friends.

if person A is friends with B, A is reachable from B and B is reachable from A.
if person A is friends with B, and B is friends with C, C is reachable from A through B.
if person A is reachable to B, if person B is reachable to C, A and C are reachable.

Example:

A-E
2 A B
5 A C
10 D E
15 E C
18 A E
25 A D
Answer: 15

A-E
2 A B
5 A C
10 D E
18 B C
Answer: -1

*/


#include <bits/stdc++.h>
using namespace std;

// 0-(n-1)  people
// u-v      edges



int find(vector<int>& dsu, int x) {

   if (dsu[x] != x) {
      dsu[x] = find(dsu, dsu[x]);
   }
   return dsu[x];
}

void union2(vector<int>& dsu, vector<int>& rank, int u, int v) {

  int up = find(dsu, u);
  int vp = find(dsu, v);
  
  if (up == vp)
    return;
  
  if (rank[up] < rank[vp]) {
    dsu[up] = vp;
    rank[vp] += rank[up];
  }
  else { 
    dsu[vp] = up;
    rank[up] += rank[vp];
  }
}

// n = no of vertices
// edges = (timestamp, (u, v)

void print(vector<int>& x) {
    
    int n = x.size();
    for (int i = 0 ; i < n ; i++)
        cout << x[i] << " ";
    cout << "\n";
}


int getFirstTimestamp(int n, vector<pair<int, pair<int, int>>> edges) {

  if (n == 0 || n == 1)
      return 0;
  
  vector<int> dsu(n);
  vector<int> rank(n, 1);
  
  // this is for parent 
  for (int i = 0 ; i < n ; i++)
     dsu[i] = i;

  int visited = 1;
  for (pair<int, pair<int, int>>& e: edges) {
    
    int u = e.second.first;
    int v = e.second.second;
    
    if (find(dsu, u) != find(dsu, v)) {
      
        print(dsu);
        cout << u << "-" << find(dsu, u) << ", " << v << "-" << find(dsu, v) << "\n";
      union2(dsu, rank, u, v);
      visited++;
        
        print(dsu);
        
        cout << "\n";
      
       // all visited
      if (visited == n) {
        return e.first;
      }
    }
  }
  
   // cannot be visited
  return -1;
}

int main() {

//   A-E
// 2 A B
// 5 A C
// 10 D E
// 15 E C
// 18 A E
// 25 A D

  // int n = 5;
  // vector<pair<int, pair<int, int>>> f  = {
  //   { 2, { 0, 1 } },
  //   { 5, { 0, 2 } },
  //   { 10,{ 3, 4 } },
  //   { 15,{ 4, 2 } },
  //   { 18,{ 0, 4 } },
  //   { 25,{ 0, 3 } }
  // };
    
    
    
//     A-E
// 2 A B
// 5 A C
// 10 D E
// 18 B C
    
    
  int n = 5;
  vector<pair<int, pair<int, int>>> f  = {
    { 2, { 0, 1 } },
    { 5, { 0, 2 } },
    { 10,{ 3, 4 } },
    { 18,{ 1, 2 } }
  };

  int ans = getFirstTimestamp(n, f);

  cout << ans << "\n";

  return 0;
}




/*

indx = 0 1 2 3 4
dsu  = 3 0 3 3 3
rank = 2 2 2 1 2 

visited = 5

n = 5;

2  0 1
5  0 2
10 3 4
15 4 2



*/

/*

Support "unfriend"
Now Friends service has a feature for users to unfriend and populate the logs like below.
It means where A and C are reachable via B, and A unfriends B, C becomes not reachable from A unless there are other 
friends reachable to C.

1648305616 Alice and Bob become friends
1648305678 Charlie and Dan become friends
1648306171 Bob and Charlie become friends
1648306225 Alice and Bob broke up
1648306237 Alice and Erin become friends
1648306311 Charlie and Dan broke up


A - B
B - C
A - C

A,B,C

*/