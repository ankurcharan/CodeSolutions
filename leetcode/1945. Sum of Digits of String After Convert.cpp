// 1945. Sum of Digits of String After Convert
// https://leetcode.com/problems/sum-of-digits-of-string-after-convert/description/




/////// METHOD 1



// class Solution {
// public:
//     int getLucky(string s, int k) {
        
//         string a;

//         for (int i = 0 ; s[i] != '\0' ; i++) {
//         	int val = s[i] - 'a' + 1;

//         	stringstream ss;
//         	ss << val;
//         	string t;
//         	ss >> t;

//         	a += t;
//         }

//         while (k--) {
            
//             int sum = 0;
//             for (int i = 0 ; a[i] != '\0' ; i++) {

//             	sum += a[i] = '0';
//             }

//             stringstream ss;
//             ss << sum;
//             ss >> a;
//         }

//         return a;
//     }
// };










/////// METHOD 2

class Solution {
public:
    int getLucky(string s, int k) {
        
        string a = "";

        for (int i = 0 ; s[i] != '\0' ; i++) {
        	int val = s[i] - 'a' + 1;
        	a += to_string(val);
        }

        while (k--) {
            
            int sum = 0;
            for (int i = 0 ; a[i] != '\0' ; i++) {
            	sum += a[i] - '0';
            }

            a = to_string(sum);
        }

        return stoi(a);
    }
};