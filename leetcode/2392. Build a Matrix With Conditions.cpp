// 2392. Build a Matrix With Conditions
// https://leetcode.com/problems/build-a-matrix-with-conditions/



class Solution {
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        
        vector<int> rowOrder = topoSort(rowConditions, k);
        vector<int> colOrder = topoSort(colConditions, k);

        if (rowOrder.empty() || colOrder.empty())
            return {};

        vector<vector<int>> matrix(k, vector<int> (k, 0));

        for (int i = 0 ; i < k ; i++) {
            for (int j = 0 ; j < k ; j++) {

                if (rowOrder[i] == colOrder[j]) {
                    matrix[i][j] = rowOrder[i];
                }
            }
        }

        return matrix;
    }

    vector<int> topoSort(vector<vector<int>> &edges, int n) {

        vector<vector<int>> adj(n + 1);

        vector<int> order;

        vector<int> visited(n + 1, 0);
        bool hasCycle = false;

        for (auto &x: edges) {
            adj[x[0]].push_back(x[1]);
        }

        for (int i = 1 ; i <= n ; i++) {

            if (visited[i] == 0) {

                dfs(i, adj, visited, order, hasCycle);
                
                if (hasCycle)   return {};
            }
        }

        reverse(order.begin(), order.end());
        return order;
    }

    void dfs(int node, vector<vector<int>> &adj, vector<int> &visited, vector<int> &order, bool &hasCycle) {

        visited[node] = 1;

        for (int neighbour: adj[node]) {

            if (visited[neighbour] == 0) {
                dfs(neighbour, adj, visited, order, hasCycle);
            
                if (hasCycle)   return;
            }
            else if (visited[neighbour] == 1) {
                // cycle detected
                hasCycle = 1;
                return;
            }
        }

        visited[node] = 2;
        order.push_back(node);
    }
};