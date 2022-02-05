/****************************************************************************
 * This code cannot be redistributed without explicit written permission.                *
 ****************************************************************************/


#include <stdio.h>
#include "bst.h"

void bsn_init( bsn_t *node, S32 val) 
{
	node->val = val;
	node->left = NULL;
	node->right = NULL;
}


//Initialize the binary search tree so that it is empty. Run time: &Theta(1)
void bst_init( bst_t *tree ) 
{
	// FIXED INDENT
	tree->root = NULL;
	tree->size = 0;
}

//Remove all nodes from this binary search tree. Run time: T(n) with T(n) memory. 
//Note: Remember that you do not have to keep a search-tree structure while you are 
//destroying the tree. If you maintain the search-tree structure, the run time will be O(n2). 
void bst_destroy( bst_t *tree ) {}

//Return the number of nodes in the binary search tree. Run time: &Theta(1)
size_t bst_size( bst_t *tree ) 
{
	size_t treeSize = 0;
	treeSize = tree->size;
	return treeSize;
}

//Insert the integer n into the binary search tree and return false if n is 
//already in the tree (do not add a duplicate into the tree) and true otherwise. 
//Ideally, such a function should not be implemented using recursion. 
//See the marking scheme at the end. Run time: O(h)
bool bst_insert( bst_t *tree, S32 val ) 
{	
	bsn_t *p_currNode = tree->root;
	bsn_t *p_prevNode = p_currNode;
	bsn_t *p_newNode = (bsn_t *) malloc( sizeof( bsn_t ) );
	
	bsn_init(p_newNode, val);
	
	//special case: inserting at the root node
	if(p_currNode == NULL) 
	{
		// FIXED INDENT
		tree->root = p_newNode;
		tree->size = tree->size + 1;	
		return __TRUE;
	}
	
	//anything but root
	while (p_currNode != NULL) 
	{
		if (p_currNode->val == val) 
		{ 
			// the value is already in the tree, don't insert again
			free(p_newNode);
			return __FALSE;
		}
		else if (val < p_currNode->val) 
		{
			// move left in tree
			p_prevNode = p_currNode;
			p_currNode = p_currNode->left;
		}
		else 
		{ 
		    // move right in tree
			p_prevNode = p_currNode;
			p_currNode = p_currNode->right;
		}
	}
	
	//p_prevNode now points to the last node before the leaf where we are inserting
	if(p_prevNode->val > val) //insert as left child
		p_prevNode->left = p_newNode;
	else //insert as right child
		p_prevNode->right = p_newNode; // m to n change 
	
	tree->size = tree->size + 1;
	
	return __TRUE;
}


// Returns the smallest integer in the binary search tree. Return INT_MAX if the tree is empty. Run time: O(h)
S32 bst_min( bst_t *tree ) 
{
	bsn_t *p_currNode = tree->root;
	
	if(tree->size == 0) 
		return INT_MAX;
	else 
	{ 
		// smallest int will be the left-most bottom node
		while(p_currNode->left != NULL) 
			p_currNode = p_currNode->left; // FIXED INDENT
	}
	
	return p_currNode->val;
}


// Returns the largest integer in the binary search tree. Return INT_MIN if the tree is empty. Run time: O(h)
S32 bst_max( bst_t *tree ) // U32 to S32
{
	bsn_t *p_currNode = tree->root;
	
	if(tree->size == 0)
	{
		return INT_MIN;
	}
	else
	{ 
		//largest int will be the right-most bottom node
		while(p_currNode->right != NULL) 
			p_currNode = p_currNode->right;
	}
	
	return p_currNode->val;
}

