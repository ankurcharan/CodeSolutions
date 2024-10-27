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

int main()
{
    vector<int> a = { 1, 2, 3, 4 };
    
    print(a, "a");
    a.erase(find(a.begin(), a.end(), 2));
    print(a, "a");

    char x = 'A';
    cout << boolalpha << isdigit(x) << "dsds\n";







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

