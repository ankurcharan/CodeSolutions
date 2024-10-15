// 146. LRU Cache
// https://leetcode.com/problems/lru-cache/description/

class LRUCache {
	int capacity;
	// (key, node in linked list)
	unordered_map<int, list<pair<int, int>>::iterator> cacheMap;

	// doubly linked list
	// (key, value)
	list<pair<int, int>> l;
public:
    LRUCache(int capacity) {
        this -> capacity = capacity;
    }
    
    int get(int key) {
        
        unordered_map<int, list<pair<int, int>>::iterator>::iterator it = cacheMap.find(key);
        if (it == cacheMap.end()) {
        	return -1;
        } 

        list<pair<int, int>>::iterator listItem = it -> second;

        int value = listItem -> second;

        l.erase(listItem);
        l.push_front({ key, value });

        cacheMap[key] = l.begin();

        return value;
    }
    
    void put(int key, int value) {
        
    	unordered_map<int, list<pair<int, int>>::iterator>::iterator it = cacheMap.find(key);
        if (it != cacheMap.end()) {

        	l.erase(it -> second);
        	cacheMap.erase(it);
        }

        l.push_front({ key, value });
        cacheMap[key] = l.begin();		// assigned from of list

        // if size is more than capacity
        if (cacheMap.size() > capacity) {

        	pair<int, int> lastElement = l.back();		// last frequently used
        												// frequently used at the front of queue

	    	l.pop_back();				// remove last element from list
        	cacheMap.erase(lastElement.first);	// remove element from list
        }		
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */