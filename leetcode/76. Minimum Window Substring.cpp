// 76. Minimum Window Substring
// https://leetcode.com/problems/minimum-window-substring/description/

class Solution {
public:

	////////////////////
	//// BRUTEFORCE ////
	////////////////////



	// bool checkIfSame(const string& s, const string& t) {

	// 	unordered_map<char, int> sm;
	// 	unordered_map<char, int> tm;

	// 	for (int i = 0 ; s[i] != '\0' ; i++)
	// 		sm[s[i]]++;

	// 	for (int i = 0 ; t[i] != '\0' ; i++)
	// 		tm[t[i]]++;

	// 	for (int i = 0 ; t[i] != '\0' ; i++)
	// 	{
	// 		if (tm[t[i]] > sm[t[i]])
	// 			return false;
	// 	}

	// 	return true;
	// }

	// string bruteforce(string s, string t) {

	// 	int minLength = INT_MAX;
	// 	string ans = "";

	// 	for (int i = 0 ; s[i] != '\0' ; i++) {

	// 		for (int j = i ; s[j] != '\0' ; j++) {

	// 			string sub = s.substr(i, j - i + 1);

	// 			if (sub.size() < minLength && checkIfSame(sub, t))
	// 			{
	// 				minLength = min(minLength, (int)sub.size());
	// 				ans = sub;
	// 			}
	// 		}
	// 	}

	// 	return ans;
	// }



	///////////////////
	// BINARY SEARCH //
	///////////////////


	// bool checkIfPossibleLength(string s, string t, int mid, int& start) {

    //     bool d = false;
    //     if (mid == 4)
    //         d = true;

	// 	int count[256];
	// 	memset(count, 0, sizeof(count));

	// 	int distinctChars = 0;
	// 	for(char x: t)
	// 	{
	// 		if (count[x] == 0)
	// 			distinctChars++;
	// 		count[x]++;
	// 	}

    //     if (d)
    //     {
    //         cout << "char count: ";
    //         for (int i = 65 ; i < 65+26 ; i++)
    //             cout << count[i] << " ";
    //         cout << endl;
    //     }


	// 	int currCount = 0;
	// 	for (int i = 0 ; s[i] != '\0' ; i++) {

	// 		count[s[i]]--;

	// 		if (count[s[i]] == 0)
	// 			currCount++;

	// 		if (i >= mid) {

	// 			count[s[i - mid]]++;
	// 			if (count[s[i - mid]] == 1)
	// 				currCount--;
	// 		}

	// 		if (i >= mid - 1) {

	// 			if (currCount == distinctChars) {
	// 				start = i - mid + 1;
	// 				return true;
	// 			}
	// 		}
	// 	}

    //     return false;
	// }

	// string binarySearch(string s, string t) {

	// 	int sn = s.length();
	// 	int tn = t.length();

	// 	int l = 0;
	// 	int r = sn;

	// 	int minLength = INT_MAX;
	// 	int start = -1;

	// 	while (l <= r) {

	// 		int mid = l + ((r - l)/2);

    //         // cout << mid << " -- mid\n";

	// 		if (checkIfPossibleLength(s, t, mid, start)) {
				
    //             // cout << " djs true\n";
    //             if (mid < minLength)
	// 			{
	// 				minLength = mid;
	// 			}

	// 			// substr found in height = mid

	// 			r = mid - 1;
	// 		}
	// 		else {
    //             // cout << " djs false\n";
	// 			l = mid + 1;

    //             // cout << "l: " << l << "  -- r: " << r << endl;
	// 		}
	// 	}

	// 	string ans = "";
	// 	if (start != -1)
	// 		ans = s.substr(start, minLength);

	// 	return ans;
	// }


	/////////////////
	//// HASHING ////
	/////////////////

	string hashing(string s, string t) {

		int sn = s.length();
		int tn = t.length();

		if (sn < tn)
			return "";		// not possible

		vector<int> scount(256, 0);
		vector<int> tcount(256, 0);


		for (int i = 0 ; t[i] != '\0' ; i++)
			tcount[t[i]]++;

		int minLength = INT_MAX;
		int startIndex = -1;

		int start = 0;			// window start index 
		int charsMatched = 0;	// char matched current for t

		for (int i = 0 ; s[i] != '\0' ; i++) {

			scount[s[i]]++;

			if (tcount[s[i]] != 0 && scount[s[i]] <= tcount[s[i]])
            {
                charsMatched++;
            }
				

			// all chars matched
			if (charsMatched == tn) {

				// minimize the window
				while (s[start] != '\0' && (scount[s[start]] > tcount[s[start]] || tcount[s[start]] == 0)) {

					if (scount[s[start]] > tcount[s[start]])
						scount[s[start]]--;

					start++;
				}

				// curr string is your ans
				int len = i - start + 1;

				if (len < minLength) {
					minLength = len;
					startIndex = start;
				}
			}
		}

		if (startIndex != -1)
			return s.substr(startIndex, minLength);

		return "";	// no string matched
 	}

	string minWindow(string s, string t) {

        // return bruteforce(s, t);	// TLE

		// return binarySearch(s, t);	// Works O(n log n)

		return hashing(s, t);           // O(n)
	}
};