// Name: Sachin Mahawar
// Rollno: B20129

#ifndef _FIB_HEAP_H
#define _FIB_HEAP_H

#include <bits/stdc++.h>
#include <cmath>
using namespace std;
#include "seqLinearList.hpp"

class node
{
public:
	int label;	  // label for node
	int key;	  // Value stored in the node.
	int degree;	  // Number of children.
	node *parent; // pointer to parent node
	node *child;  // pointer to one of the child node
	node *left;	  // Left sibling
	node *right;  // Right sibling
	char mark;	  // to detect if a child of node is removed or not

	node() {}
	~node() {}
};

/**
 * Represents head of the fibonacci heap.
 * It should always point to the node containing minimum value.
 */
class Fibonacci_Heap
{
public:
	int numberOfNodes;
	node *minNode;

	Fibonacci_Heap() {}
	~Fibonacci_Heap() {}
};

class FibonacciHeap
{

public:
	Fibonacci_Heap *H;

	/**
	 * Constructor
	 */
	FibonacciHeap()
	{
		H = new Fibonacci_Heap();
		node *newNode;
		newNode = NULL;

		H->minNode = newNode;
		H->numberOfNodes = 0;
	}

	/**
	 * Destructor
	 */
	~FibonacciHeap() {}

	/**
	 * Function Make_Fib_Heap.
	 * Returns an instance of Fibonacci_Heap.
	 */
	Fibonacci_Heap *Make_Fib_Heap()
	{
		return H;
	}

	/**
	 * Function Fib_Heap_Insert.
	 * Inserts a given integer x into Fibonacci_Heap.
	 * Returns object of the Fibonacci_Heap after insertion.
	 */
	Fibonacci_Heap *Fib_Heap_Insert(Fibonacci_Heap *H, int lab, int val)
	{
		// Initializing new node
		node *x = new node();
		x->label = lab;
		x->child = NULL;
		x->parent = NULL;
		x->degree = 0;
		x->key = val;
		x->left = x;
		x->right = x;
		x->mark = '0';

		// Adding new node to root list
		if (H->minNode == NULL)
		{
			H->minNode = x;
		}
		else
		{
			(H->minNode->left)->right = x;
			x->right = H->minNode;
			x->left = H->minNode->left;
			H->minNode->left = x;

			if (val < H->minNode->key) // Updating minNode
			{
				H->minNode = x;
			}
		}
		H->numberOfNodes++;
		return H;
	}

	/**
	 * Function Fib_Heap_Union.
	 * Combines two fibonacci heaps with objects obj1 and obj2.
	 * Returns object of the combined Fibonacci_Heap.
	 */
	Fibonacci_Heap *Fib_Heap_Union(Fibonacci_Heap *H1, Fibonacci_Heap *H2)
	{
		Fibonacci_Heap *H = Make_Fib_Heap();
		H->minNode = H1->minNode;
		H->numberOfNodes = H1->numberOfNodes;

		// Concatenation of root lists
		node *a = H->minNode->right;
		node *b = H2->minNode->left;

		H->minNode->right = H2->minNode;
		H2->minNode->left = H->minNode;
		a->left = b;
		b->right = a;

		// updating minimum key node
		if (H1->minNode == NULL || (H2->minNode != NULL && H2->minNode->key < H1->minNode->key))
		{
			H->minNode = H2->minNode;
		}

		H->numberOfNodes = H1->numberOfNodes + H2->numberOfNodes;
		return H;
	}

	/**
	 * Function Extract_Min.
	 * Deletes node containing minimum value from the Fibonacci_Heap.
	 * Returns this node containing minimun value.
	 */
	node *Extract_Min(Fibonacci_Heap *&H)
	{
		if (H->minNode != NULL)
		{
			node *res = H->minNode;
			node *tmp = H->minNode->child;

			if (tmp != NULL)
			{
				// Counting child of H.minNode
				int children = 0;
				node *cnt = tmp;
				do
				{
					children++;
					cnt = cnt->right;
				} while (cnt != tmp);

				// For each child, move it to root list
				while (children--)
				{
					node *nxt = tmp->right;
					if (tmp->left != tmp)
					{
						(tmp->left)->right = tmp->left;
						(tmp->right)->left = tmp->left;
					}

					(H->minNode->left)->right = tmp;
					tmp->right = H->minNode;
					tmp->left = H->minNode->left;
					H->minNode->left = tmp;

					tmp->parent = NULL;
					tmp = nxt;
				}
			}

			H->numberOfNodes--;

			// Removing/Extracting MinNode from root list, then Consolidating Fib-Heap
			if (H->minNode->right == H->minNode)
			{
				H->minNode = NULL;
			}
			else
			{
				(H->minNode->right)->left = H->minNode->left;
				(H->minNode->left)->right = H->minNode->right;
				H->minNode->child = NULL;

				node *tt = H->minNode->right;
				// cout << tt->key << "\n";

				H->minNode->left = H->minNode;
				H->minNode->right = H->minNode;
				H->minNode = tt;

				Consolidate(H);
			}
			return res;
		}
		else
		{
			return NULL;
		}
	}

	/**
	 * Function Fib_Heap_Display.
	 * Prints the Fibonacci_Heap.
	 */
	void display(node *x)
	{
		if (x == NULL)
			return;
		node *tmp = x;
		do
		{
			cout << tmp->key << "(";
			display(tmp->child);
			cout << ")->";
			tmp = tmp->right;
		} while (tmp != x);
	}

	void Fib_Heap_Display(Fibonacci_Heap *H)
	{
		display(H->minNode);
		cout << "\n";
	}

