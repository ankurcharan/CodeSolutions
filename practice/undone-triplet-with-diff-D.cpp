// https://leetcode.com/discuss/interview-question/4964533/Google-Phone-Interview-Question

/*

Q: There is stream of float values (-inf, inf) which is coming as input and an integer D.


We need to find a set of 3 values which satisfy condition - |a - b| <= D, |b - c| <= D, |a - c| <= D, assuming a,b,c are 3 float values. Print these 3 values and remove them and continue ....


Constraints -
All values in stream will be unique.
D -> [0, inf)


Eg:
Input stream - [1,10,7,-2,8,....], d = 5
Output - (when 8 comes, then print "7 8 10" and remove them and continue)


class Solution {
	private int D;
	void init(int d) {
		this.D = d;
	void func(float item) {
		// implement
	}
}
What data structure should be used here, and what approach can be applied?

*/

#include<bits/stdc++.h>
#include<iterator>
using namespace std;

class Solution {
	int d;
	set<float> nums;
public:
	void init(int d) {
		this -> d = d;
		this -> nums.clear();
	}

	void addingItem(float item) {

		// item is middle in triplet
		set<float>::iterator itA = nums.lower_bound(item);							// bigger element
		set<float>::iterator itB = (itA != nums.end()) ? prev(itA) : nums.end();	// smaller element
        
        cout << "MIDDLE ELEMENT\n";

		float a = (itB != nums.end()) ? *itB : 0;
		float c = (itA != nums.end()) ? *itA : 0;
        // cout << a << " , " << item << " , " << c << "\n";
        
		if (itA != nums.end() && itB != nums.end() && (item - a) <= d && (c - item) <= d) {

			// found the triplet 
			cout << "triplet: " << a << " , " << item << " , " << c << "\n";

			nums.erase(itA);
			nums.erase(itB);

			return;
		}
        
        cout << "FIRST ELEMENT\n";


		// item is first in triplet
		itA = nums.upper_bound(item);			// first element bigger than item
		itB = (itA != nums.end()) ? nums.upper_bound(*itA) : nums.end();		// greater than itA

		a = (itA != nums.end()) ? *itA : 0;
		c = (itB != nums.end()) ? *itB : 0;
        
        // cout << item << " , " << a << " , " << c << "\n";

		if (itA != nums.end() && itB != nums.end() && (a - item) <= d && (c - a) <= d) {

			// found the triplet 
			cout << "triplet: " << item << " , " << a << " , " << c << "\n";

			nums.erase(itA);
			nums.erase(itB);

			return;
		}
        
        cout << "THIRD ELEMENT\n";

		// item is third in triplet
		itA = nums.lower_bound(item);
        
        if (itA == nums.end()) cout << "end\n";
        if (itA == nums.end()) {
            
            set<float>::reverse_iterator itX = nums.rbegin();
            set<float>::reverse_iterator itC = next(itX);
            
            cout << *itC << "dsds\n";
            a = (itX != nums.rend()) ? *itX : 0;
            
            
            
            // c = (itC != nums.rend()) ? *itC : 0;
            
            // cout << *itX << " , ";
            // cout << a << " , " << c << " , " << item << "\n";

//             if (itB != nums.end() && itC != nums.end() && (item - c) <= d && (c - a) <= d) {

//                 // found the triplet 
//                 cout << "triplet: " << a << " , " << c << " , " << item << "\n";

//                 nums.erase(itB);
//                 nums.erase(itC);

//                 return;
//             }
        }
        else {
            
            itB = (itA != nums.end()) ? prev(itA) : nums.end();
            // itB = prev(itA);
            set<float>::iterator itC = (itB != nums.end()) ? prev(itB) : nums.end();

            a = (itB != nums.end()) ? *itB : 0;
            c = (itC != nums.end()) ? *itC : 0;
            
            cout << *itA << " , ";
            cout << a << " , " << c << " , " << item << "\n";

            if (itB != nums.end() && itC != nums.end() && (item - c) <= d && (c - a) <= d) {

                // found the triplet 
                cout << "triplet: " << a << " , " << c << " , " << item << "\n";

                nums.erase(itB);
                nums.erase(itC);

                return;
            }
        }
            
		
        
        
        
        // not in triplet, so insert
        nums.insert(item);
	}
};

void printTriplets(vector<int> & a, int d) {

	Solution s;
	s.init(d);

	for (int i = 0 ; i < (int)a.size() ; i++) {
		cout << "adding: " << a[i] << "\n";
		s.addingItem(a[i]);
        cout << endl;
	}
}

int main() {

//     // // NO triplet
//     vector<int> n = { 1, 10, 7, -2, 8 };
// 	int dn = 1;

// 	printTriplets(n, dn);
    
    
    
//     // // MIDDLE element
    
// 	vector<int> a = { 1, 10, 7, -2, 8 };
// 	int da = 2;

// 	printTriplets(a, da);
    
    
    
//     // FIRST element
    
//     vector<int> b = { 1, 10, 9, -2, 8 };
// 	int db = 1;

// 	printTriplets(b, db);
    
    
    
    // THIRD element
    
    vector<int> b = { 1, 8, 9, -2, 10 };
	int db = 1;

	printTriplets(b, db);
    
    
	return 0;
}













