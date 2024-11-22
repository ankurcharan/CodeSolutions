
    int nq = additionalHubs.size();
    int n  = warehouseCapacity.size();

    vector<long> result(nq);
    vector<long> prefixMin(n, LONG_MAX);
    vector<long> suffixMin(n, LONG_MAX);
    
    prefixMin[0] = warehouseCapacity[n - 1] - warehouseCapacity[0];
    for (int i = 0 ; i < n ; i++) {
        prefixMin[i] = min(prefixMin[i - 1], (long(warehouseCapacity[n - 1] - warehouseCapacity[i])));
    }
    
    suffixMin[n - 1] = warehouseCapacity[n - 1] - warehouseCapacity[n - 1];
    for (int i = n - 2 ; i >= 0 ; i--) {
        suffixMin[i] = min(suffixMin[i + 1], (long)(warehouseCapacity[n - 1] - warehouseCapacity[i]));    
    }
    
    for (int i = 0 ; i < nq ; i++) {
        
        int hA = additionalHubs[i][0] - 1;
        int hB = additionalHubs[i][0] - 1;
    
        vector<int> hubs = { hA, hB, n - 1 };
        sort(hubs.begin(), hubs.end());
        
        long totalCost = 0;
        for (int i = 0 ; i < n ; i++) {
            // int warehousePos = i;
            long minCost = LONG_MAX;
         
            minCost = min(minCost, long(warehouseCapacity[n - 1] - warehouseCapacity[i]));
            
            for (int hub: hubs) {
                
                if (hub >= i) {
                    minCost = min(minCost, long(warehouseCapacity[hub] - warehouseCapacity[i]));
                }
            }
            
            totalCost += minCost;
        }
        
        result[i] = totalCost;
    }
    
    return result;