	/**
	 * Function Fib_Heap_Find.
	 * Finds the value x in the Fibonacci_Heap.
	 * Returns the node containing value x, otherwise null.
	 */
	node *fib_find(node *h, int lab)
	{
		node *tmp = h;
		do
		{
			if (tmp->label == lab)
				return tmp;
			tmp = tmp->right;
		} while (tmp != h);

		tmp = h;
		node *res = NULL;
		do
		{
			if (tmp->child != NULL)
			{
				if (res == NULL)
					(res) = fib_find(tmp->child, lab);
			}
			tmp = tmp->right;
		} while (tmp != h);
		return (res);
	}

	node *Fib_Heap_Find(Fibonacci_Heap *H, int lab)
	{
		if (H->minNode == NULL)
			return NULL;
		return fib_find(H->minNode, lab);
	}

	/**
	 * Function Consolidate.
	 * Rearranges the Fibonacci_Heap.
	 */
	Fibonacci_Heap *Consolidate(Fibonacci_Heap *H)
	{
		// Creating Auzilary array
		int sz = (H->numberOfNodes + 1) / 2 + 1; // Took extra space to avoid overflow
												 // (Total nodes)/2 instead of (total nodes in root list)/2
		node *Aux[sz];
		for (int i = 0; i < sz; i++)
			Aux[i] = NULL;

		node *w = H->minNode;
		node *st = H->minNode;

		// Storing children of H.minNode in children array
		node *gg = w;
		vector<node *> children;
		do
		{
			children.push_back(gg);
			gg = gg->right;
		} while (gg != H->minNode);

		for (auto &w : children)
		{
			node *x = w;
			node *nxt = w->right;
			int deg = w->degree;

			// Merging heaps will we get single heap of particular degree
			while (Aux[deg] != NULL)
			{
				node *y = Aux[deg];

				if (x->key > y->key)
				{
					node *t = x;
					x = y;
					y = t;
				}

				// remove y from root list
				(y->left)->right = y->right;
				(y->right)->left = y->left;

				y->right = y;
				y->left = y;
				y->parent = x;

				// Merging y in silbling list of node child of node x
				if (x->child == NULL)
				{
					x->child = y;
				}
				else
				{
					node *Ch = x->child;
					if (Ch->left == Ch)
					{
						Ch->right = y;
						Ch->left = y;
						y->left = Ch;
						y->right = Ch;
					}
					else
					{
						(Ch->left)->right = y;
						y->right = Ch;
						y->left = Ch->left;
						Ch->left = y;
					}
					if (Ch->key > y->key)
					{
						x->child = y;
					}
				}

				x->degree++;

				y->mark = '0';
				Aux[deg] = NULL;
				deg++;
			}
			Aux[deg] = x; // Putting current node in Auxilary array
		}

		H->minNode = NULL;

		// Finding new H.minNode from root list
		for (int i = 0; i < sz; i++)
		{
			if (Aux[i] != NULL)
			{
				if (H->minNode == NULL || H->minNode->key > Aux[i]->key)
				{
					H->minNode = Aux[i];
				}
			}
		}
		return H;
	}

	// To cut the edge between node x and its parent node
	void Cut(Fibonacci_Heap *H, node *x, node *par)
	{
		// Cutting edge
		x->left->right = x->right;
		x->right->left = x->left;

		if (x != x->right)
			par->child = x->right;
		else
			par->child = NULL;

		par->degree--;

		// Adding node X to root list of Fib-Heap
		(H->minNode->left)->right = x;
		x->right = H->minNode;
		x->left = H->minNode->left;
		H->minNode->left = x;

		// Updating H.minNode
		if (x->key < H->minNode->key)
		{
			H->minNode = x;
		}

		x->mark = '0';
		x->parent = NULL;
	}

	// Function to recursively cur edges till we get non marked('0') node
	void CascadingCut(Fibonacci_Heap *H, node *y)
	{
		node *z = y->parent;
		if (z != NULL)
		{
			if (y->mark == '0')
			{
				y->mark = '1';
			}
			else
			{
				Cut(H, y, z);
				CascadingCut(H, z);
			}
		}
	}

	/**
	 * Function Fib_Heap_Decrease_key.
	 * Decreases the value x to new value k.
	 * If operation is successful returns true otherwise false.
	 */
	void Fib_Heap_Decrease_key(Fibonacci_Heap *H, int lab, int k)
	{
		node *x = Fib_Heap_Find(H, lab);

		if (x == NULL)
		{
			cout << "No node with this value in FibHeap\n";
			return;
		}

		x->key = k;

		if (x->parent != NULL && x->parent->key > x->key)
		{
			node *par = x->parent;
			Cut(H, x, x->parent); // cutting X to x.parent edge
			CascadingCut(H, par); // recursively cutting edge if parent edge is marked and parent.key>x.key
		}
		else
		{
			if (x->key < H->minNode->key)
			{
				H->minNode = x;
			}
		}

		// cout << x->label << ": " << x->key << "\n";
	}

	/**
	 * Function Fib_Heap_Delete_key.
	 * Deletes the given value k from the Fibonacci_Heap.
	 * If operation is successful returns true otherwise false.
	 */
	void Fib_Heap_Delete_key(Fibonacci_Heap *H, int lab)
	{
		Fib_Heap_Decrease_key(H, lab, INT32_MIN);
		Extract_Min(H);
	}

	/**
	 * Function get_number_of_nodes.
	 * Returns total number of nodes present in the Fibonacci_Heap.
	 */
	int get_number_of_nodes(Fibonacci_Heap *H)
	{
		return H->numberOfNodes;
	}
};

#endif
