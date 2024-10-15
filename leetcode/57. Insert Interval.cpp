// 57. Insert Interval
// https://leetcode.com/problems/insert-interval/description/

class Solution {
public:

	vector<vector<int>> linearSearch(vector<vector<int>>& intervals, vector<int>& newInterval) {

		int n = intervals.size();
		vector<vector<int>> intervalsMod;

		int i = 0;
		// intervals before new interval
		while (i < n && intervals[i][1] < newInterval[0]) {
			intervalsMod.push_back(intervals[i]);
			i++;
		}

		// overlapping interval
		while (i < n && newInterval[1] >= intervals[i][0]) {
			newInterval[0] = min(newInterval[0], intervals[i][0]);
			newInterval[1] = max(newInterval[1], intervals[i][1]);
			i++;
		}
		intervalsMod.push_back(newInterval);


		while (i < n)
			intervalsMod.push_back(intervals[i]), i++;

		return intervalsMod;
	}

	vector<vector<int>> binarySearch(vector<vector<int>>& intervals, vector<int>& newInterval) {

		if (intervals.empty()) {
			return { newInterval };
		}

		int n = intervals.size();
		int target = newInterval[0];

		int l = 0;
		int h = n - 1;
		while (l <= h) {

			int mid = l + (h-l) / 2;

			if (intervals[mid][0] < target) 
				l = mid + 1;
			else 
				h = mid - 1;
		}

		intervals.insert(intervals.begin() + l, newInterval);

		vector<vector<int>> res;
		for (const auto& interval: intervals) {

			if (res.empty() || res.back()[1] < interval[0])
				res.push_back(interval);
			else
				res.back()[1] = max(res.back()[1], interval[1]);
		}

		return res;
	}

	vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {

		// return linearSearch(intervals, newInterval);

		return binarySearch(intervals, newInterval);
	}
};

