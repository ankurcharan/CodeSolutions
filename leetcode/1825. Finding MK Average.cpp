// 1825. Finding MK Average
// https://leetcode.com/problems/finding-mk-average/description/

class MKAverage {
	int m, k;
	multiset<int> low, mid, high;

	long long int sum = 0;		// sum of middle elements

	queue<int> q;

public:
    MKAverage(int m, int k) {
        
        this -> m = m;
        this -> k = k;
    }
    
    void addElement(int num) {
        
        if (low.empty() || num <= *low.rbegin())
        	low.insert(num);
        else if (high.empty() || num >= *high.begin())
        	high.insert(num);
        else {
        	mid.insert(num);
        	sum += num;
        }

        // add item to window
        q.push(num);

        // remove extra element from window
        if (q.size() > m) {

        	int f = q.front();
        	q.pop();

        	if (low.find(f) != low.end()) 
        		low.erase(low.find(f));
        	else if (high.find(f) != high.end()) 
        		high.erase(high.find(f));
        	else {
        		mid.erase(mid.find(f));
        		sum -= f;
        	}
        }


        // remove k highest elements
        while (high.size() > k) {

        	// remove first element from high and push back to mid

        	int x = *high.begin();
        	high.erase(high.begin());

        	mid.insert(x);
        	sum += x;
        }

        // you have to remove k lowest elements
        while (low.size() > k) {

        	// remove last from low and push up to mid
        	
        	int x = *low.rbegin();
        	low.erase(prev(low.end()));

        	mid.insert(x);
        	sum += x;
        }

        while (low.size() < k && mid.size() > 0) {

        	int x = *mid.begin();
        	mid.erase(mid.begin());

        	sum -= x;
        	low.insert(x);
        }

        while (high.size() < k && mid.size() > 0) {

        	int x = *mid.rbegin();
        	mid.erase(prev(mid.end()));

        	sum -= x;
        	high.insert(x);
        }
    }
    
    int calculateMKAverage() {
        
        // q.size() == m
        return q.size() < m ? -1 : sum / (q.size() - (2 * k));
    }
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */