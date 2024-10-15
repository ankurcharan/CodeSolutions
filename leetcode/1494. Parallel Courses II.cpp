// 1494. Parallel Courses II
// https://leetcode.com/problems/parallel-courses-ii/description/

class Solution {
public:
    int topoSortWithMaxNumberOfCourseInSem(int n, vector<vector<int>>& relations, int k) {

    	vector<int> indegree(n, 0);
        vector<int> g[n];

        for (vector<int> r: relations) {

        	g[r[0] - 1].push_back(r[1] - 1);
        	indegree[r[1] - 1]++;
        }

        // topo
        queue<int> q;

        for (int i = 0 ; i < n ; i++) {
            cout << setw(2) << i << " ";
        }
        cout << "\n";
        for (int i = 0 ; i < n ; i++) {
            cout << setw(2) << indegree[i] << " ";
        	if (indegree[i] == 0) {
                // cout << "push: " << i << "\n";
                q.push(i);
            }
        }
        cout << "\n";

        int nodesProcessed = n;
        int semesters = 0;

        while (!q.empty()) {

        	int s = ((int)q.size() > k) ? k : q.size();

            cout << "size: " << s << "\n";
        	semesters += s / k;
        	if (s % k != 0)
        		semesters += 1;

        	while(s--) {

        		int f = q.front();
        		q.pop();
                nodesProcessed--;

                cout << "push: ";
        		for (int neighbour: g[f]) {

        			indegree[neighbour]--;
        			if (indegree[neighbour] == 0) {
                        cout << neighbour << " ";
        				q.push(neighbour);
        			}
        		}
                cout << "\n";
        	}
        }

        return nodesProcessed == 0 ? semesters : -1;
    }

    
    int bitmaskSoln(int n, vector<vector<int>>& relations, int k) {

    	vector<int> d(n + 1, 0);
    	for (vector<int> r: relations) {

    		// r[0]--;
    		// r[1]--;

    		// cout << r[0] << ',' << r[1] << " = ";
    		
    		d[r[1]] |= (1 << r[0]);

    		// cout << (d[r[1]] || (1 << r[0])) << " \n";
    	}

        // for (int i = 0 ; i <= n ; i++) {
        //     bitset<5> b(d[i]); 
        //     cout << i << " = " << b.to_string() << "\n";
        // }
    	// cout << "\n";

    	// // start BFS
    	// (no of subjects covered, distance ie semesters)
    	queue<pair<int, int>> q;
    	q.push({ 0, 0 });

    	// mark 0 as visited, cause not the node. starts with 1
    	unordered_set<int> visited = { {0} };

    	while (!q.empty()) {

    		pair<int, int> f = q.front();
    		q.pop();

            // bitset<15> b(f.first);
            // cout << b.to_string() << "\n"; 

            // (1 < (n + 1))   == this will be equal to n+1 bits with highest bit set
            // 1 0 0 0 0 0 0 ... n bits 
            // -2 will subtrac
            // -1 will shift all bits = 0 1 1 1 1 1 1 1 ... n bits
            // -2 will unset the last bit = 0 1 1 1 1 1 1 1 0 
            // so all the courses are set from 1 to n 
            // i.e. all courses are taken
    		if (f.first == (1 << (n + 1)) - 2) {
    			return f.second;
    		}

    		// current chosen subjects
    		int curr = f.first;

    		int next = 0;
    		for (int i = 1 ; i <= n ; i++) {

    			// curr = currently selected subjects
    			// d[i] = subjects needed to be picked up already to pick up i-th subject
    			// this condition checks that if all the required subjects are already picked up, you can pick up the current subject

    			if ((curr & d[i]) == d[i]) {
    			
    				// pick up the i-th subject, now that conditions are met
    				next |= (1 << i);
    			}
    		}

    		// this will set only those subjects which aren't already picked up
    		// only the new ones would be set in next now
    		next = next ^ curr;

    		// next picked subjects don't crosse threshold = k
    		if (__builtin_popcount(next) <= k) {

    			// not visited already
    			if (visited.count(next | curr) == 0) {

    				visited.insert(next | curr);
    				// push the new subjects, total sem = 1 + prev sem
    				q.push({ next | curr, f.second + 1 });
    			}
    		}
    		else {

    			int x = next;
    			while (next) {

    				// bitset<5> b(next);
    				// cout << "next: " << b.to_string() << "\n";

    				// pick k subjects if bit count > k
    				if (__builtin_popcount(next) == k && !visited.count(next | curr)) {

    					visited.insert(next | curr);
    					q.push({ next | curr, 1 + f.second });
    				}

    				// reduce the subjects, find all cases of less or equal subjects
    				// this basically creates all subsequences
    				next = (next - 1) & x;
    			}
    		}
    	}

    	return 0;
    }


    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        
        // wrong answer. doesn't work. 
        // return topoSortWithMaxNumberOfCourseInSem(n, relations, k);
    
    	return bitmaskSoln(n, relations, k);
    }
};