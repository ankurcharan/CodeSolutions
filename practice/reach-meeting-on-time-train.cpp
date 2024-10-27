// reach-meeting-on-time-train

/*
You are given a table representing a train schedule

Train#	DepartureCity	DepartureTime	ArrivalCity	ArrivalTime
0		BOS				09:30			MTL			16:00
1 		BOS				10:00			NYC			14:00
2		NYC				13:30			DC 			15:30
3 		NYC				14:30 			DC 			16:30
4		DC 				15:00 			NYC 		18:00
5		DC 				16:00 			ATL 		22:00

I'm given city at a given time. I have meeting in some other city at some other time. 
Given schedule of trains above, can I make it to my meeting on time?

*/

#include <bits/stdc++.h>
using namespace std;

void createGraph(vector<pair<pair<string, string>, pair<int, int>>>& trains, unordered_map<string, vector<pair<int, pair<int, string>>>>& g) {
	
        for (pair<pair<string, string>, pair<int, int>>& t: trains) {   
            g[t.first.first].push_back({ t.second.first, { t.second.second, t.first.second } });
        }
    
        for (auto it: g) {
            
            cout << it.first << " = ";
            for (auto x: it.second) {
                cout << "(" << x.first << ", " << x.second.first << ", " << x.second.second << ") - ";
            }
            cout << "\n";
        }
}

class djikstraCmp {
public:
    bool operator()(pair<int, string>& a, pair<int, string>& b) {
    
        return a.first > b.first;
    }
};

bool canMakeOnTime(unordered_map<string, vector<pair<int, pair<int, string>>>>& g, string srcCity, int srcTime, 
                  string destCity, int destTime) {
    
    // (time, city)
    priority_queue<pair<int, string>, vector<pair<int, string>>, djikstraCmp> pq;
    
    pq.push({ srcTime, srcCity });
    
    while (!pq.empty()) {
        
        pair<int, string> f = pq.top();
        pq.pop();
        
        cout << "pop: " << f.first << " at " << f.second << "\n";
        
        if (f.first > destTime)
            continue;
        
        if (f.second.compare(destCity) == 0) {
            return f.first <= destTime;
        }
        
        for (auto it: g[f.second]) {
            
            if (it.first >= f.first) {
                
                pq.push({ it.second.first, it.second.second });
            }
        }
    }
    
    return false;
}

class djikstraCmpWithDays {
public:
    bool operator()(pair<int, pair<int, string>>& a, pair<int, pair<int, string>>& b) {
    
    	if (a.first == b.first) {
    		return a.second.first > b.second.first;
    	}

        return a.first > b.first;
    }
};

bool canMakeOnTimeWithMoreDays(unordered_map<string, vector<pair<int, pair<int, string>>>>& g, string srcCity, int srcDay, int srcTime, 
                  string destCity, int destDay, int destTime) {

	// (day, (time, city))
    priority_queue<pair<int, pair<int, string>>, vector<pair<int, pair<int, string>>>, djikstraCmpWithDays> pq;	

    pq.push({ srcDay, { srcTime, srcCity } });

    while (!pq.empty()) {

    	pair<int, pair<int, string>> f = pq.top();
    	pq.pop();
        
        cout << "pop: " << f.first << " th day, time: " << f.second.first << ", city: " << f.second.second << "\n";

    	if (f.first > destDay)
    		continue;
    	if (f.first == destDay && f.second.first > destTime)
    		continue;

    	if (f.second.second == destCity) {

    		if (f.first < destDay)
    			return true;
    		if (f.first == destDay)
    			return f.second.first <= destTime;
    	}

        // cout << "pushing\n";
    	for (auto it: g[f.second.second]) {

    		// time is less than current time
    		// can take this train next day
    		if (it.first < f.second.first) {

                cout << "push: day: " << f.first + 1 << ", time: " << it.second.first << ", city: " << it.second.second << "\n";
    			pq.push({ f.first + 1, { it.second.first, it.second.second } });
    		}
            // same day 
            else {
                cout << "push: day: " << f.first << ", time: " << it.second.first << ", city: " << it.second.second << "\n";
                pq.push({ f.first, { it.second.first, it.second.second } });
            }
    	}
    }


    return false;
}


int main() {


	// (src city, dest city) - (src time, dest time)
	vector<pair<pair<string, string>, pair<int, int>>> trains = {

		{ { "BOS", "MTL" }, {  930, 1600 } },
		{ { "BOS", "NYC" }, { 1000, 1400 } },
		{ { "NYC", "DC"  }, { 1330, 1530 } },
		{ { "NYC", "DC"  }, { 1430, 1630 } },
		{ { "DC", "NYC"  }, { 1500, 1800 } },
		{ { "DC", "ATL"  }, { 1600, 2200 } }
	};

	// each node will store list of 
	// srcCity = [(startTime, (destTime, destCity))]
	unordered_map<string, vector<pair<int, pair<int, string>>>> g;

	createGraph(trains, g);

    // string srcCity = "BOS";
	// int srcTime = 900;
	// string destCity = "MTL";
	// int destTime = 1600;
    
	// bool ans = canMakeOnTime(g, srcCity, srcTime, destCity, destTime);
    // cout << "travel: " << srcCity << " (" << srcTime << ") " << destCity << " (" << destTime << ") = " << boolalpha << ans << endl;








	// follow up with number of days
	string srcCity = "BOS";
	int srcTime = 900;
	int srcDay = 0;
	string destCity = "MTL";
	int destTime = 1500;
	int destDay = 0;
    
	bool ans = canMakeOnTimeWithMoreDays(g, srcCity, srcDay, srcTime, destCity, destDay, destTime);
    cout << "\ntravel: " << srcCity << " (" << srcTime << ") " << destCity << " (" << destTime << ") = " << boolalpha << ans << endl;






	return 0;
}