// 895. Maximum Frequency Stack
// https://leetcode.com/problems/maximum-frequency-stack/description/

class FreqStack {

	// frequency, (position, value)
	priority_queue<pair<int, pair<int, int>>> pq;

	// freq of each key
	unordered_map<int, int> freq;

	int position = 0;		// insertion position 
public:
    FreqStack() {
        
    }
    
    void push(int val) {
        
        freq[val]++;
        position++;

        pq.push({ freq[val], { position, val } });
    }
    
    int pop() {
        
        pair<int, pair<int, int>> f = pq.top();
        pq.pop();

        int value = f.second.second;
        freq[value]--;

        return value;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */