// #include <iostream>
// #include <vector>
// #include <string>
#include<bits/stdc++.h>

using namespace std;

void print(vector<int>& a, string name) {

    cout << name << ": ";
    for (int x: a) {
        cout << x << " ";
    }
    cout << "\n";
}





#include <iostream>
#include <vector>
using namespace std;

int maximumProfit(vector<int>& prices) {
    int n = prices.size();
    int lMin = prices[0];  // Local Minima
    int lMax = prices[0];  // Local Maxima
    int res = 0;
  
    int i = 0;
    while (i < n - 1) {
      
        // Find local minima 
        while (i < n - 1 && prices[i] >= prices[i + 1]) { i++; }

        cout << "minIdx: " << i << endl;

        lMin = prices[i];
       
        // Local Maxima
        while (i < n - 1 && prices[i] <= prices[i + 1]) { i++; }
        lMax = prices[i];
      
        // Add current profit 
        res = res + (lMax - lMin);
    }
  
    return res;
}

int main()
{
    vector<int> prices = {100, 90, 80, 70, 60, 50, 40};
    cout << maximumProfit(prices);







    // vector<int> a = { 1, 2, 3, 4 };
    
    // print(a, "a");
    // a.erase(find(a.begin(), a.end(), 2));
    // print(a, "a");

    // char x = 'A';
    // cout << boolalpha << isdigit(x) << "dsds\n";







    // vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    // for (const string& word : msg)
    // {
    //     cout << word << " ";
    // }
    // cout << endl;

    // bitset<40> a(16);
    // bitset<40> b(32);

    // cout << (a | b).to_string() << "\n";



    return 0;
}

