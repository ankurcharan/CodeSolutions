// https://leetcode.com/discuss/interview-question/5063427/google-onsite-round-2

/*
tdin: 
7 6
16 0 16 0 16 0 0 
0 1
1 5 
2 3
3 4
4 5
5 6


graph: 
                                         16 (A/0)
                                         |
                                         0 (B/1)
                                         |   
16 (C/2) ---- 0 (D/3) ---- 16 (E/4) ---- 0 (F/5) ---- 0 (G/6)

after:

                                         16 (A/0)
                                         |
                                         15 (B/1)
                                         |   
16 (C/2) ---- 15 (D/3) ---- 16 (E/4) ----14 (F/5) ---- 13 (G/6)




*/

#include<bits/stdc++.h>
#include<map>
using namespace std;

class Node {
public:
    int value;
    char x;

    Node(int value, char x) {
        this -> value = value;
        this -> x = x;
    }
};

void processGraph(unordered_map<Node*, vector<Node*>> &g, int n) {

    vector<bool> visit(n, false);

    queue<Node*> q;

    for (auto it: g) {
        if (it.first -> value == 16) {

            q.push(it.first);
            (it.first -> value)--;
            visit[it.first -> x - 'A'] = true;
        }
    }    
    
    // // get sources
    // while(!q.empty()) {
        
    //     Node* f = q.front();
    //     q.pop();
        
    //     cout << f -> x << " " << f -> value << "\n";
    // }
    


    // // print visited
    // cout << "visit: \n";
    // for (int i = 0 ; i < n ; i++) {
    //     cout << char('A' + i) << " "; 
    // }
    // cout << "\n";
    
    // for (int i = 0 ; i < n ; i++) {
    //     cout << visit[i] << " "; 
    // }
    // cout << "\n";

    while (!q.empty()) {

        Node* f = q.front();
        q.pop();

        for (auto it: g[f]) {

            if (visit[it -> x - 'A'])
                continue;

            
            visit[it -> x - 'A'] = true;
            it -> value = f -> value - 1;
            q.push(it);            
        }        
    }
    
    // // print visted
    // cout << "visit: \n";
    // for (int i = 0 ; i < n ; i++) {
    //     cout << char('A' + i) << " "; 
    // }
    // cout << "\n";
    
    // for (int i = 0 ; i < n ; i++) {
    //     cout << visit[i] << " "; 
    // }
    // cout << "\n";
    
    // for (auto it: g) {
    //     cout << it.first -> x << " -> " << it.first -> value << "\n";
    // }
    // cout << "\n";

    // return 0;
}

void printGraph(unordered_map<Node*, vector<Node*>> g) {

    for (auto it: g) {

        cout << it.first -> x << " -> " << it.first -> value << "\n";
    }
    cout << "\n";
}


int main() {



    int n, e;
    // cin >> n >> e;



// // tc1
// 7 6
// 16 0 16 0 16 0 0 
// 0 1
// 1 5 
// 2 3
// 3 4
// 4 5
// 5 6
    n = 7;
    e = 6;

    vector<int> nodeValues = { 16, 0, 16, 0, 16, 0, 0 };
    vector<vector<int>> edges = {
        { 0, 1 },
        { 1, 5 },
        { 2, 3 },
        { 3, 4 },
        { 4, 5 },
        { 5, 6 },
    };

    unordered_map<int, Node*> nodes;
    for (int i = 0 ; i < n ; i++) {
        int value = nodeValues[i];
        // cin >> value;
        nodes[i] = new Node(value, 'A' + i);
    }



    unordered_map<Node*, vector<Node*>> g;
    for (int i = 0; i < e; i++) {
        int u, v;
        // cin >> u >> v;

        u = edges[i][0];
        v = edges[i][1];

        Node* nodeU = nodes[u];
        Node* nodeV = nodes[v];

        g[nodeU].push_back(nodeV);
        g[nodeV].push_back(nodeU);
    }

    cout << "before: \n";
    printGraph(g);

    processGraph(g, n);

    cout << "after: \n";
    printGraph(g);
    

    return 0;
}