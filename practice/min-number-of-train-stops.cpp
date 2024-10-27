// min-number-of-train-stops
// https://leetcode.com/discuss/interview-question/algorithms/124552/google-minimum-number-of-train-stops

/*


There are an infinite number of train stops starting from station number 0.


There are an infinite number of trains. The nth train stops at all of the k * 2^(n - 1) 
stops where k is between 0 and infinity.


When n = 1, the first train stops at stops 	0, 1, 2, 3, 4, 5, 6, etc.
When n = 2, the second train stops at stops 0, 2, 4, 6, 8, etc.
When n = 3, the third train stops at stops 	0, 4, 8, 12, etc.

Given a start station number and end station number, 
return the minimum number of stops between them. 
You can use any of the trains to get from one stop to another stop.


For example, the minimum number of stops between 
start = 1 and end = 4 is 3 
	because we can get from 1 to 2 to 4.

*/

#include <bits/stdc++.h>
using namespace std;

int minSteps(int start, int end) {

    cout << "INITIAL = start: " << start << ", end: " << end << "\n\n";
    
	int minSteps = 1;
	while (start < end) {
		
                
        int pow1 = log2(end);
		int pow2 = log2(end - start);

		cout << "pow1: " << pow1 << ", pow2: " << pow2 << "\n";

		minSteps++;

		end -= pow(2, min(pow1, pow2));
        
        cout << "start: " << start << ", end: " << end << "\n\n";
	}
    
    cout << "ENDING = start: " << start << ", end: " << end << "\n\n";

	return minSteps + end - start;
}

int main() {

	int start = 13;
	int end = 64;

	int ans = minSteps(start, end);

	cout << "ans: " <<  ans << "\n";

	return 0;
}