using namespace std;
#include <iostream>
#include "binstree.h"

// constructor  initializes Root
BST::BST()
{
  Root = NULL;   // This is an empty tree
}

// destructor must completely destroy the tree
BST::~BST()
{
  dtraverse(Root); // traverse to delete all vertices in post order
  Root = NULL;    
}
// PURPOSE: Does Post Order traversal of the tree and deletes each vertex
// PARAM:   V is a pointer to the vertex to be deleted
void BST::dtraverse(Vertex *V)  // recursive post order traversal
{   
  if (V != NULL) 
    {
      dtraverse(V->Left);         // destroy left sub tree of V
      dtraverse(V->Right);       //  destroy right sub tree of V
      delete V;                  //  delete V
    }
}

// PURPOSE: Show vertices in IN order traversal from the Root
void BST::Display()
{
  cout << "Elements in the IN order: " << endl;
  INorderTraversal(Root);  // start in-order traversal from the root
}
// PURPOSE: Does IN order traversal from V recursively
// PARAM: V is te pointer to the vertex to visit right now
// For non EC, the height and balance will always be 0 
void BST::INorderTraversal(Vertex *V)
{
  if (V != NULL)
    {
      // ** traverse left sub-tree of V recursively
      INorderTraversal(V->Left);
      // ** display V's element, height and balance and do endl;
      cout <<  V->Elem <<  endl;
      // ** traverse right sub-tree of V recursively
      INorderTraversal(V->Right);
    }
}

// PURPOSE: Searches for an element in PRE-order traversal
// This is the same as Depth First Traversal
bool BST::Search(el_t K)
{
  
  return PREorderSearch(Root, K);  // start pre-order traversal from the root
  
}
// PURPOSE: Does PRE order search from V recursively
// PARAM: V is the pointer to the vertex to be visited now
//        K is what we are looking for
bool BST::PREorderSearch(Vertex *V, el_t K)
{
    if(V != NULL)
      {
        if (K == V->Elem) 
	  {

	    return true; // found the element in V
	    
	  }
	else if (K < V->Elem)  //** traverse left sub-tree of V recursively
	  {

	    return PREorderSearch(V->Left, K);
	  }
	else //** traverse right sub-tree of V recursively
	  {

	    return PREorderSearch(V->Right, K);
	  }
      }
    else
      {

	return false;
      }
}

// ------ The following are for adding and deleting vertices -----


// PURPOSE: Adds a vertex to the binary search tree for a new element 
// PARAM: the new element E
// ALGORITHM: We will do this iteratively (not recursively)
// to demonstrate the algorithm that is in the notes
//    - smaller than the current -> go to the left
//    - bigger than the current  -> go to the right
//    - cannot go any further    -> add it there
void BST::InsertVertex(el_t E)
{
  // Set up a new vertex first
   Vertex *N;         // N will point to the new vertex to be inserted
   N = new Vertex;    // a new vertex is created
   N->Left  = NULL;   // make sure it does not
   N->Right = NULL;   // point to anything
   N->Elem = E;      // put element E in it
   N->Height = 0;
   N->Balance = 0;
   N->Up = NULL;      // no parent for now
   //   cout << "Trying to insert " << E << endl;

   if (Root == NULL)  // Special case: we have a brand new empty tree
     {
       Root = N;      // the new vertex is added as the root
       //       cout << "...adding " << E << " as the root" << endl; 
     }// end of the special case

   else  // the tree is not empty
     {
        Vertex *V;       // V will point to the current vertex
        Vertex *Parent;  // Parent will point to V's parent

        V = Root;        // start with the root as V

	// go down the tree until you cannot go any further        
	while (V != NULL)
	  {
	    if (N->Elem == V->Elem) // the element already exists
              {	 cout << "...error: the element already exists" << endl;
		return;  
	      }
	    else
	      { 
		if(N->Elem < V->Elem)  // what I have is smaller than V
		  { // cout << "...going to the left" << endl; 
		    // ** change Parent to be V to go down
		    Parent=V;
		    // ** change V to be V's Left
		    V=V->Left;
		  }
	      
		else // what I have is bigger than V
		  { // cout << "...going to the right" << endl;
		    // ** change Parent to be V to go down
		    Parent=V;
		    // ** change V to be V's Right
		    V=V->Right;
		  }
	      }
	  }//end of while
	    
   // reached NULL -- Must add N as the Parent's child
        
        if (N->Elem < Parent->Elem)  
          {  
	    // ** Parent's Left should point to the same place as N
	    Parent->Left = N;
            // ** N should point UP to the Parent
	    N->Up = Parent;
	    // cout << "...adding " << E << " as the left child of " << Parent->Elem << endl;
            // ** EC call here 	
	  }
        else 
	  {
	    // ** Parent's Right should point to the same place as N
	    Parent->Right = N;
            // ** N should point UP to the Parent
	    N->Up = Parent;
	    
	    // cout << "...adding " << E << " as the right child of "  << Parent->Elem << endl;
	    // ** EC call here
	  }
	
     }// end of normal case

}// end of InsertVertex


