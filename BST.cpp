
// Cecelia Dahlinger
// Nonlinear Data Structures
// 2/16/18
// Binary Search Tree Lab 1
//
// This project is to implement a binary search tree. There will be a set of user commands
// to choose from including insert, delete, and list. The help command will present a list 
// of commands. The tree will support only strings, and will keep a count of duplicate 
// entries.

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

//Classes

// This program includes a BSTNode class, which contains the code for nodes used by the BSTree class.
// The BSTree class is a binary search tree data structure with the ability to insert and remove items.

class BSTNode
{
	// Node for the binary search tree class (BSTree)
	private:
		// Data Members
		string key; // String of data within the node
		int count; // Integer to keep count of times string is inserted/removed
		BSTNode* leftChild; // Pointer to the left child of the node
		BSTNode* rightChild; // Pointer to the right child of the node
		BSTNode* parent; // Pointer back to the parent of the node
	public:
		//Constructor
		BSTNode(string str)
		{
			key = str; // Sets the key to the given string
			count = 1; // Sets total count to 1
			leftChild = NULL; // Sets left and right children to null as well as the parent node to null
			rightChild = NULL;
			parent = NULL;
		}

		//Functions
		void setAllNULL()
		{
			leftChild = NULL; 
			rightChild = NULL;
			parent = NULL;
		}
		void setLeft(BSTNode* left)
		{
			// Sets left child pointer to given node pointer
			leftChild = left;
		}
		void setRight(BSTNode* right)
		{
			// Sets right child to given node pointer
			rightChild = right;
		}
		void setParent(BSTNode* node)
		{
			// Sets parent pointer to given node pointer
			parent = node;
		}
		void increaseCount()
		{
			// Increases count by one
			count++;
		}
		void decreaseCount()
		{
			// decreases count by one
			count--;
		}
		void setKey(string str)
		{
			//sets key to given string
			key = str;
		}
		BSTNode* getLeft()
		{
			// Returns a pointer to the left child
			return leftChild;
		}
		BSTNode* getRight()
		{
			// Returns a pointer to the right child
			return rightChild;
		}
		BSTNode* getParent()
		{
			// Returns a pointer to the parent node
			return parent;
		}
		int getCount()
		{
			// Returns and integer count of the String
			return count;
		}
		string getKey()
		{
			// return the string that is the key
			return key;
		}
};

class BSTree 
{
	private:
		// Data Members
		BSTNode* root; // Pointer to the root of the tree
	public:
		// Constructor
		BSTree()
		{
			root = NULL;
		}

		// Functions
		BSTNode* search(string str)
		{
			// Find and return a pointer to the node if found, else reutrn NULL
			BSTNode* current = root;
			// Use the BST property to find where the given string SHOULD be, if not found return null
			while (current != NULL)
			{
				//if str is less than current, go left
				string key = current->getKey();
				//string key = "aaaaaaa";
				if (str.compare(key)<0)
				{
					current = current->getLeft(); // Set current to the left child of itself
				}
				//if str is greater than current, go right
				else if (str.compare(key)>0)
				{
					current = current->getRight(); // Set current to the right child of itself
				}
				//if str is equal to the current node, return a pointer to that node
				else
				{
					return current;
				}
			}
			// If we fall off the tree, the string is not in the tree. Returning current returns NULL
			return current;
		}
		BSTNode* insert(string str)
		{
			// Inserts the string into the tree at the appropriate location
			BSTNode* current = root;
			BSTNode* previous = NULL;
			//determine of the newNode should go left or right of the current node
			//when loop ends, newNode was either found, increased, and method returned or previous is the parent node of the newNode
			int goLeftorRight = 0; // Indicator of where to place the new node if we fall off the tree
			// While current isn't a NULL pointer, look for the spot to put it
			while (current != NULL)
			{
				//if str is less than current, go left
				string key = current->getKey();
				//string key = "aaaaaaa";
				if (str.compare(key)<0)
				{
					previous = current; // Set previous to current, moving down through the tree
					current = current->getLeft(); // Set current to the left child of itself
					goLeftorRight = -1; // -1 indicates to go left if this is a leaf
				}
				//if str is greater than current, go right
				else if (str.compare(key)>0)
				{
					previous = current; // Set previous to current, moving down through the tree
					current = current->getRight(); // Set current to the right child of itself
					goLeftorRight = 1; // 1 indicates go right if this is a leaf
				}
				//if str is equal to the current node, increase numtimes and return
				else
				{
					current->increaseCount();
					return current;
				}
			}
			//Create new node newNode
			BSTNode* newNode = new BSTNode(str);
			//newnode goes to the left child of prev
			if (goLeftorRight == -1)
			{
				previous -> setLeft(newNode);
				newNode->setParent(previous);
			}
			//newNode goes to the right of prev
			else if (goLeftorRight == 1)
			{
				previous->setRight(newNode);
				newNode->setParent(previous);
			}
			// Otherwise, this means that the tree is empty, insert newNode as the root
			else
			{
				root = newNode;
				return newNode;
			}
		}
		BSTNode* min()
		{
			// Returns pointer to the minimum string in the tree
			// Go left as far as we can
			BSTNode* current = root;
			// While the current node's left child is not NULL, continue moving left
			if (current != NULL)
			{
				while (current->getLeft() != NULL)
				{
					current = current->getLeft();
				}
			}
			// return the current node, it is the leftmost, or minimum
			return current;
		}
		BSTNode* max()
		{
			// Returns pointer to the maximum string in the tree
			// Go right as far as we can
			BSTNode* current = root;
			// While the current node's right child is not NULL, continue moving right
			if (current != NULL)
			{
				while (current->getRight() != NULL)
				{
					current = current->getRight();
				}
			}
			// return the current node, it is the rightmost, or maximum
			return current;
		}
		BSTNode* next(string str)
		{
			// Find the successor of the given string in the tree
			// Get the node corresponding to the given str
			BSTNode* node = search(str);
			// node will be NULL if str isn't in the tree, output NULL. Also if node is max, output NULL
			if (node != NULL && node != max())
			{
				// If node has a right child, go right, then left as far as we can go
				if (node->getRight() != NULL)
				{
					node = node->getRight();
					while (node->getLeft() != NULL)
						node = node->getLeft();
					return node;
				}
				else
				{
					BSTNode* parent = node->getParent();
					while (parent != NULL && node == parent->getRight())
					{
						node = parent;
						parent = parent->getParent();
					}
					return parent;
				}
			}
			else
				return NULL; // Return NULL if the string does not exist in the tree, or is the max
		}
		BSTNode* prev(string str)
		{
			// Find the predecessor of the given string in the tree
			// Get the node corresponding to the given str
			BSTNode* node = search(str);
			// node will be NULL if str isn't in the tree, output NULL. Also if node is min, output NULL
			if (node != NULL && node != min())
			{
				// If node has a left child, go left, then right as far as we can go
				if (node->getLeft() != NULL)
				{
					node = node->getLeft();
					while (node->getRight() != NULL)
						node = node->getRight();
					return node;
				}
				else
				{
					BSTNode* parent = node->getParent();
					while (parent != NULL && node == parent->getLeft())
					{
						node = parent;
						parent = parent->getParent();
					}
					return parent;
				}
			}
			else
				return NULL; // Return NULL if the string does not exist in the tree, or is the max

		}
		void remove(string str)
		{
			// Remove the node from the tree
			// This is difficult....
			// Start by finding it using search
			BSTNode* node = search(str); // Node is a pointer to the node we will be removing, or it is NULL if there is no node with str as its key
			// Determine if the node's count is greater than 1. if greater thhan 1, just decrease, else remove
			if (node->getCount() > 1)
			{
				node->decreaseCount();
			}
			// Determine if it is a leaf, has one child, or two children
			// If it is a leaf...
			// Just delete it
			// determine if it was the root, if it is set the root to null, then continue
			else if (node->getLeft() == NULL && node->getRight() == NULL)
			{
				// Check if root
				if (node->getParent() != NULL)
				{
					if (node->getParent()->getRight() == node)
					{
						node->getParent()->setRight(NULL);
						//deconstruct node
					}
					else if (node->getParent()->getLeft() == node)
					{
						node->getParent()->setLeft(NULL);
						//deconstruct node
					}
				}
				else
				{
					root = NULL;
					//deconstruct node
				}
			}
			// If it has one child...
			// Link it's parent node to it's child and delete the node
			// Has right child only
			else if ((node->getLeft() == NULL && node->getRight() != NULL))
			{
				// Has a parent node
				if (node->getParent() != NULL)
				{
					// Is parent node's right child
					if (node->getParent()->getRight() == node)
					{
						node->getParent()->setRight(node->getRight()); // Set parent's right child to node's right child
						node->getRight()->setParent(node->getParent()); // Set node's right child's parent node to node's parent node
						//deconstruct node
						node->setAllNULL();
						delete node;
					}
					// Is parent node's left node
					else if (node->getParent()->getLeft() == node)
					{
						node->getParent()->setLeft(node->getRight()); // Set parent's left child to node's right child
						node->getRight()->setParent(node->getParent()); // Set node's right child's parent node to node's parent node
						//deconstruct node
						node->setAllNULL();
						delete node;
					}
				}
				else
				{
					// This means it is the root... set it's right child to root
					root = node->getRight();
					//deconstruct node
					node->setAllNULL();
					delete node;
				}
			}
			// Has left child only
			else if ((node->getLeft() != NULL && node->getRight() == NULL))
			{
				// Has a parent node
				if (node->getParent() != NULL)
				{
					// Is parent node's right child
					if (node->getParent()->getRight() == node)
					{
						node->getParent()->setRight(node->getLeft()); // Set parent's right child to node's left child
						node->getLeft()->setParent(node->getParent()); // Set node's left child's parent node to node's parent node
						//deconstruct node
						node->setAllNULL();
						delete node;
					}
					// Is parent node's left node
					else if (node->getParent()->getLeft() == node)
					{
						node->getParent()->setLeft(node->getLeft()); // Set parent's left child to node's left child
						node->getLeft()->setParent(node->getParent()); // Set node's left child's parent node to node's parent node
						//deconstruct node
						node->setAllNULL();
						delete node;
					}
				}
				else
				{
					// This means it is the root, set it's left child to be the new root
					root = node->getLeft();
					//deconstruct node
					node->setAllNULL();
					delete node;
				}
			}
			//If it has two children...
			// Note in this case, we don't have to move the root pointer because we never delete the current node, just change it's contents
			else
			{
				// Find node's sucessor
				BSTNode* y = next(str);
				// If y, node's successor, is node's right child
				// Copy y's key into node and set node's right child to y's right child, the right child's parent pointer is also set to node. Delete y.
				if (y == node->getRight())
				{
					node->setKey(y->getKey());
					//if y was a leaf, just remove it buy setting it's parent's left pointer to NULL
					if (y->getRight() == NULL && y->getLeft() == NULL)
					{
						y->getParent()->setRight(NULL);
						y->setAllNULL();
						delete y;
					}
					else
					{
						node->setRight(y->getRight());
						y->getRight()->setParent(node);
						y->setAllNULL();
						delete y;
					}
				}
				// If y is somewhere else in the tree
				// Copy y's key into node
				// set node's right child's left child to y's right child
				// set y's right child's parent to node's right child
				// Delete y.
				else
				{
					//if y was a leaf, just remove it buy setting it's parent's left pointer to NULL
					if (y->getRight() == NULL && y->getLeft() == NULL)
					{
						y->getParent()->setRight(NULL);
						y->setAllNULL();
						delete y;
					}
					else 
					{
						node->setKey(y->getKey());
						node->getRight()->setLeft(y->getRight());
						y->getRight()->setParent(node->getRight());
						y->setAllNULL();
						delete y;
					}
				}

			}
		}
		void displayNode(string str)
		{
			// Used to output after an action, or as a search
			BSTNode* node = search(str);
			cout << str + " "; // Always outputs the string even if it can't find it
			if (node != NULL)
				cout <<  node->getCount(); // output string count if found
			else
				cout << "0"; // output 0 if not found
			cout << "\n";
			return;
		}
		void displayAll()
		{
			// In-order traversal, displaying all strings in order with count
			BSTNode* current = min();
			//Using a do while loop, output current, then move to the successor of current until next(current) is null
			do 
			{
				cout << current->getKey() + " ";
				cout << current->getCount();
				cout << "\n";
			} while ((current = next(current->getKey())) != NULL);
			return;
		}

};


