// 56. Merge Intervals
// https://leetcode.com/problems/merge-intervals/description/


class Solution {
public:

	vector<vector<int>> merge(vector<vector<int>>& intervals) {

    	// return connectedComponents(intervals);

    	return sorting(intervals);
    }

    ////////////////////////////////
    //////////// Sorting ///////////
    ////////////////////////////////

    vector<vector<int>> sorting(vector<vector<int>>& intervals) {

    	sort(intervals.begin(), intervals.end());	// sorted by first, second

    	vector<vector<int>> merged;
    	for (auto interval: intervals) {

    		if (merged.empty() || merged.back()[1] < interval[0]) {
    			merged.push_back(interval);
    		}
    		else {
    			merged.back()[1] = max(merged.back()[1], interval[1]);
    		}
    	}

    	return merged;
    }

    ////////////////////////////////
    ///// Connected Components /////
    ////////////////////////////////

    vector<vector<int>> connectedComponents(vector<vector<int>>& intervals) {

		map<vector<int>, vector<vector<int>>> g;
		map<int, vector<vector<int>>> nodes_in_comp;
		set<vector<int>> visit;

		buildGraph(intervals, g);
		buildComponents(intervals, g, visit, nodes_in_comp);

		vector<vector<int>> merged;
		for (size_t comp = 0 ; comp < nodes_in_comp.size() ; comp++) {
			merged.push_back(mergeNodes(nodes_in_comp[comp]));
		}

		return merged;
	}

	bool overlappingInterval(vector<int> &a, vector<int> &b) {

		// (1, 5) - (4, 7)

		// 		1 <= 7    &&   4   <= 5 
		return a[0] <= b[1] && b[0] <= a[1];
	}

	void buildGraph(vector<vector<int>>& intervals, map<vector<int>, vector<vector<int>>>& g) {

		for (vector<int> int1: intervals) {			// interval-1
			for (vector<int> int2: intervals) {		// interval-2

				if (overlappingInterval(int1, int2)) {

					g[int1].push_back(int2);
					g[int2].push_back(int1);
				}
			}
		}
	}

	void markComponentDFS(vector<int>& start, int componentNumber, map<vector<int>, vector<vector<int>>>& g, map<int, vector<vector<int>>>& nodes_in_comp, set<vector<int>>& visit) {

		stack<vector<int>> s;
		s.push(start);

		while (!s.empty()) {

			vector<int> node = s.top();
			s.pop();

			if (visit.find(node) == visit.end()) {

				visit.insert(node);

				nodes_in_comp[componentNumber].push_back(node);

				for (auto child: g[node]) {
					s.push(child);
				}
			}
		}
	}

	void buildComponents(vector<vector<int>>& intervals, map<vector<int>, vector<vector<int>>>& g, set<vector<int>>& visit, map<int, vector<vector<int>>>& nodes_in_comp) {

		int componentNum = 0;

		for (vector<int> interval: intervals) {

			if (visit.find(interval) == visit.end())
			{
				markComponentDFS(interval, componentNum, g, nodes_in_comp, visit);
				componentNum++;
			}
		}
	}

	vector<int> mergeNodes(vector<vector<int>>& nodes) {

		int min_start = nodes[0][0];
		for (auto node: nodes) {
			min_start = min(min_start, node[0]);
		}

		int max_end = nodes[0][1];
		for (auto node: nodes) {
			max_end = max(max_end, node[1]);
		}

		return { min_start, max_end };
	}
};