// 630. Course Schedule III
// https://leetcode.com/problems/course-schedule-iii/description/

bool cmp(vector<int>& a, vector<int>& b) {

	return a[1] < b[1];
}


class Solution {
public:

	int priorityQueue(vector<vector<int>>& courses) {

		if (courses.size() <= 0)
			return 0;

        // sort in increasing order of end time
		sort(courses.begin(), courses.end(), cmp);

		// for (int i = 0 ; i < courses.size() ; i++)
		// 	cout << courses[i][0] << ", " << courses[i][1] << endl;
		// cout << "\n";

        priority_queue<int> q;

        int sum = 0;
        for (int i = 0 ; i < courses.size() ; i++) {

            sum += courses[i][0];

            // just to get count of the events processed
            q.push(courses[i][0]);

            if (sum > courses[i][1]) {

                // cout << "pop: " << q.top() << "\n";

                // pop the longest task, so you can fit more tasks later in the window
                sum -= q.top();
                q.pop();
            }
        }

		return q.size();
	}

    int scheduleCourse(vector<vector<int>>& courses) {
        
        return priorityQueue(courses);
    }
};