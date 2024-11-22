
// https://leetcode.com/discuss/interview-question/1682632/google-phone-screen-number-of-islands-in-a-tree



// Hi Ankur
// Hi Nischal

// Hi there
// Refreshing

/*

# Question:

In a tree of zeros and ones, an island is defined as
a group of ones that are surrounded by zeros or are
at the boundary of the tree.

Example:

      0(1) T/T
     /          \
    1(2)r:T F   1(3) T
    /           /
   0(5) T/T     1(4) T
  /    \
1(6) T   1(7) Tr:T
  \       \
  1(8) T   1(9) -T
  
  
      0(1) T/F
     /          \
    1(2)r:T F   0(3) F
    /           /
   0(5) T/T     0(4) F
  /    \
1(6) T   1(7) Tr:T
  \       \
  1(8) T   1(9) -T
  


Find the number of islands in the tree.
In the above example, there are 4 islands.


Follow Up Question #1: Count of distinct sizes

Find the number of distinct island sizes.

Here, size = number of 1s in the island.

In the above example, there are 2 sizes (1 and 2).



Follow Up Question #2: Count of distinct shapes

Find the number of distinct island shapes.

In the above example, there are 3 shapes:

1     1   1
     /     \
    1       1
    
    LLLCRRR
    1
    /
   1
   /
  1
      
      0
      / 
     1
    /  \  
   1    1


*/




/*
F2


      0(1) T/T
     /          \
    1(2)r:T F   1(3) T
    /           /
   0(5) T/T     1(4) T
  /         \
1(6) R+""=R   1(7) Tr:T
/ \            \
1(10)  1(8) "", T     1(9) -T


node 6
left = ""
right ""

if (left.second == true)
  L + left.first 
if (right.second == true)
  R + right.first
  
tree shape = L + ""
             R + ""
           
           return "LCR", true


5
left == "R", true
right = "R", true

tree shape 
if (left.second == true)
  L + left.first 
if (right.second == true)
  R + right.first

*


class Node {
public:
  Node* left, right;
  int v;
  
  Node(int v) {
    this -> v = v;
    left = right = NULL;
  }
};


/*

      0(1) T/T
     /                \
    1(2) r:T          1(3) r:T 
    /                 /       \
   0(5) T/T         1(4) r:T   0 island++;
  /         \                   \
1(6) r:2      1(7) r:2          1 r:T
  \           \
  1(8) r:1    1(9) r:1
  
  
  */

// O(n)


// time: O(n)
// space: O(n)
int distinctSize(Node* root, unordered_set<int>& s, int& islands) {
  
  if (root == NULL)
    return 0;
  
  int left = distinctSize(root -> left, s);
  int right = distinctSize(root -> right, s);
  
  if (root -> v == 1) {
    return left + right + 1;
  }
  else if (root -> v == 0) {

    if (left != 0) {
      s.insert(left);   // O(1)
      islands++;
    }
    if(right != 0) {
      s.insert(right); 
      islands++;
    }
    
    return 0;
  }
}

// will do distinct size and number of islands in single pass
int getDistinctSize(Node* root) {
 
  if (root == NULL) 
    return 0;
  
  int islands = 0;
  unordered_set<int> sizes;   // sizes in tree
  int rs = distinctSize(root, sizes, islands);
  if (rs != 0) {
    islands++;
    sizes.insert(rs);
  }
     
  cout << " no of islands: " << islands << endl;
  cout << "distinct sizes: " << sizes.size() << endl;
  
  return sizes.size();
}



/*

      0(1) T/T
     /                \
    1(2) r:T          1(3) r:T 
    /                 /       \
   0(5) T/T         1(4) r:T   0 island++;
  /         \                   \
1(6) r:T      1(7) r:T          1 r:T
  \           \
  1(8) r:T    1(9) r:T
  
  
  5 
  islands += 2;
  0
  islands += 2;
  
  
  */

bool recurse(Node* root, int& islands) {

  if (root == NULL)
    return false;
  
  bool l = recurse(root -> left, islands);
  bool r = recurse(root -> right, islands);
  
  if (root -> v == 1) {
    return true;
  }
  else if (root -> v == 0) {
   
    islands += l;
    islands += r;
    
    return false;
  }
}

int numberOfIsland(Node* root) {
 
  if (root == NULL) 
    return 0;
  
  int islands = 0;
  recurse(root, islands);
  
  if (root -> v == 1) {
    islands++;
  }
  
  return islands;
}


/*
n = number of all nodes, h = height of the tree, s = number of islands

time: O(n)


Space Complexity

BFS
 - skew tree = O(1) space
 - complete => h = log2(n)      O(2^h) space  

Recursive 
 - skew = O(n) 
 - complete = (log n) 

*/