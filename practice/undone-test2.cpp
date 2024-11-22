#include <bits/stdc++.h>
#include <climits>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


/*
 * Complete the 'getMinConnectionCost' function below.
 *
 * The function is expected to return a LONG_INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY warehouseCapacity
 *  2. 2D_INTEGER_ARRAY additionalHubs
 */
 
// long getSumDiff(vector<int>& warehouseCapacity, vector<long long int>& prefix, set<int>& s) {
    
//     int st = -1;
//     long sum = 0;
    
//     for (int x: s) {
        
//         if (st == -1) {
//             if (x != 0)
//                 sum += prefix[x - 1];
//         }
//         else {
//             sum += prefix[x - 1] - prefix[st];
//         }
        
//         st = x;
//     }
    
//     return sum;
// }

vector<long> getMinConnectionCost(vector<int> warehouseCapacity, vector<vector<int>> additionalHubs) {


    int nq = additionalHubs.size();
    int n  = warehouseCapacity.size();
    
    vector<long> cost(n);
    for (int i = 0 ; i < n ; i++) {
        cost[i] = warehouseCapacity[n - 1] - warehouseCapacity[i];
    }
    
    vector<long> result(nq);
    for (int i = 0 ; i < nq ; i++) {
        int hA = additionalHubs[i][0] - 1;
        int hB = additionalHubs[i][1] - 1;
        
        vector<int> hubs = { hA, hB, n - 1 };
        sort(hubs.begin(), hubs.end());
        
        long totalCost = 0;
        for (int i = 0 ; i < n ; i++) {
            int warehousePos = i;
            long minCost = LONG_MAX;
            
            for (int hub: hubs) {
                
                if (hub >= warehousePos) {
                    minCost = min(minCost, long(warehouseCapacity[hub] - warehouseCapacity[warehousePos]));
                }
            }
            
            totalCost += minCost;
        }
        
        result[i] = totalCost;
    }
    
    return result;
    
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string warehouseCapacity_count_temp;
    getline(cin, warehouseCapacity_count_temp);

    int warehouseCapacity_count = stoi(ltrim(rtrim(warehouseCapacity_count_temp)));

    vector<int> warehouseCapacity(warehouseCapacity_count);

    for (int i = 0; i < warehouseCapacity_count; i++) {
        string warehouseCapacity_item_temp;
        getline(cin, warehouseCapacity_item_temp);

        int warehouseCapacity_item = stoi(ltrim(rtrim(warehouseCapacity_item_temp)));

        warehouseCapacity[i] = warehouseCapacity_item;
    }

    string additionalHubs_rows_temp;
    getline(cin, additionalHubs_rows_temp);

    int additionalHubs_rows = stoi(ltrim(rtrim(additionalHubs_rows_temp)));

    string additionalHubs_columns_temp;
    getline(cin, additionalHubs_columns_temp);

    int additionalHubs_columns = stoi(ltrim(rtrim(additionalHubs_columns_temp)));

    vector<vector<int>> additionalHubs(additionalHubs_rows);

    for (int i = 0; i < additionalHubs_rows; i++) {
        additionalHubs[i].resize(additionalHubs_columns);

        string additionalHubs_row_temp_temp;
        getline(cin, additionalHubs_row_temp_temp);

        vector<string> additionalHubs_row_temp = split(rtrim(additionalHubs_row_temp_temp));

        for (int j = 0; j < additionalHubs_columns; j++) {
            int additionalHubs_row_item = stoi(additionalHubs_row_temp[j]);

            additionalHubs[i][j] = additionalHubs_row_item;
        }
    }

    vector<long> result = getMinConnectionCost(warehouseCapacity, additionalHubs);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
