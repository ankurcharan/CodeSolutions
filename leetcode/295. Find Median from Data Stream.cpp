// 295. Find Median from Data Stream
// https://leetcode.com/problems/find-median-from-data-stream/description/

class cmp {
public:
    bool operator()(int a, int b) {
        return a > b;       
    }
};


class MedianFinder {

	priority_queue<int> maxHeap;
	priority_queue<int, vector<int>, greater<int>>	minHeap;

    double median = 0;

public:
    MedianFinder() {     
    }
    
    void addNum(int num) {
        
        if (num < median) {
            maxHeap.push(num);
        }
        else {
            minHeap.push(num);
        }

        int x = maxHeap.size();
        int y = minHeap.size();

        if (abs(x - y) > 1) {

        	if (x > y)      // max heap has more elements
        	{
        		minHeap.push(maxHeap.top());
        		maxHeap.pop();
        	}
        	else            // mi heap has more elements 
            {
        		maxHeap.push(minHeap.top());
        		minHeap.pop();
        	}
        }

        x = maxHeap.size();
        y = minHeap.size();

        if (x == y) {
            median = (maxHeap.top() + minHeap.top()) / 2.0;
        }
        else if (x > y) {
            median = maxHeap.top();
        }
        else {
            median = minHeap.top();
        }
    }
    
    double findMedian() {
        
        return median;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */