// 155. Min Stack
// https://leetcode.com/problems/min-stack/description/

// using only one stack 

// Stack doesn’t hold the actual value of an element if it is minimum so far.
// The actual minimum element is always stored in the 'minElement' variable


/* 
PUSHING

let element to be inserted = x;
let min element yet = minElement;


if (x >= minElement)
	push to stack
else when x < minElement
	push (2 * x - minElement)

	explanation
		x < minElement
		2x < 2*minElement
		2x - minElement < minElement

	so element pushed will always be less than minimum value





POPPING

let element at top of stack = x;
let min element now = minElement

if (x >= minElement)
	pop as usual
else when x < minElement
	
	popped values = minElement  	 		this is the value that should be popped from stack
	minElement = 2 * minElement - x 		update min value to new value

	explanation:
		this works cause what is popped is 2*minimum - olderMinimum

		2 * minimum - (2 * minimum - olderMinimum) = olderMinimum
		
		and pushed element was assigned as minimum element
*/

// take care of long long values
// when doing 2x - m or 2m - t


class MinStack {
	stack<long long int> s;
	long long int minElement = INT_MAX;
public:
    MinStack() {
        
    }
    
    void push(int val) {
        
        // cout << "push: " << val << "\n";

        if (s.empty()) {
        	minElement = val;
        	s.push(val);

        	return;
        }

        if (val < minElement) {
            // cout << "modified push: "  << (two * val - minElement) << "\n";
        	s.push(2L * val - minElement);
        	minElement = val;
        }
        else
        	s.push(val);

        // cout << "minElement: " << minElement << "\n\n";
    }
    
    void pop() {
        
        if (s.empty())
        	return;

        long long int t = s.top();
        s.pop();

        if (t < minElement) {
        	minElement = 2L * minElement - t;
        }

        if (s.empty())
            minElement = INT_MAX;
    }
    
    int top() {
        
        if (s.empty())
        	return -1;

        long long int t = s.top();

        // cout << "top here: " << t << "\n";

        if (t < minElement) {

            // cout << "top: " << t << "   new: " << minElement << "\n";
        	return (int)minElement;
        }
        else 
        	return (int)t;
    }
    
    int getMin() {
        
        return (int)minElement;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 // **/