// Perform the actual deletion of the node
// There are three possible cases:
//	1. It is a leaf node
//  2. It has only one child
//	3. It has two children
void bst_delete ( bsn_t * p_currNode, bsn_t * p_parentNode) // added pointer to parameters
{
	bsn_t *p_swapNode = NULL;
	bsn_t *p_swapParent = NULL;
	
	// case 1: leaf node, just delete
	if((p_currNode->right == NULL) && (p_currNode->left == NULL)) 
	{
		// FIXED INDENT
		//update the pointer on the parent node to NULL
		if(p_parentNode->left == p_currNode) 
		{
			p_parentNode->left = NULL; // FIXED INDENT
		}
		else 
		{
			p_parentNode->right = NULL; // FIXED INDENT
		}
	}
	// case 3: two children, pick one to replace with
	// balancing was not a parameter, so we will always take max of left branch to replace it with
	else if ((p_currNode->right != NULL) && (p_currNode->left != NULL)) // LOGIC ERROR: added another &
	{
		p_swapNode = p_currNode->left;
		p_swapParent = p_currNode;
		
		// traverse until we find the max of the subtree
		while(p_swapNode->right  != NULL) 
		{
			p_swapParent = p_swapNode;
			p_swapNode = p_swapNode->right; // LOGIC ERROR: changed left to right
		}
		
		// we now have the max of the subtree. By definition, it can only have one left or no children.
		// if it is a leaf, we can simply copy the value into the current node and delete the leaf instead
		p_currNode->val = p_swapNode->val;
		
		// FIXED INDENT
		if(p_swapParent->left == p_swapNode) 
			p_swapParent->left = p_swapNode->left; 
		// FIXED INDENT
		else 
			p_swapParent->right = p_swapNode->left;

		p_currNode = p_swapNode;
	}
	// case 2: one child, replace with child, delete child
	else
	{
		if(p_currNode->left != NULL) //child is to the left
		{
			// need to know whether we are to the left or right of the parent
			if(p_parentNode->left == p_currNode)
			{
				p_parentNode->left = p_currNode->left; // SYNTAX: changed . to ->
			}
			else
			{
				p_parentNode->right = p_currNode->left;
			}
		}
		else // child is to the right
		{
			// need to know whether we are to the left or right of the parent
			if(p_parentNode->left == p_currNode)
			{
				p_parentNode->left = p_currNode->right;// LOGIC ERROR: changed parentNode->right to left
			}
			else
			{
				p_parentNode->right = p_currNode->right;// LOGIC ERROR: changed parentNode->left to right
			}
		}
	}
	
	p_currNode->left = NULL;
	p_currNode->right = NULL;
	p_currNode->val = 0;
	free(p_currNode);
}

bool bst_erase( bst_t *tree, S32 val ) 
{
    bsn_t *p_currNode = tree->root;
    bsn_t *p_parentNode = p_currNode;
    
    while (p_currNode != NULL)
    {
        if (p_currNode->val == val)
        {
            if(p_parentNode == p_currNode) // we are removing the root with one child left
            {
                if((p_currNode->left != NULL) && (p_currNode->right != NULL)) 
                { 
                    // can swap in from left as usual
                    bst_delete ( p_currNode, p_parentNode);
                }
                else
                {
                    if ((p_currNode->left == NULL) && (p_currNode->right == NULL)) 
                    {
                        // last element in tree
                        tree->root = NULL;
                    }
                    else if (p_currNode->left != NULL) 
                    {
                        tree->root = p_currNode->left;
                    }
                    else
					{
						tree->root = p_currNode->right;
					} 
                    free(p_currNode);
                }
            }
            else 
            {
                bst_delete (p_currNode, p_parentNode);
            }
            tree->size -= 1;    //decrement size of the tree LOGIC ERROR:  + -> -
            return __TRUE;
        }
        else if (val < p_currNode->val) 
        { 
            //move left in tree
            p_parentNode = p_currNode;
            p_currNode = p_currNode->left;
        }
        else 
        { 
            //move right in tree
            p_parentNode = p_currNode;
            p_currNode = p_currNode->right;
        }
    } // added } SYNTAX  
	return __FALSE;
}