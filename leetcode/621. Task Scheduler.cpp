// 621. Task Scheduler
// https://leetcode.com/problems/task-scheduler/

class Solution {
public:
    int freqScheduling(vector<char>& tasks, int n) {

    	int freq[26];
        fill(freq, freq + 26, 0);

        // for (int i = 0 ; i < 26 ; i++) 
        //     cout << setw(2) << freq[i] << " ";
        // cout << "\n";

        int totalTasks = tasks.size();
        for (int i = 0 ; i < totalTasks ; i++)
            freq[tasks[i] - 'A']++;

        // for (int i = 0 ; i < 26 ; i++) 
        //     cout << setw(2) << freq[i] << " ";
        // cout << "\n";

        // only frequency is enough, we don't have to print the order of taks
        priority_queue<int> pq;     // max heap 

        for (int i = 0 ; i < 26 ; i++) {
            if (freq[i] >  0)
                pq.push(freq[i]);
        }

        int time = 0;       // time for execution

        while (!pq.empty()) {

            int cycle = n + 1;      // cycle of cooldown
            vector<int> store;      // to store the tasks that cannot be scheduled in this cycle

            int taskCount = 0;

            // execute cycle
            while (cycle-- && !pq.empty()) {
                if (pq.top() > 1) {
                    store.push_back(pq.top() - 1);      // item scheduled and freq-1 cause now left that many execution to dp
                } 
                pq.pop();       // if freq = 1. pop. no need to store
                taskCount++;    // tasks scheduled in this
            }

            // push store back to queue after cooldown
            for (int x: store) {
                pq.push(x);
            }

            // if queue is empty, then only the current task count 
            // else the cycle is the time passed
            time += (pq.empty() ? taskCount : n + 1);
        }

        // return time passed for execution
        return time;
    }


    int fillSlotsAndSorting(vector<char>& tasks, int n) {

    	vector<int> freq(26, 0);

    	// get freq
    	for (char task: tasks) {
    		freq[task - 'A']++;
    	}

    	// sort in non-decreasing order
    	sort(freq.begin(), freq.end());

    	// get max freq
    	int maxFreq = freq[25] - 1;
    	// no of idle slots to be required
    	int idleSlots = maxFreq * n;		// A - - - A - - - A for n=3 (cooldown)

    	// iterate over frequency from second highest to lowest freq
    	for (int i = 24 ; i >= 0 ; i--) {

    		// you can only schedule them in between the windows
    		// or the max freq of these items
    		// they would always fit in between
    		// or maybe just one more if freq is equal
    		// one of those frequency is left
    		// A B -- A B -- A B 
    		idleSlots -= min(maxFreq, freq[i]);
    	}

    	// if idle slots left, add them to number of tasks = their last execution
    	// or just the number of tasks
    	return idleSlots > 0 ? idleSlots + tasks.size() : tasks.size();
    }


    int greedy(vector<char>& tasks, int n) {

    	vector<int> freq(26, 0);

    	int maxFreq = 0;		// max freq
    	int maxCount = 0;		// no of items with maxFreq
    	
    	for (char task: tasks) {
    		freq[task - 'A']++;

    		if (maxFreq == freq[task - 'A']) {
    			maxCount++;
    		}
    		else if (maxFreq < freq[task - 'A']) {
    			maxFreq = freq[task - 'A'];
    			maxCount = 1;
    		}
    	}

    	// middle parts in between that are empty
    	// in case of multiple items being max freq
    	// this becomes a joint task of that many items
    	int partCount = maxFreq - 1;

    	// if single item - n items in between 
    	// if multiple - n - (maxcount - 1) items in between 
    	// ex. A = 3, B = 2, n = 2 => A - - A - - A 		| partLen = 2 - (1 - 1) = 2
    	// ex. A = 3, B = 3, n = 2 => A B - A B - A B 		| partLen = 2 - (2 - 1) = 1
    	int partLength = n - (maxCount - 1);

    	// total empty slots in between
    	int emptySlots = partCount * partLength;

    	// remove the tasks scheduled (the max freq one)
    	// from the total tasks
    	int availableTasks = tasks.size() - (maxFreq * maxCount);	
    	
    	// find the no of tasks that are still left idle
    	int idles = max(0, emptySlots - availableTasks);

    	// return the number of items
    	// which would be the number of tasks and total idles
    	return tasks.size() + idles;
    }


    int mathFormula(vector<char>& tasks, int n) {

    	vector<int> freq(26, 0);
    	int maxFreq = 0;

    	for (char task: tasks) {
    		freq[task - 'A']++;
    		maxFreq = max(maxFreq, freq[task - 'A']);
    	}

    	// get total time needed for execution
    	// scheduled (maxFreq-1) iteration of task
    	// last iteration i sleft
    	int time = (maxFreq - 1) * (n + 1);

    	for (int f: freq) {

    		// if max freq
    		if (f == maxFreq) {
    			time++;		// only increase time for those max freq counts
			    			// last round of scheduling
    		}
    	}

    	// total time needed
    	return max((int)tasks.size(), time);
    }


    int leastInterval(vector<char>& tasks, int n) {
        
        // return freqScheduling(tasks, n);

        // return fillSlotsAndSorting(tasks, n);

        // return greedy(tasks, n);

        return mathFormula(tasks, n);
    }
};