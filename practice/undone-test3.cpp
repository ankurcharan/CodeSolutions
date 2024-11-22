#include <bits/stdc++.h>
using namespace std;

// Function to calculate the minimum connection cost for each query
vector<long> getMinConnectionCost(vector<int>& warehouseCapacity, vector<vector<int>>& additionalHubs) {
    int n = warehouseCapacity.size();
    int q = additionalHubs.size();
    vector<long> result(q);

    // Precompute prefix and suffix minimum connection costs
    vector<long> prefixMin(n, LONG_MAX), suffixMin(n, LONG_MAX);
    
    // Compute prefix minimum cost for central hub
    prefixMin[0] = warehouseCapacity[n - 1] - warehouseCapacity[0];
    for (int i = 1; i < n; ++i) {
        prefixMin[i] = min(prefixMin[i - 1], (long)(warehouseCapacity[n - 1] - warehouseCapacity[i]));
    }

    // Compute suffix minimum cost for central hub
    suffixMin[n - 1] = warehouseCapacity[n - 1] - warehouseCapacity[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        suffixMin[i] = min(suffixMin[i + 1], (long)(warehouseCapacity[n - 1] - warehouseCapacity[i]));
    }

    // Process each query
    for (int k = 0; k < q; ++k) {
        int hubA = additionalHubs[k][0] - 1; // Convert to 0-based index
        int hubB = additionalHubs[k][1] - 1;

        // Include the two additional hubs
        vector<int> hubs = {hubA, hubB};
        sort(hubs.begin(), hubs.end());

        // Calculate the total connection cost
        long totalCost = 0;

        for (int i = 0; i < n; ++i) {
            // Find the minimum cost using precomputed values
            long minCost = LONG_MAX;

            // Central hub cost
            minCost = min(minCost, warehouseCapacity[n - 1] - warehouseCapacity[i]);

            // Additional hub costs
            for (int hub : hubs) {
                if (hub >= i) {
                    minCost = min(minCost, (long)(warehouseCapacity[hub] - warehouseCapacity[i]));
                    break; // Since hubs are sorted, stop early
                }
            }

            totalCost += minCost;
        }

        result[k] = totalCost;
    }

    return result;
}

// Driver code for testing
int main() {
    vector<int> warehouseCapacity = {0, 2, 5, 9, 12, 18};
    vector<vector<int>> additionalHubs = {{2, 5}, {1, 3}};

    vector<long> result = getMinConnectionCost(warehouseCapacity, additionalHubs);

    for (long cost : result) {
        cout << cost << endl;
    }

    return 0;
}