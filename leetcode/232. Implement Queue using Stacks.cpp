// 232. Implement Queue using Stacks
// https://leetcode.com/problems/implement-queue-using-stacks/description/




////////////////////////////////////
//// 1 stack - expensive deque ////
////////////////////////////////////
// enqueue operation takes O(1) time
// while deque will be slower and in O(n)
// this will use one user stack and other recursion stack from the call

class MyQueue {
	stack<int> s;

	int getLastElement(bool pop) {

		// empty stack
		if (s.empty()) 
			return -1;

		int x = s.top();
		s.pop();

		if (s.empty())  {// last element
		
			if (pop == false) 
				s.push(x);

			return x;
		}

		int element = getLastElement(pop);
		
		// back and push its own item
		s.push(x);

		return element;		// popped or peek element
	}
public:

    MyQueue() {
    }
    
    void push(int x) {
        
        // push to stack
        s.push(x);
    }
    
    int pop() {
    
    	return getLastElement(true);
    }
    
    int peek() {
        
        return getLastElement(false);
    }
    
    bool empty() {
       
    	// return if stack is empty
		return s.empty();
    }
};






////////////////////////////////////
//// 2 stacks - expensive deque ////
////////////////////////////////////
// enqueue operation takes O(1) time
// while deque will be slower and in O(n) but amortized O(1)

// class MyQueue {
// 	stack<int> s1, s2;
// public:

//     MyQueue() {
//     }
    
//     void push(int x) {
        
//         // push to stack
//         s1.push(x);
//     }
    
//     int pop() {
    
//     	// empty queue
//     	if (s1.empty() && s2.empty())
//     		return -1;

//     	// if s2 is empty 
//     	// then only move items to s2 from s1
//     	// they will inorder they are inserted from top
//     	// then you can pop as s2.top() which is the front of the queue
//     	if (s2.empty()) {

//     		while (s1.empty() == false) {

//     			s2.push(s1.top());
//     			s1.pop();
//     		}
//     	}

//         // pop value
//         int value = s2.top();
//     	s2.pop();

//     	return value;
//     }
    
//     int peek() {
        
//         // empty stack
//         if (s1.empty() && s2.empty()) {
//         	return -1;
//         }

//         if (s2.empty()) {

//         	while (s1.empty() == false) {
//         		s2.push(s1.top());
//         		s1.pop();
//         	}
//         }

//         return s2.top();
//     }
    
//     bool empty() {
       
//     	// return if stack is empty
// 		return s1.empty() && s2.empty();
//     }
// };







//////////////////////////////////////
//// 2 stacks - expensive enqueue ////
//////////////////////////////////////
// enqueue operation takes O(n) time
// while deque will be faster and in O(1)

// class MyQueue {
// 	stack<int> s1, s2;
// public:

//     MyQueue() {
//     }
    
//     void push(int x) {
        
//         // push all values of s1 to s2
//         while (s1.empty() == false) {

//         	s2.push(s1.top());
//         	s1.pop();
//         }

//         // push element at bottom of s1
//         s1.push(x);

//         // push element back to s1 from s2
//         while (s2.empty() == false) {

//         	s1.push(s2.top());
//         	s2.pop();
//         }
//     }
    
//     int pop() {
        
//         // no values to pop
//         if (s1.empty())
//         	return -1;

//         // return top value of s1
//         int value = s1.top();
//         s1.pop();

//         return value;
//     }
    
//     int peek() {
        
//         // empty stack
//         if (s1.empty())
//         	return -1;

//         // return top element of s1
//         return s1.top();
//     }
    
//     bool empty() {
       
//     	// return if stack is empty
// 		return s1.empty();
//     }
// };

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */