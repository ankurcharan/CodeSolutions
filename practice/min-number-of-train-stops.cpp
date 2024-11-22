// min-number-of-train-stops
// https://leetcode.com/discuss/interview-question/algorithms/124552/google-minimum-number-of-train-stops

/*


There are an infinite number of train stops starting from station number 0.


There are an infinite number of trains. The nth train stops at all of the k * 2^(n - 1) 
stops where k is between 0 and infinity.


When n = 1, the first train stops at stops 	0, 1, 2, 3, 4, 5, 6, etc.
When n = 2, the second train stops at stops 0, 2, 4, 6, 8, etc.
When n = 3, the third train stops at stops 	0, 4, 8, 12, etc.

Given a start station number and end station number, 
return the minimum number of stops between them. 
You can use any of the trains to get from one stop to another stop.


For example, the minimum number of stops between 
start = 1 and end = 4 is 3 
	because we can get from 1 to 2 to 4.

*/

#include <bits/stdc++.h>
using namespace std;



int minSteps(int start, int end) {

    // cout << "INITIAL = start: " << start << ", end: " << end << "\n\n";
    
	int minSteps = 1;
	while (start < end) {
		
                
        int pow1 = log2(end);
		int pow2 = log2(end - start);

		// cout << "pow1: " << pow1 << ", pow2: " << pow2 << "\n";

		minSteps++;

		end -= pow(2, min(pow1, pow2));
        
        // cout << "start: " << start << ", end: " << end << "\n\n";
	}
    
    if (end - start)
	    cout << "ENDING = start: " << start << ", end: " << end << "\n\n";

	return minSteps + end - start;
}





int getHighestTwoPowerFactor(int from) {

	int printStart = from;


	// itself is power of 2
	if (from & (from - 1) == 0) {

		cout << "getHighestTwoPowerFactor: " << printStart << " = itself" << endl;
		return from;
	}

	int count = 0;

	// even
	while (from % 2 == 0) {

		count++;
		from >>= 1;
	}

	cout << "getHighestTwoPowerFactor: " << printStart << " = " << count << " = " << (1 << count) << endl;

	return 1 << count;
}

void printSteps(int start, int end) {

	cout << "step: " << start << "\n";

	// no step needed
	if (start == end) {
		cout << "0 steps for this\n";
		return;
	}

	int step = 1;

	if (start == 0) {
		int highestPowerTwo = log2(end);
		start = (1 << highestPowerTwo);
		
		cout << "step: " << start << "\n";
		
		step++;
	}
	else if (start & 1) {

		start++;
		step++;

		cout << "step: " << start << "\n";
	}

	// no step needed
	if (start == end)
		return;

	int highestTwoPowerFactor = 1;

	while (true) {

		highestTwoPowerFactor = getHighestTwoPowerFactor(start);
		
		start += highestTwoPowerFactor;
		step++;


		if (start > end) {

			start -= highestTwoPowerFactor;
			step--;

			cout << "step: " << start << "\n";
			break;
		}
		else if (start == end) {

			cout << "step: reached end" << "\n";
			cout << "step count: " << step << "\n";
		}

		cout << "step: " << start << "\n";
	}

	while (start < end) {

		while (start + highestTwoPowerFactor > end) {
			highestTwoPowerFactor /= 2;
		}

		start += highestTwoPowerFactor;
		step++;

		cout << "step: " << start << "\n";
	}

	cout << "total steps: " << step << "\n";
}



int main() {

	// int start = 13;
	// int end = 64;

	int start = 15;
	int end = 65;

	// int ans = minSteps(start, end);
	// cout << "ans: " <<  ans << "\n";

	printSteps(start, end);

	return 0;
}



/**

// "static void main" must be defined in a public class.

public class Main {
    
    public static void main(String[] args) {
        
        Main m = new Main();
        
        System.out.println(m.getTrains(0, 67));
    }
    
    
    
    public int getTrains(int from, int to) {
		System.out.print(from + " \n");
		
        int count = 1;
		
		if(from == 0) {
			from = getNearestTwoPower(to);
            
            System.out.print("from = 0: " + from + "\n");
            
			count++;
			System.out.print(from + " ");
		}
        else if (from % 2 != 0) {
			System.out.print(from + " is odd, incrementing\n");
            from++;
			count++;
			System.out.print(from + " as updated \n");
		} 
        
        
		if(from == to)
			return count;
		
		//int nearestTwoPower = getNearestTwoPower(from);
		
		int getHighestTwoPowerFactor = 1;
		
        
        System.out.println("\n\n");
        
		while(true) {
            
			getHighestTwoPowerFactor = getHighestTwoPowerFactor(from);
			
            System.out.print("from: " + from + ", getHighestTwoPowerFactor: "  + getHighestTwoPowerFactor + "\n");
            
            from += getHighestTwoPowerFactor;
			count++;
            
            System.out.print("from: " + from + ", count: " + count + "\n");
            
			if(from > to) {
				from -= getHighestTwoPowerFactor;
				count--;
				break;
			}else if(from == to) {
				System.out.println(from + " ");
				return count;
			}
			System.out.print("from: " + from + " \n\n");
		}
        
        System.out.print("from out: " + from + " \n\n");
		
		while(from < to) {
			while(from + getHighestTwoPowerFactor > to) {
				getHighestTwoPowerFactor /= 2;
			}
            
            System.out.print("from: " + from + ", getHighestTwoPowerFactor: "  + getHighestTwoPowerFactor + "\n");
            
			from += getHighestTwoPowerFactor;
			count++;
            System.out.print("from: " + from + ", getHighestTwoPowerFactor: "  + getHighestTwoPowerFactor + "\n");
            System.out.println();
		}
		System.out.println();
		return count;
			
	}

	public int getHighestTwoPowerFactor(int from) {
		// TODO Auto-generated method stub
		if((from & (from - 1)) == 0) {
            System.out.print("getHighestTwoPowerFactor: " + from + " from & (from - 1)) == 0 \n" );
            return from;   
        }
		
		int count = 0;
		while(from % 2 == 0) {
            System.out.print(from + " (" + count + ") ");
			from >>= 1;
			count++;
		}
        System.out.print(from + " (" + count + ")  => return: " + (1 << count) + "\n");
		return 1 << count;
		
	}
	
	public int getNearestTwoPower(int from) {
		// TODO Auto-generated method stub
		if((from & (from - 1)) == 0)
			return from;
		
		int count = 0;
		while(from != 0) {
			from >>= 1;
			count++;
		}
		return 1 << (count - 1);
		
	}
} 



 */