// https://leetcode.com/discuss/interview-question/5032591/Google-or-Phone-Screen-or-282.-Expression-Add-Operators

/*

This was asked in Google Phone Screen.
Input :
2 3 4
List of all operators including "(" and ")".
Target = 20

Output = ( 2 + 3 ) * 4
Return list of all such expressions which evaluate to target.

I prososed to do it via Backtracking but he said try if you can do it via trees.
Finally, wrote code using backtracking but it wasn't completely done.

Let me know your solution using trees/backtracking.

Same as : https://leetcode.com/problems/expression-add-operators/

*/



// #include<bits/stdc++.h>
// using namespace std;

// vector<string> getExpressions(string s, int target) {

// 	int n = s.size();

// 	// (value, expression)
// 	unordered_map<long long int, vector<string>> m;

// 	// add single digit strings
// 	for (int i = 0 ; s[i] != '\0' ; i++) {

// 		int v = s[i] - '0';
// 		string vs(1, s[i]);

// 		m[v].push_back(vs);
// 	}

// 	// length of the string
// 	for (int l = 2 ; l <= n ; l++) {

// 		// start index of the window
// 		for (int s = 0 ; s + l - 1 < n ; s++) {

// 			// end index of window
// 			int e = s + l - 1;

// 			// get substring
// 			string sub = s.substr(s, l);
// 			int v = stoi(sub);

// 			m[v].push()
// 		}
// 	}
// }

// int main() {

// 	string s = "1234567";
// 	int target = 20;

// 	vector<string> expressions = getExpressions(s, target);
	
// 	cout << "expressions:\n";
// 	for (string exp: expressions) 
// 		cout << exp << "\n";

// 	return 0;
// }

















/*****



class Node {

    public:
    Node(){}

    unordered_map< long long , vector<string> > mp ;

    void insert( long long v , string str ){
        mp[v].push_back(str);
    }
};

class Solution {
public:
    vector<string> addOperators(string A , int T ) {
        int N = A.size();

        Node t[N][N];

        for( int i = 0 ; i < N ; i++ )
        {
            long long v = (A[i]-'0');
            string str(1,A[i]);
            t[i][i].insert( v , str );
        }

        for( int L = 2 ; L <= N ; L++ )
        for( int i = 0 ; i+L-1<N; i++ )
        {
            int j = i+L-1;

            // these two lines are added only for each substring, as this itself it possible by default
            int v = stoi(A.substr(i,L));
            t[i][j].insert( v , A.substr(i,L));

            for( int k = i ; k < j ; k++ )
            {
                auto F = t[i][k];
                auto S = t[k+1][j];

                for( auto x : F.mp )
                for( auto y : S.mp )
                {
                    int vx = x.first ;
                    int vy = y.first ;

                    for( auto str_x : x.second )
                    for( auto str_y : y.second )
                    {
                        t[i][j].insert( vx+vy , "(" + str_x + "+" + str_y + ")"  );
                        t[i][j].insert( vx-vy , "(" + str_x + "-" + str_y + ")"  );
                        t[i][j].insert( vx*vy , "(" + str_x + "*" + str_y + ")"  );

                    }
                }
            }
        }
    
        vector< string > res ;

        for( auto x : t[0][N-1].mp[T] )
        {
            cout<<x<<endl;
        }

        return res ;
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
     auto A =  "105"; 
     int target = 5 ;

     Solution tool;
     tool.addOperators(A, target);

    return 0;
}  

Results:

(1*05)  
(1*(0+5))
((1+0)*5)
((1-0)*5)
((1*0)+5)
(10-5)




*/




/*


class Node {

    public:
    Node(){}

    unordered_map< long long , vector<string> > mp ;

    void insert( long long v , string str ){
        mp[v].push_back(str);
    }
};

class Solution {
public:
    vector<string> addOperators(string A , int T ) {
        int N = A.size();

        Node t[N][N];

        for( int i = 0 ; i < N ; i++ )
        {
            long long v = (A[i]-'0');
            string str(1,A[i]);
            t[i][i].insert( v , str );
        }

        for( int L = 2 ; L <= N ; L++ )
        for( int i = 0 ; i+L-1<N; i++ )
        {
            int j = i+L-1;

            // these two lines are added only for each substring, as this itself it possible by default
            int v = stoi(A.substr(i,L));
            t[i][j].insert( v , A.substr(i,L));

            for( int k = i ; k < j ; k++ )
            {
                auto F = t[i][k];
                auto S = t[k+1][j];

                for( auto x : F.mp )
                for( auto y : S.mp )
                {
                    int vx = x.first ;
                    int vy = y.first ;

                    for( auto str_x : x.second ) {
                        for( auto str_y : y.second )
                        {
                            cout << "chars: " << str_x << ", " << str_y << "\n";
                            
                            t[i][j].insert( vx+vy , "(" + str_x + "+" + str_y + ")"  );
                            t[i][j].insert( vx-vy , "(" + str_x + "-" + str_y + ")"  );
                            t[i][j].insert( vx*vy , "(" + str_x + "*" + str_y + ")"  );

                        }
                    }
                    
                }
            }
        }
    
        vector< string > res ;

        for( auto x : t[0][N-1].mp[T] )
        {
            cout<<x<<endl;
        }

        return res ;
    }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
     auto A =  "105"; 
     int target = 5 ;

     Solution tool;
     tool.addOperators(A, target);

    return 0;
}  

Results:

(1*05)  
(1*(0+5))
((1+0)*5)
((1-0)*5)
((1*0)+5)
(10-5)

*/