// 8. String to Integer (atoi)
// https://leetcode.com/problems/string-to-integer-atoi/description/

const int32_t int_max = pow(2, 31) - 1;
const int int_min = -1 * pow(2, 31);

class Solution {
public:
    int myAtoi(string s) {
        
        //  1 = positive
        // -1 = negative
        int sign = 1;	

        int result = 0;

        int i = 0;
        while (s[i] != '\0' && s[i] == ' ')	// remove whitespace
        	i++;

        if (s[i] != '\0' && s[i] == '-')
        	sign = -1, i++;
        else if (s[i] != '\0' && s[i] == '+')
        	sign = 1, i++;

        // leading zeroes
        while (s[i] != '\0' && s[i] == '0')
        	i++;

        // cout << "sign: " << sign << "\n";
        // cout << "first i: " << i << endl;

        while (s[i] != '\0') {

        	if (!isdigit(s[i]))
        		return result * sign;		// cannot be converted to int - return answer yet

        	if ((result > INT_MAX / 10 || (result == INT_MAX / 10 && (s[i] - '0' > 7)))) {

                // cout << "result: " << result <<  " -- fc:" << (result > INT_MAX / 10 ) << " -- sc:" << (result == INT_MAX / 10) << " - " << (s[i] - '0') << "\n";              
    			return sign == 1 ? INT_MAX : INT_MIN;
    		}

            // cout << i << " : i\n";
    		result = (result * 10) + (s[i] - '0');

            i++;
        }

        return result * sign;
    }
};