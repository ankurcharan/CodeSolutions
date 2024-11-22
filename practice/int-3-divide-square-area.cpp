// int-3-divide-square-area
// https://leetcode.com/discuss/interview-experience/5720580/Google-or-SDE(L3)-or-BangaloreHyd-or-Aug-24/

/**
Question
	In a x-y cartesian plane, 
	squares are made with axes paralled to x-axis and y- axis, 
	their topleft corner x,y is given and edge length a is given for each,,

	we have to tell a horizontal axis that divides the area of all squares in 2 equal halves.

Example
	l = [(1, 2), (2, 4)] 		// topleft coordinates
	sizes = [5, 10] 			// edge lengths

She told me i can just give on how would i solve it, 
i don't have to code it since we didn't have enough time.


Solution
	i was able to come up with a binary search solution, 
	i felt we can take range for y coordinates ,
	then we could simple check in O(n) time for how much area is above A1 
	and how much is below the proposed axis A2 .

	this would be O(nlogy) solution.
	
The interviewer wasn't satisfied and told me to think of a better solution.
Wasn't able to do in the remaining time and she ended the round.







Later , i thought of the this solution..

It involves calculating weighted average.
	l = [(1, 2), (2, 4)]
	sizes = [5, 10]
so for each square you can assume it as point weight equal to its area at 
average of their y coordinate 
	(2+(-3)) / 2 = -0.5. 
so at y coordinate = -0.5 we can assume 25(area) weight, 
similarly at -1 a weight of 100(area)

ans =(-0.5 *25-1*100)/125 =-0.9

O(N) solution


Edit: 
	Thanks to quick observations of @sagarchapara , 
	the weighted average approach fails for many test cases and is incorrect.
	Any solutions for second question are greatly appreciated.


Verdict- Passed
 
*/


#include <bits/stdc++.h>
using namespace std;

double getWhichAreaBigger(vector<pair<double, double>>& leftmostPoints, vector<double>& sideLength, double yaxis) {

	// top
	double area1 = 0;
	
	// bottom
	double area2 = 0;

	for (int i = 0 ; i < leftmostPoints.size() ; i++) {

		long long int sqArea = sideLength[i] * sideLength[i];

		// complete bottom
		if (leftmostPoints[i].second < yaxis) {
            // cout << setw(2) << i << "    bottom\n";
			area2 += sqArea;
		}
		// complete top
		else if ((leftmostPoints[i].second - sideLength[i]) > yaxis) {
			// cout << setw(2) << i << "    upper\n";
            area1 += sqArea;
		}
		// some part up and some part down
		else {

            // cout << setw(2) << i << "    half\n";
            
			double up = (leftmostPoints[i].second - yaxis) * sideLength[i];
			area1 += up;
			area2 += sqArea - up;
		}
	}

	// cout << "yaxis: " << setw(4) << yaxis << ", area1: " << setw(3) << area1;
	// cout << ", area2: " << setw(3) << area2;
	// cout << ", diff: " << setw(4) << (area1 - area2) << "\n";

	return area1 - area2;
}

double findHorizontalAxes(vector<pair<double, double>>& leftmostPoints, vector<double>& sideLength) {

	double minY = 0;
	double maxY = 0;

	for (int i = 0 ; i < leftmostPoints.size() ; i++) {

		minY = min(minY, leftmostPoints[i].second - sideLength[i]);
		maxY = max(maxY, leftmostPoints[i].second);
	}

	cout << "blah -- minY: " << minY << ", maxY: " << maxY << "\n";

	while (minY <= maxY) {

		double mid = (minY + maxY) / 2;
        mid = round(mid * 100);
        mid = mid / 100;
        
		double diff = getWhichAreaBigger(leftmostPoints, sideLength, mid);

        cout << "minY: " << setw(3) << minY << ", maxY: " << setw(3) << maxY << ", ";
        cout << "mid: " << setw(3) << mid << ", diff: " << setw(3) << diff << "\n\n";
        
		if (diff == 0)
			return mid;
		else if (diff < 0) // move down
			maxY = mid - 0.01;
		else
			minY = mid + 0.01;
	}

	return INT_MIN;
}

double findHorizontalAxesOptimized(vector<pair<double, double>>& leftmostPoints, vector<double>& sideLength) {

	double minY = numeric_limits<double>::max();
	double maxY = numeric_limits<double>::min();

	double totalAreaOfAllSquare = 0;

	unordered_map<int, int> change;

	for (int i = 0 ; i < leftmostPoints.size() ; i++) {

		minY = min(minY, leftmostPoints[i].second - sideLength[i]);
		maxY = max(maxY, leftmostPoints[i].second);

		change[(leftmostPoints[i].second - sideLength[i]) * 10] += sideLength[i];
		change[leftmostPoints[i].second * 10] += -1 * sideLength[i];
	
		// totalAreaOfAllSquare += (sideLength[i] * sideLength[i]);
	}

	cout << "changes\n";
	for (auto it: change) {
		cout << it.first << " = " << it.second << "\n";
	}
	cout << "\n\n";


	cout << "findHorizontalAxesOptimized => minY: " << minY << ", maxY: " << maxY << "\n";
	cout << "findHorizontalAxesOptimized => totalAreaOfAllSquare: " << totalAreaOfAllSquare << "\n";
	cout << "\n\n";


	long long int prefix = 0;
	long long int sum = 0;
	for (double i = minY ; i <= maxY ; i += 0.1) {

		int mult = round(i * 10);
		cout << setw(3) << i << " = " << setw(3) << mult << " = " << change[mult] << " = " << prefix << " \n";
		
		prefix += change[mult];
		sum += prefix;
	}

	cout << "\n\nsum: total: " << sum << "\n";

	long long int halfSum = 0;
	for (double i = minY ; i <= maxY ; i += 0.1) {

		int mult = round(i * 10);
		// cout << setw(3) << i << " = " << setw(3) << mult << " = " << change[mult] << " = " << prefix << " \n";
		
		prefix += change[mult];
		halfSum += prefix;


		if (halfSum > (sum / 2)) {
			cout << endl;
			return i;
		}
	}	
	cout << endl;

	return INT_MIN;
}


int main() {
	
	// // not possible = INT_MIN
	// vector<pair<double, double>> leftmostPoints = { { 1, 2 }, { 2, 4 } };
	// vector<double> sideLength = { 5, 10 };

    
	// // ans = 0
	// vector<pair<double, double>> leftmostPoints = { { 1, 1 }, { 1, 2 } };
	// vector<double> sideLength = { 2, 4 };
    

	// // ans = 0.5    
	// vector<pair<double, double>> leftmostPoints = { { 0, 1 }, { 0, 1 } };
	// vector<double> sideLength = { 1, 1 };


	// ans = 6
	vector<pair<double, double>> leftmostPoints = { { 1, 10 }, { 2, 10 } };
	vector<double> sideLength = { 8, 8 };



	// double ans = findHorizontalAxes(leftmostPoints, sideLength);
	double ans = findHorizontalAxesOptimized(leftmostPoints, sideLength);
	cout << "ans: " << ans << endl;

	return 0;
}