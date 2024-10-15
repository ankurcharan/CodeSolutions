// 981. Time Based Key-Value Store
// https://leetcode.com/problems/time-based-key-value-store/description/

class TimeMap {
private:
	unordered_map<string, vector<pair<int, string>>> m;
public:
    TimeMap() {
        m.clear();
    }
    
    void set(string key, string value, int timestamp) {
        
        m[key].push_back({ timestamp, value });
    }
    
    string get(string key, int timestamp) {
        
        // bool d = false;
        // if (timestamp == 20)
        //     d = true;

    	if (m.find(key) == m.end())
    		return "";		// not found

    	int l = 0;
    	int r = m[key].size() - 1;
    	string ans = "";

    	while (l <= r) {

    		int mid = l + (r - l) / 2;

            // if (d)
            //     cout << "l: " << l << " , r: " << r << " -- mid: " << mid << "\n";

    		if (m[key][mid].first <= timestamp)
    		{
    			ans = m[key][mid].second;
    			l = mid + 1;
    		}
    		else
    			r = mid - 1;
    	}

    	return ans;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */