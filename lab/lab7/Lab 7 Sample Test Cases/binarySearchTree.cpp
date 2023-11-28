/*
 * Name: Mac Howe 
 * Date Submitted: 11/8/23
 * Lab Section: 002
 * Assignment Name: Binary Search Tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

#include "binarySearchTree.h"

using namespace std;

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  vector<int> rhs;
  if (T == nullptr) return inorder;
  inorder=inorder_traversal(T->left);
  inorder.push_back(T->key);
  rhs=inorder_traversal(T->right);
  inorder.insert(inorder.end(), rhs.begin(), rhs.end());
  return inorder;
}

// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node *find(Node *T, int k)
{

if(T == nullptr){
  return T;
}

  if (T->key == k) return T;
  else if (k < T->key) return find(T->left, k);
  else return find(T->right, k);

}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T != nullptr && r >= 0 && r < T->size);

  int leftSize = (T->left != nullptr) ? T->left->size : 0; 

  
  if (r < leftSize) {
    return select(T->left, r); 
  } 
  
  else if (r > leftSize) {
    return select(T->right, r - leftSize - 1); 
  }
  
  return T; 
}


// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.  
Node *join(Node *L, Node *R)
{
  if (L == nullptr) return R;
  if (R == nullptr) return L;


  double probability = L->size / (L->size + R->size);
  double randomValue = rand() / (double)RAND_MAX;
  if (randomValue <= probability) {
    L->right = join(L->right, R); 
    fix_size(L);
    return L;
  } else {
    R->left = join(L, R->left); 
    fix_size(R);
    return R; 
  }
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k)
{
  assert(T != nullptr);

  if(T->key == k){
    Node *L = T->left;
    Node *R = T->right;

    delete T;

    return join(L, R);
  }else if (k < T->key) {
    T->left = remove(T->left, k);
  } else {
        T->right = remove(T->right, k);
  }

  fix_size(T);
  return T;
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R)
{
if (T == nullptr) {
    *L = nullptr;
    *R = nullptr;
    return;
  }

  if (T->key <= k) {
   
    *L = T; 
    split(T->right, k, &(T->right), R); 
  } else {
   
    *R = T; 
    split(T->left, k, L, &(T->left)); 
  }

  fix_size(T); 
}

// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k) {
 
  if (T == nullptr) {
    return new Node(k);
  }

  int N = T->size + 1;

  int r = rand() % N;

  if (r == 0) {
    Node *newNode = new Node(k);
    split(T, k, &(newNode->left), &(newNode->right));
    fix_size(newNode);
    return newNode;
  } else {
    if (k < T->key) {
      T->left = insert_random(T->left, k);
    } else {
      T->right = insert_random(T->right, k);
    }
    fix_size(T);
    return T;
  }
}


void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

// int main(void)
// {
//   vector<int> inorder;
//   vector<int> A(10,0);
  
//   // put 0..9 into A[0..9] in random order
//   for (int i=0; i<10; i++) A[i] = i;
//   for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
//   cout << "Contents of A (to be inserted into BST):\n";
//   printVector(A);
  
//   // insert contents of A into a BST
//   Node *T = nullptr;
//   for (int i=0; i<10; i++) T = insert(T, A[i]);
  
//   // print contents of BST (should be 0..9 in sorted order)
//   cout << "Contents of BST (should be 0..9 in sorted order):\n";
//   inorder=inorder_traversal(T);
//   printVector(inorder);

//   // test select
//   for (int i=0; i<10; i++) {
//     Node *result = select(T, i);
//     if (!result || result->key != i) cout << "Select test failed for select(" << i << ")!\n";
//   }

//   // test find: Elements 0..9 should be found; 10 should not be found
//   cout << "Elements 0..9 should be found; 10 should not be found:\n";
//   for (int i=0; i<11; i++) 
//     if (find(T,i)) cout << i << " found\n";
//     else cout << i << " not found\n";

//   // test split
//   Node *L, *R;
//   split(T, 4, &L, &R);
//   cout << "Contents of left tree after split (should be 0..4):\n";
//   inorder=inorder_traversal(L);
//   printVector(inorder);
//   cout << "Left tree size " << L->size << "\n";
//   cout << "Contents of right tree after split (should be 5..9):\n";
//   inorder=inorder_traversal(R);
//   printVector(inorder);
//   cout << "Right tree size " << R->size << "\n";
    
//   // test join
//   T = join(L, R);
//   cout << "Contents of re-joined tree (should be 0..9)\n";
//   inorder=inorder_traversal(T);
//   printVector(inorder);
//   cout << "Tree size " << T->size << "\n";
  
//   // test remove
//   for (int i=0; i<10; i++) A[i] = i;
//   for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
//   for (int i=0; i<10; i++) {
//     T = remove(T, A[i]);
//     cout << "Contents of tree after removing " << A[i] << ":\n";
//     inorder=inorder_traversal(T);
//     printVector(inorder);
//     if (T != nullptr)
//       cout << "Tree size " << T->size << "\n";
//   }

//   // test insert_random
//   cout << "Inserting 1 million elements in order; this should be very fast...\n";
//   for (int i=0; i<1000000; i++) T = insert_random(T, i);
//   cout << "Tree size " << T->size << "\n";
//   cout << "Done\n";
  
//   return 0;
// }
