// houses-in-neighbourhood
// https://leetcode.com/discuss/interview-question/4949834/Google-or-SDE2-or-Phone-Screen


/*

Google | SDE2 | Phone Screen









you are given an array of houses in a neighboorhood in a city.
you have to rearrange houses in such a way that in a single neighbourhood 
the houses are sorted by number in ascending order and no 2 houses with same number are in same neighbourhood.
you can only rearrange house based on the capacity of each neighbourhood . 
If neighbourhood "1" in input has 2 houses then at output also it can only have 2 houses.


For example-
{
{1,2},
{4,4,7,8},
{4,9,9,9}
}


becomes
{
{4,9},
{1,2,4,9},
{4,7,8,9}
}


can someone suggest what should be the optimal solution for this.
Thanks in advance.


My Solution was :
1)Use a hashmap in java to get the frequency count of each house number.
2)use a priorityqueue to store the houses
-based on there frequency
-if frequency is same then smaller number house should be placed before
In above example 4 number house has 3 frequency and 9 number house also has 3 frequency
so we will first pick 4 and allocate it to all the neighbourhood then do the same for others.
At the end sort the neighbourhood array once again.
I faced rejection in the interview .
I was able to code the entire solution .
I was given 35 minutes for this question .
Can someone think of another approach ?

*/

#include<bits/stdc++.h>
using namespace std;


// neighborhood = 	[street1, street2, street3, street4, ...]
// street = 		[house1, house2, house3, house4, ...]


// (frequency, houseNumber)
class cmp {
public:
    bool operator()(pair<int, int>& a, pair<int, int>& b) {

        if (a.first == b.first) {
            return a.second > b.second;
        }

        return a.first < b.first;
    }    
};


bool rearrangeHouse(vector<vector<int>>& a) {

	int n = a.size();
	if (n == 0)		return false;
    // do not check for column size cause each row
    // can have different size

	// hold the count of houses whose freq is equal to 
	// the number of neighbourhoods (n)
	int maxFreqHouses = 0;

	// hold the length of min size 
	// basically min sized neighborhood
	int minStreetLength = a[0].size();

	unordered_map<int, int> f;
	for (int i = 0 ; i < n ; i++) {

        int m = a[i].size();
		minStreetLength = min(minStreetLength, m);

		for (int j = 0 ; j < m ; j++) {

			f[a[i][j]]++;

			if (f[a[i][j]] == n)
				maxFreqHouses++;

			if (f[a[i][j]] > n)
				return false;
		}
	}

	// max freq length house has to be ordered in each of 
	// the neighborhood
	// so maxFreqHouses i.e freq = n 
	// cannot be more then the min street length
	if (maxFreqHouses > minStreetLength)
		return false;

	// re-arrange the house according to frequency
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

	for (unordered_map<int, int>::iterator it = f.begin() ; it != f.end() ; ++it) {
		pq.push({ it -> second, it -> first });
	}

	// checking priority queue
    // put values in the matrix
    int columnIndex = 0;
    int rowIndex = 0;
    int count = 0;
    while (!pq.empty()) {

		pair<int, int> x = pq.top();
		pq.pop();

		cout << x.first << " " << x.second << "\n";
	
        while (x.first) {
            
            if (columnIndex < a[rowIndex].size()) {
                a[rowIndex][columnIndex] = x.second;    
                count++;
                x.first--;
            }
            
            rowIndex++;
            if (rowIndex == n) {
                rowIndex = 0;
                columnIndex+= 1;
            }
        }
    }
    
    cout << "count: " << count << "\n";
    


	return true;
}

int main() {

	vector<vector<int>> a = {
		{ 1 , 2 },
		{ 4 , 4 , 7 , 8 },
		{ 4 , 9 , 9 , 9 }
	};

	int n = a.size();
	
	cout << "BEFORE:\n";
	for (int i = 0 ; i < n ; i++) {
        
        int m = a[i].size();
		for (int j = 0 ; j < m ; j++) {
			cout << setw(2) << a[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n";

	bool ans = rearrangeHouse(a);
    cout << "ans: " << boolalpha << ans << "\n";
    
    if (ans == false) {
        cout << "no arrangement possible.\n";
        return 0;
    }
    
	cout << "\n\nAFTER:\n";
	for (int i = 0 ; i < n ; i++) {
        
        int m = a[i].size();
        
        // sort(a[i].begin(), a[i].end());
		for (int j = 0 ; j < m ; j++) {
			cout << setw(2) << a[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n";

	return 0;
}