// PURPOSE: Deletes a vertex that has E as its element.
// PARAM: element E to be removed
// ALGORITHM: First we must find the vertex then call Remove
void BST::DeleteVertex(el_t E)
{
  // cout << "Trying to delete " << E << endl;
  
  Vertex *V;              // the current vertex
  Vertex *Parent;
  // case 1: Lonely Root  
  if ((E == Root->Elem) && (Root->Left == NULL && Root->Right == NULL))
    {// cout << "...deleting the lonely root" << endl;
      delete Root; 
      Root = NULL;
      return; 
    }  // only the Root was there and deleted it
  
  // case 2:  One Substree Root
  // ** if what you want to delete is the root
  if((E == Root->Elem) && ((Root->Left != NULL && Root->Right == NULL) || (Root->Right != NULL && Root->Left == NULL)))
    {
      // ** and it has only the left subtree
      if(Root->Left != NULL)
	{  //** change the root to the left child and return
	  Root = Root->Left;
	  
	}
      // ** and it has only the right subtree
      else 
	{ // ** change the root to the right child and return
	  Root = Root->Right;
	  
	}
      return;
    }
    // end of deleting the root with one subtree
  
  // Otherwise deleting something else
  
  V = Root;  // start with the root to look for E
  
  // going down the tree looking for E
  while (V != NULL)
    { 
      if (E == V->Elem)   // found it
	{ // cout << "...removing " << V->Elem << endl;
	  // ** call remove here to remove V
	  remove(V,Parent);
	  return; 
	}
      
      else 
	{
	  if (E < V->Elem)
	    { // cout << "...going to the left" << endl;
	      // ** update Parent and V here to go down
	      Parent = V;
	      V = V->Left;
	    }
	  else
	    { // cout << "...going to the right" << endl;
	      // ** update Parent and V here to go down
	      Parent = V;
	      V = V->Right;
	    }
	}      
    }// end of while
  
  // reached NULL  -- did not find it
  cout << "Did not find the element in the tree." << endl;
  
}// end of DeleteVertex


// PURPOSE: Removes vertex pointed to by V
// PARAM: V and its parent  pointer P
// Case 1: it is a leaf, delete it
// Case 2: it has just one child, bypass it
// Case 3: it has two children, replace it with the max of the left subtree
void BST::remove(Vertex *V, Vertex *P)
{
  // ** if V is a leaf (case 1)
  if((V->Left == NULL) & (V->Right == NULL))
    {
      // cout << "removing a leaf" << endl;
	// ** if V is a left child of P
	if(P->Left == V)
	  { // ** delete V and also make Parent's left NULL
	    delete V;
	    P->Left = NULL;
	  }
	// ** EC call from P
	
	else // V is a right child of the Parent
	  { 
	    // ** delete V and also make Parent's right NULL 
	    delete V;
	    P->Right = NULL;
	    // ** EC call from P
	  }
    }//end of leaf case
    
  else if((V->Left == NULL && V->Right != NULL) || (V->Right == NULL && V->Left != NULL)) // ** if V has just the left child so bypass V (case 2)
	{
	  if(V->Left != NULL)
	    {
	      // cout << "removing a vertex with just the left child" << endl;
	      // ** You need if then else to determine Parent's left or right
	      if(P->Right == V)
		{
		  P->Right = V->Left;
		  delete V;
		}
	      else if (P->Left == V)
		{
		  P->Left = V->Left;
		  delete V;
		}

	    }
	  else if(V->Right!=NULL)
	    {
	      // cout << "removing a vertex with just the right child" << endl;
	      if(P->Right == V)
                {
                  P->Right = V->Right;
                  delete V;
                }
              else if (P->Left == V)
                {
                  P->Left = V->Right;
                  delete V;
                }

	    }
	}

  else if(V->Left != NULL && V->Right !=NULL)
    {
      //  cout << "removing an internal vertex with children" << endl;
      // cout << "..find the MAX of its left sub-tree" << endl;
      el_t Melem;
      Melem = findMax(V);
      // cout << "..replacing " << V->Elem << " with " << Melem << endl;
      V->Elem = Melem;
    }
  
  // ** should point to V's left child; 
  // ** Make the left child point UP to the parent;
  // ** Be sure to delete V
  // ** EC call from P
// end of V with left child       

// ** if V has just the right child so bypass V (case 2)
	
	
// ** You need if then else to determine Parent's left or right
// ** should point to V's right child; 
// ** Make the right child point UP to the parent;   
// ** Be sure to delete V
// ** EC call from P
//end of V with right child




// find MAX element in the left sub-tree of V


// ** Replace V's element with Melem here
//end of V with two children

// end of remove
}
// PURPOSE: Finds the Maximum element in the left sub-tree of V
// and also deletes that vertex
el_t BST::findMax(Vertex *V)
{
  Vertex *Parent = V;
  V = V->Left;          // start with the left child of V
  
  // ** while the right child of V is still available
  while(V->Right != NULL)
    {
      // ** update Parent and V to go to the right
      Parent=V;
      V=V->Right;
    }
  
  // reached NULL Right  -- V now has the MAX element
  el_t X = V->Elem;
  //cout << "...Max is " << X << endl;
  remove(V, Parent);    // remove the MAX vertex 
  return X;             // return the MAX element
  
}// end of FindMax

