// 169. Majority Element
// https://leetcode.com/problems/majority-element/description/

class Solution {
public:
	
	int mooreVoting(vector<int>& a) {
		
		int n = a.size();

		// find candidate
		
		// set candidate as index = 0	
		int candidateIndex = 0;
		int candidateCount = 1;

		for (int i = 1 ; i < n ; i++) {
			
			if (a[i] == a[candidateIndex])
				candidateCount++;
			else
				candidateCount--;

			if (candidateCount == 0) {
				
				candidateIndex = i;
				candidateCount = 1;
			}
		}

        return a[candidateIndex]; // LC says majority element always exist
                                    // other wise you have to verify 

		// verify if candidate is majority element
		
		candidateCount = 0;
		for (int i = 0 ; i < n ; i++) {
			if (a[i] == a[candidateIndex])
				candidateCount++;
		}

		if (candidateCount > n / 2)
			return a[candidateIndex];
		
		return -1;              // if no majority element found
	}


	int majorityElement(vector<int>& nums) {
		
		return mooreVoting(nums);      
	}
};