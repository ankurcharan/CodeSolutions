// 721. Accounts Merge
// https://leetcode.com/problems/accounts-merge/description/

class Solution {
public:
	void dfs(unordered_map<string, vector<string>>& g, string curr, unordered_set<string>& visited, vector<string>& currAccount) {

		visited.insert(curr);
		currAccount.push_back(curr);

		for (string others: g[curr]) {

			if (visited.find(others) == visited.end())
				dfs(g, others, visited, currAccount);
		}
	}

    vector<vector<string>> dfsConnectComponents(vector<vector<string>>& accounts) {

    	unordered_map<string, vector<string>> g;

		int n = accounts.size();

		// create graph
		for (int i = 0 ; i < n ; i++) {

			int accountSize = accounts[i].size();

			string firstEmail = accounts[i][1];		// 0 = name, 1 = first email
			for (int j = 2 ; j < accountSize ; j++) {

				string email = accounts[i][j];
				g[email].push_back(firstEmail);
				g[firstEmail].push_back(email);
			}
		}	      


		// store components
		unordered_set<string> visited;

		vector<vector<string>> mergedAccounts;
		for (int i = 0 ; i < n ; i++) {

			int accountSize = accounts[i].size();
			string name = accounts[i][0];
			string firstEmail = accounts[i][1];

			if (visited.find(firstEmail) == visited.end()) {

				vector<string> currAccount;
				currAccount.push_back(name);
				dfs(g, firstEmail, visited, currAccount);

				// sort after 1st element
				// 1st element = name
				sort(currAccount.begin() + 1, currAccount.end());
				
				mergedAccounts.push_back(currAccount);
			}
		}

		return mergedAccounts;
    }


	/////////////////////////////////
	////// Disjoint-Set Union ///////
	/////////////////////////////////
	void dsuUnion(int a, int b, vector<int>& dsuSize, vector<int>& dsuGroup) {

		int aGroup = findGroup(a, dsuGroup);
		int bGroup = findGroup(b, dsuGroup);

		if (aGroup == bGroup)
			return;

		if (dsuSize[aGroup] > dsuSize[bGroup]) {
			dsuSize[aGroup] += dsuSize[bGroup];
			dsuGroup[bGroup] = aGroup; 
		}
		else {
			dsuSize[bGroup] += dsuSize[aGroup];
			dsuGroup[aGroup] = bGroup;
		}
	}

	int findGroup(int i, vector<int>& dsuGroup) {

		if (dsuGroup[i] == i)
			return i;

		return dsuGroup[i] = findGroup(dsuGroup[i], dsuGroup);
	}

    vector<vector<string>> disjointSetUnion(vector<vector<string>>& accounts) {

    	int n = accounts.size();

        // cout << "n:  " << n << "\n";

    	// each group is its own representative
    	// and size is 1
    	vector<int> dsuGroup(n);
    	vector<int> dsuSize(n);
    	for (int i = 0 ; i < n ; i++) {
    		dsuGroup[i] = i;
    		dsuSize[i] = 1;
    	}

        // cout << "dsuGroup before: ";
        // for (int i = 0 ; i < n ; i++) {
    	// 	cout << setw(2) << dsuGroup[i] << " ";
        // }
        // cout << "\n";

    	// map email to groups
    	unordered_map<string, int> emailGroup;

    	for (int i = 0 ; i < n ; i++) {

    		int accountSize = accounts[i].size();
    		// ignore 0 cause name
    		for (int j = 1 ; j < accountSize ; j++) {

    			// seeing email for first time
    			if (emailGroup.find(accounts[i][j]) == emailGroup.end()) {
    				emailGroup[accounts[i][j]] = i;
    			}
    			// seeing for second time means, person needs to be grouped
    			else {
    				dsuUnion(i, emailGroup[accounts[i][j]], dsuSize, dsuGroup);
    			}
    		}
    	}

        // cout << "dsuGroup after : ";
        // for (int i = 0 ; i < n ; i++) {
    	// 	cout << setw(2) << dsuGroup[i] << " ";
        // }
        // cout << "\n";

      
    	// store emails to components/groups representative
    	unordered_map<int, vector<string>> components;
    	for (auto emailGroupIterator: emailGroup) {

    		// find group transitive/root group of current group
    		int group = findGroup(emailGroupIterator.second, dsuGroup);

    		components[group].push_back(emailGroupIterator.first);
    	}

    	// merge accounts and push name
    	vector<vector<string>> mergedAccounts;

    	for (auto componentsIterator: components) {

    		int group = componentsIterator.first;

    		// init account group with name
    		vector<string> accountGroup = { accounts[group][0] };
    		
    		accountGroup.insert(accountGroup.end(), componentsIterator.second.begin(), componentsIterator.second.end());

    		// do not sort name
    		sort(accountGroup.begin() + 1, accountGroup.end());

    		mergedAccounts.push_back(accountGroup);
    	}

    	return mergedAccounts;
    }


    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {

    	// return dfsConnectComponents(accounts);

    	return disjointSetUnion(accounts);
    }
};