//Main Method
int main()
{
	// A console program with a list of commands. It will terminate once 'exit' is typed


	BSTree* myTree = new BSTree();			// Creates the data structure of a tree
	bool terminate = false;					// Boolean to keep the loop going while exit was not selected
	string command;							// String input from the command line
	string key;								// String input if command requires it
	// Take in an input while variable terminate is false
	while (!terminate)
	{
		key = "";							// Set key to an empty string at the beginning of each loop iteration
		cin >> command;						// Take in a string command
		
		// Convert command to all lowercase, for case insensitivity
		for (int i = 0; command[i]; i++) 
			command[i] = tolower(command[i]);

		// Use nested if statements to setermine if there should be another input
		// Also complete the action requested
		if (command == "insert")
		{
			// Get input key
			cin >> key;
			// Insert the given key into myTree and output str count
			myTree->insert(key);
			myTree->displayNode(key);
		}
		else if (command == "delete") 
		{
			// Get input key
			cin >> key;
			// Check that there is a node in the tree with the given key, else display -1
			if (myTree->search(key) == NULL)
			{
				cout << key;
				cout << " -1\n";
			}
			else
			{
				// Call remove function
				myTree->remove(key);
				myTree->displayNode(key);
			}
		}
		else if (command == "search")
		{
			// Get input key
			cin >> key;
			// Calls search function, display node searches then displays count
			myTree->displayNode(key);
		}
		else if (command == "min")
		{
			// Check if the tree is empty, then return a blank line, else return the key of min
			if (myTree->min() == NULL)
				cout << "\n";
			else
				cout << myTree->min()->getKey();
		}
		else if (command == "max")
		{
			// Check if the tree is empty, then return a blank line, else return the key of max
			if (myTree->max() == NULL)
				cout << "\n";
			else
				cout << myTree->max()->getKey();
		}
		else if (command == "next")
		{
			// Get input key
			cin >> key;
			// Call next function
			BSTNode* next = myTree->next(key);
			// Check for if next is NULL, display blank line
			if (next == NULL)
			{
				cout << "\n\n";
			}
			else
			{
				cout << next->getKey();
				cout << "\n";
			}
		}
		else if (command == "prev")
		{
			// Get input key
			cin >> key;
			// Call prev function
			BSTNode* prev = myTree->prev(key);
			// Check for if prev is NULL, display blank line
			if (prev == NULL)
			{
				cout << "\n\n";
			}
			else
			{
				cout << prev->getKey();
				cout << "\n";
			}
		}
		else if (command == "list")
		{
			// Call list function
			myTree->displayAll();
		}
		else if (command == "help")
		{
			// Display a list of possible commands
			cout << "List of commands: \ninsert <key> \ndelete <key>\nsearch <key>\nmin\nmax\nnext <key>\nprev <key>\nlist\nhelp\nexit\n";
		}
		else if (command == "exit")
		{
			// Set terminate to true
			cout << "Good bye!";
			terminate = true;
		}
		else // This case occurs if the input is not a command choice
		{
			// Display error message, allow next command
			cout << "Invalid command. Type 'help' for a list of commands.\n";
		}
	}
	
    return 0;
}

