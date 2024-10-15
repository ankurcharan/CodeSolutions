// 134. Gas Station
// https://leetcode.com/problems/gas-station/description/

class Solution {
public:
	bool completePossible(vector<int>& gas, vector<int>& cost, int start) {

		int n = gas.size();
		int i = start;

		int gasCurr = gas[i] - cost[i];
		i = (i + 1) % n;

		while (i != start) {

			if (gasCurr <= 0)
				return false;

			gasCurr += (gas[i] - cost[i]);
			i = (i + 1) % n;
		}

        if (gasCurr < 0)
            return false;

		return true;
	}

	int bruteforce(vector<int>& gas, vector<int>& cost) {

		int n = gas.size();

		for (int i = 0 ; i < n ; i++) {
			if (completePossible(gas, cost, i))
				return i;
		}

		return -1;
	}

    int queueSoln(vector<int>& gas, vector<int>& cost) {

        int n = gas.size();
    	int start = 0;
    	int end = 1 % n;	

    	int currGas = gas[start] - cost[start];		// start included

    	while (end != start || currGas < 0) {

    		while (currGas < 0) { // && start != end

    			currGas -= gas[start] - cost[start];
    			start = (start + 1) % n;

    			if (start == 0)		// returned back 
    				return -1;
    		}

    		currGas += gas[end] - cost[end];
    		end = (end + 1) % n;
    	}

    	return start;
    }


    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
     
    	// return bruteforce (gas, cost);   

    	return queueSoln(gas, cost);
    }
};