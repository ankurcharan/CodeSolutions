// 460. LFU Cache
// https://leetcode.com/problems/lfu-cache/description/

class LFUCache {


	// key: frequency
	// vallue = list of kv pair that have same frequency
	unordered_map<int, list<pair<int, int>>> frequencies;

	// key: original key
	// value: pair (frequency, iterator to corresponding key in frequencies map list
	unordered_map<int, pair<int, list<pair<int, int>>::iterator>> cache;

	int capacity;
	int minFreq;
public:
    LFUCache(int capacity) {
    	this -> capacity = capacity;
    	this -> minFreq = 0;
    }
    
    int get(int key) {
        
        const auto it = cache.find(key);

        // key not present
        if (it == cache.end()) {
        	return -1;
        }

        // get frequency
        const int f = it -> second.first;
    
    	// list iterator
        const auto iter = it -> second.second;
    	
    	// list item - key value pair of item
    	const pair<int, int> kv = *iter;

    	frequencies[f].erase(iter);

    	if (frequencies[f].empty()) {

    		frequencies.erase(f);
    		
    		if (minFreq == f) {
    			++minFreq;
    		}
    	}

    	insert(key, f + 1, kv.second);
    	return kv.second;
    }
    
    void put(int key, int value) {

    	if (capacity <= 0)
    		return;

    	const auto it = cache.find(key);
    	
    	// key already exists
    	if (it != cache.end()) {

    		pair<int, list<pair<int, int>>::iterator>& cacheValue = it -> second;

    		list<pair<int, int>>::iterator toList = cacheValue.second;

    		// update value
    		toList -> second = value;

    		// update from key
    		get(key);

    		return;
    	}


    	// capacity is already at max size
    	// so you have to delete the min freq element
    	if (cache.size() == capacity) {

    		// find list of elements of min freq
    		list<pair<int, int>>& minFreqElementList = frequencies[minFreq];
    		
    		// first element of that frequency
    		int minFreqElement = minFreqElementList.front().first;

    		// delete element from cache
    		cache.erase(minFreqElement);

    		// delete the element from list
    		minFreqElementList.pop_front();

    		// removed last element
    		if (minFreqElementList.empty()) {

    			// delete the frequency hashmap
    			frequencies.erase(minFreq);
    		}
    	}

    	minFreq = 1;		// new value
    	insert(key, 1, value);
    }

    void insert(int key, int frequency, int value) {

    	// add value for that freq
    	frequencies[frequency].push_back({ key, value });

    	// update cache
    	cache[key] = { frequency, --frequencies[frequency].end() };
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */