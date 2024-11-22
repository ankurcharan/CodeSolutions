// find-last-index
// https://leetcode.com/discuss/interview-question/4878831/Google-onsite-question

/*


Given an array with N integers, 
starting index S and a value X. You are playing game in which you start from S 
and first move is always odd. If the move is odd you can jump to 
first index on the left which has value A[idx]+1. If the move is even you the same on right side. 
Whenever we make a jump update the previous position by X. 
Output the end position when you can not make any jump. 
If the game is going to be infinite return -1 or return the end index.


From example


A = [3,4,2,2,7]
X = 4
S=2


we are at index 2, A[2] = 2; move is odd 2+1=3 exists at index 0 Array will become this
3,4,6,2,7
Now we are at index 0, make a jump because 4 exists on right (even move)


7,4,6,2,7
Now at index 1 4+1 5 doesnt exist on the right of 5


Answer is 1 final index.


A = [2,1]
X = 2
S = 1


This is an infinite case.


*/

// CHECK COMMENTS AND DISCUSSIONS


#include<bits/stdc++.h>
using namespace std;

int getNextIndex(vector<int>& a, int& direction, int index, unordered_map<int, set<int>>& numLook) {

    cout << index << " towards " << (direction == -1 ? "left" : "right") << "\n"; 
    
	int nextValue = a[index] + 1;

	if (numLook.find(nextValue) == numLook.end()) 
		return -1;		// not able to move

	// numLook, vector value would be sorted by value and value is index

	// left movement
	if (direction == -1) {

		auto it = lower_bound(numLook[nextValue].begin(), numLook[nextValue].end(), index);
		if (it == numLook[nextValue].begin()) {
			return -1;		// not prev element
		}

		return *prev(it);
	} 
	// right movement
	else {

		auto it = upper_bound(numLook[nextValue].begin(), numLook[nextValue].end(), index);
		if (it == numLook[nextValue].end()) {
			return -1;		// not next value
		}

		return *it;
	}

}

void updateValues(vector<int> &a, int index, int x, unordered_map<int, set<int>>& numLook) {

    if (numLook.find(a[index]) == numLook.end())
        return;
    
    int oldValue = a[index];
    
	numLook[a[index]].erase(index);
	a[index] += x;
	numLook[a[index]].insert(index);
}

void print(vector<int>& a) {
    
    int n = a.size();
    
    for (int i = 0 ; i < n ; i++) {
        cout << setw(2) << a[i] << " ";
    }
    cout << "\n";
}


int getLastIndex(vector<int> &a, int s, int x, int initDirection = -1) {

	unordered_map<int, set<int>> numLook;

	int valueMax = INT_MIN;
	int n = a.size();

	for (int i = 0 ; i < n ; i++) {

		// get max value of array
		valueMax = max(valueMax, a[i]);

		// add indexes of a certain element
		numLook[a[i]].insert(i);
	}

	int direction = initDirection;	// direction of movement. -1 = left | +1 = right
	int index = s;		// start index
	int currNum = a[s];	// curr number
    
    print(a);

	// that means all of your values would be visited
	// because
	// valueMax is the max value of array
	// so when you visit this, you will make this valueMax + x
	// every other value < valueMax, so when you add +x to it, 
	// value+x < valueMax+x
	while (currNum <= (valueMax + x)) {

		int nextIndex = getNextIndex(a, direction, index, numLook);
        
        cout << index << " moves to " << nextIndex << "\n";

		if (nextIndex == -1) {
			// no possible move
			return index;
		}

		updateValues(a, index, x, numLook);
		currNum++;
		index = nextIndex;
        
        direction *= -1;
        
        print(a);
	}

	return -1;		// infinite numbers
}


int main() {

	vector<int> v = { 3 , 4 , 2 , 2 , 7 };
	int x = 4;
	int s = 2;

	int li = getLastIndex(v, s, x);
    cout << "lastIndex: " << li << "\n";
    
    



    
    
    
    // vector<int> v = { 2, 1 };
	// int x = 2;
	// int s = 1;

	// int li = getLastIndex(v, s, x);
    // cout << "lastIndex: " << li << "\n";

    




        
        
    // vector<int> v = { 1, 1000, 2 };
	// int x = 2;
	// int s = 0;
    
    

	// int li = getLastIndex(v, s, x, 1);
    // cout << "lastIndex: " << li << "\n";
	return 0;
}





/*


If X is odd, then there's guaranteed to be no cycle. 
The proof is not straightforward but I'll try to simplify it - Proof by contradiction


Let's say we start with some index and visit indices in the array as described above, 
but at some point we will visit an already visited index again. 
Let's consider the first time this happens. 

Then, the path from the last visit of this index up to the current one 
is a simple cycle (no repetitions, as we're considering the first index which we encountered twice)

Since X is odd, then length of this cycle must also be odd - since the visited index 
was incremented by X in the last visit, 
and the difference in values of successive nodes we visit is exactly equal to one, 
when we visit this node, we must have visited an even number of indices after it's last visit.

Now, when we're at this index, our direction is opposite to what it was at this index in the last visit, 
and hence we're not going to visit the next node in the cycle in any case. 
Let's say value of our current index is a[indx], then value of the next index in the cycle would be a[indx]+1, 

but we're not going to visit this index now. So, let's say we visit an 
index in the opposite direction having value a[indx]+1. 
Then that would mean that the next index in the cycle would never be visited again, 
because it doesn't have value greater than a[indx]+1.

So, every time we discover a cycle, we rule out an index from the 
set of possible indices we could visit next. 
This way, all indices are ruled out at one point

What this also implies is that if X is even, and if we visit an index again, 
then we've found an infinite cycle and we return -1.

2
Hide 6 replies
Reply
Share
Report
siddharthjoshi120's avatar
siddharthjoshi120

11
Last Edit: April 14, 2024 9:02 PM

Read More
I'll first explain the intuition behind this condition before giving a formal proof - 
we want to reach a stage where we can bound the values for all the positions in the array. 

Imagine an array like this [1 1000 2] and S = 1, X = 2, we're facing right initially. 
Then we visit 2, turn left, visit 3, and so on... until we reach this state 
[999 1000 1000] and we're at 999, facing right. 

In this case, we won't visit the last index of the array, 
instead we would visit the 1000 in the middle of the array. 

So, the cyclic pattern could break when the positions in the current cycle have reached a certain value, 

precisely when there's an element that hasn't been visited yet whose value is equal to the current value plus one.


Now, coming to a formal proof - let's call arr_max the maximum value among all the elements 
in the original array. 
Consider the stage when curr_val = arr_max, 
we claim that all values in the array must be < arr_max + X 

at this point. 
If there was an element with value >= arr_max + X, 
then there are two scenarios: 

Either we visited this element at least once before, 
or haven't visited it at all. 

In the latter scenario, the original value of this element is >= arr_max + X, 
which is not possible as arr_max is the largest value in the original array by our assumption and 
X >= 1. 

In the former scenario, 
we visited this element at least once before, 
then at that point curr_val must be >= arr_max (*as curr_val + X will be the new value of this element) 

but this is also not possible as we're currently having curr_val = arr_max and 
clearly at any previous stage, 
curr_val must have been smaller. 

This proves our claim.


Finally, we'll make use of this claim. 
We're currently having curr_val = arr_max. 

Now, when we jump to arr_max + 1 (if there's such a value), 
all the elements with value <= arr_max + 1 excluding the index we jump to, 

become unvisitable. 

The value of the previous index (from which we jumped) becomes equal to arr_max + X. 

Next, we jump to arr_max + 2 (if there's such a value) and value of previous index becomes arr_max + 1 + X, 

and so on. 

Notice that after X jumps, if there's an index we didn't jump to, 
it's value remains < arr_max + X and hence is unvisitable. 

The remaining indices however have all distinct values, given by 
{arr_max + X, arr_max + X + 1,..., arr_max + 2*X - 1} 
and if we made it so far, 
if we're facing in the same direction as when we started, this cycle will go on forever. 

Thus it suffices to check until arr_max + X + 1 operations.

1
Reply
Share
Report
siddharthjoshi120's avatar
siddharthjoshi120

11
April 14, 2024 8:31 PM

Read More
@sarveshchavan777 I have another example, ... 3 ... 1 ... 2, 

we're starting at 1, 
initially facing right and X = 3. 

We jump to 2, 
turn left, then jump to 3, 
turn right and jump back to 4 (the starting index). ... 6 ... 4 ... 5. 

Now, we're facing left and won't jump back to 5.


My statement holds true only when we revisit an index, however, 
in the example you gave, we're not revisiting any index.

Actually, there's another statement that's wrong in my proof - 
"What this also implies is that if X is even, 
and if we visit an index again, 

then we've found an infinite cycle and we return -1." 
Please read my next comment for explanation of my final solution.

*/