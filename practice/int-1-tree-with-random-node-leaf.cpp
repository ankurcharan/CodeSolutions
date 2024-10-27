// int-1-tree-with-random-node-leaf
// https://leetcode.com/discuss/interview-question/2006734/google-onsite-l4-rejected

/*

Implement a Tree class.


// Question details
// You're given an interface of a Dynamic Tree, your task is to write an
// implementation according to the interface docstrings. You can change the syntax according to a language of your choice, feel free to use any helper methods or fields.
// Implement the methods of the following Tree class.

data class TreeNode<T> {
	TreeNode parent = null;
	T item;
	// New fields if required.
}

class Tree<T> {
	// Creates Tree instance in which the number of nodes can not exceed capacity.
	// The tree should already have a single node: its root.
	Tree(int capacity) {}

	// Returns the number of nodes.
	int size() {}

	// Returns the root of the tree.
	TreeNode getRoot() {}

	// Creates a node that is attached to a parent node that already exists.
	TreeNode createNode(TreeNode parent) {}

	// Returns a random node in the Tree. Each Tree's node has an equal probability to
	// be selected.
	TreeNode getRandomNode() {}
}

// My code

data class TreeNode(val parent: TreeNode?, children: MutableList<TreeNode>)

class Tree(private val capacity: Int) {
	var root = TreeNode(null, mutableListOf()) // arraylist
	var size = 1
	val nodes = mutableListOf(root)
	val leaves = mutableListOf(root)
	val random = Random()

	fun size(): Int = size

	fun getRoot(): TreeNode = root

	fun createNode(parent: TreeNode): TreeNode {
		if (size == capacity) throw IllegalStateException()
		val node = TreeNode(
			parent,
			mutableListOf())
		)
		parent.children += node
		nodes += node
		size++
		return node
	}

	fun getRandomNode(): TreeNode {
		val index = random.getInt(nodes.size) // [0-nodes.size)
		return nodes[index]
	}

	fun getRandomLeaf(): TreeNode {
		val leaves = nodes.filter { }
	}
}

// Time: O(n)
buildTree(int n) {
	tree = new Tree(n); // Time: O(1)
	for (i=0; i<n-1; i++) { // Time: O(n)
		parent = tree.getRandomNode(); // Time: O(1)
		tree.createNode(parent); // Time: O(1)
	}
}

*/




#include <bits/stdc++.h>
using namespace std;

// TreeNodeX only because leetcode has pre-compiled class
// TreeNode that they use
// and I was running this on LC Playground
class TreeNodeX {
public:
	TreeNodeX* parent;
	int item;

	// added
	TreeNodeX(TreeNodeX* parent, int item) {
		this -> parent = parent;
		this -> item = item;
	}
};

class Tree {

	int capacity;
	TreeNodeX* root;
	vector<TreeNodeX*> nodes;
    
    vector<TreeNodeX*> leavesList;
    unordered_map<TreeNodeX*, int> leafIndex;

	int nodeItem = 1;
    
    int getRandomIndex(int s) {
        return rand() % s;
    }

public:
	// Creates Tree instance in which the number of nodes 
	// can not exceed capacity.
	// The tree should already have a single node: its root.
	Tree(int capacity) {	

		srand(time(NULL));

		this -> capacity = capacity;
		
        TreeNodeX* rootNode = new TreeNodeX(NULL, 0);
        this -> root = rootNode;
        nodes.push_back(root);
        
        leavesList.push_back(root);
        leafIndex[root] = 0;
	}

	// returns number of nodes
	int size() {
		return nodes.size();
	}

	// Creates a node that is attached to a parent node that already exists.
	TreeNodeX* createNode(TreeNodeX* parent) {

		if (nodes.size() == capacity) {
			cout << "size full\n";
			return NULL;
		}

		TreeNodeX* newNode = new TreeNodeX(parent, nodeItem++);
		// parent -> children.insert(newNode);
        
        nodes.push_back(newNode);
        
        if (leafIndex.find(parent) != leafIndex.end()) {
            
            // cout << "parent is leaf\n";

            int pIndex = leafIndex[parent];
            
            leavesList[pIndex] = newNode;
            leafIndex[newNode] = pIndex;

            leafIndex.erase(parent);
        }
        else {
            // cout << "parent is not leaf\n";
        	leavesList.push_back(newNode);
        	leafIndex[newNode] = leavesList.size() - 1;
        }

		return newNode;
	}

	// Returns the root of the tree.
	TreeNodeX* getRoot() {
		return root;
	}

	TreeNodeX* getRandomNode() {

		int randomIndex = getRandomIndex(nodes.size());

		cout << "node size: " << nodes.size() << ", ";
		cout << "randomIndex: " << randomIndex << "\n";
		
		return nodes[randomIndex];
	}

	TreeNodeX* getRandomLeaf() {
        
        int randomIndex = getRandomIndex(leavesList.size());
		

		cout << "leaves size: " << leavesList.size() << ", ";
		cout << "randomIndex: " << randomIndex << "\n";
		
        return leavesList[randomIndex];
	}

	void printNodes() {

		cout << "nodes: ";
		for (TreeNodeX* node: nodes) {
			cout << node -> item << " ";
		}
		cout << "\n";
	}

	void printLeaves() {

		cout << "leaves: ";
		for (TreeNodeX* leaf: leavesList) {
			cout << leaf -> item << " ";
		}
		cout << "\n";
	}
};

int main() {

	// srand(time(NULL));

	Tree t(5);

	TreeNodeX* root = t.getRoot();
	t.createNode(root);
	t.createNode(root);
	// t.createNode(root);
	TreeNodeX* four = t.createNode(root);
    
    // t.createNode(root);

    t.createNode(four);
    
    int q = 10;
    cout << "random: \n";
    while (q--) {
    	TreeNodeX* random = t.getRandomNode();
    };
    cout << "\n";


    q = 10;
    cout << "random leaf:\n";
    while (q--) {
    	TreeNodeX* randomLeaf = t.getRandomLeaf();
    };

    cout << endl;
    t.printNodes();
    t.printLeaves();

	return 0;
}