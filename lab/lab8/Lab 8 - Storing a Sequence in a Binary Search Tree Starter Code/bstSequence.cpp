/*
 * Name: Mac Howe
 * Date Submitted: Nov 15 2023
 * Lab Section: 002
 * Assignment Name: BST Sequence
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

#include "bstSequence.h"

using namespace std;

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

/*
// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}
*/

// insert value v at rank r
Node *insert(Node *T, int v, int r)
{ 

  if (T == nullptr) return new Node(v);

  int rank_of_root = T->left ? T->left->size : 0;

  if(r <= rank_of_root) T->left = insert(T->left, v, r);
  else T->right = insert(T->right, v, r - rank_of_root - 1);
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

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=nullptr && r>=0 && r<T->size);

  int rank_of_root = T->left ? T->left->size : 0;
  if (r == rank_of_root) return T;
  if (r < rank_of_root) return select(T->left, r);
  else return select(T->right, r - rank_of_root - 1);
}

// Split tree T on rank r into tree L (containing ranks < r) and 
// a tree R (containing ranks >= r)
void split(Node *T, int r, Node **L, Node **R) {
    if (!T) { *L = *R = nullptr; return; }

    int rootRank = T->left ? T->left->size : 0;
    if (r <= rootRank) {
        split(T->left, r, L, &T->left);
        *R = T;
    } else {
        split(T->right, r - rootRank - 1, &T->right, R);
        *L = T;
    }
    fix_size(T);
}


// insert value v at rank r
Node *insert_random(Node *T, int v, int r) {
    if (T == nullptr) return new Node(v);

    int n = T->size + 1;
    if (rand() % n == 0) {  // Insert at root with probability 1/n
        Node *L, *R;
        split(T, r, &L, &R);
        T = new Node(v);
        T->left = L;
        T->right = R;
    } else {
        int rank_of_root = T->left ? T->left->size : 0;
        if (r <= rank_of_root)
            T->left = insert_random(T->left, v, r);
        else
            T->right = insert_random(T->right, v, r - rank_of_root - 1);
    }
    fix_size(T);
    return T;
}


// Returns true if team x defeated team y
// Leave this function unmodified
bool did_x_beat_y(int x, int y)
{
  assert (x != y);
  if (x > y) return !did_x_beat_y(y,x);
  unsigned long long lx = x;
  unsigned long long ly = y;
  return ((17 + 8321813 * lx + 1861 * ly) % 1299827) % 2 == 0;
}

// Return a BST containing a valid ordering of n teams
Node *order_n_teams(int n) {
    Node *T = nullptr;

    // start by inserting the first team
    T = insert_random(T, 0, 0);

    // now insert the other teams...
    for (int i = 1; i < n; i++) {
        if (did_x_beat_y(i, select(T, 0)->key)) // can we insert at beginning?
            T = insert_random(T, i, 0);
        else if (did_x_beat_y(select(T, T->size - 1)->key, i)) // can we insert at end?
            T = insert_random(T, i, T->size);
        else {
            // Find the correct position using binary search
            int lo = 0, hi = T->size - 1;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (did_x_beat_y(select(T, mid)->key, i))
                    lo = mid + 1;
                else
                    hi = mid;
            }
            T = insert_random(T, i, lo);
        }
    }
    return T;
}


void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

int main(void)
{
  vector<int> inorder;
  Node *T = nullptr;

  // test insert at beginning
  for (int i=0; i<5; i++)
    T = insert_random(T, i+1, 0);
  cout << "Tree should contain 5 4 3 2 1:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test insert at end
  for (int i=5; i<10; i++)
    T = insert_random(T, i+1, T->size);
  cout << "Tree should contain 5 4 3 2 1 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  
  // test insert at middle
  for (int i=10; i<15; i++)
    T = insert_random(T, i+1, T->size/2);
  cout << "Tree should contain 5 4 3 2 1 12 14 15 13 11 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
    
  // once insert is working, the next step is to build the
  // insert_random function -- to test this, just change
  // calls to insert above to insert_random.

  int N = 100000; // this should run quickly even for very large N!
  Node *S = order_n_teams(N);
  if (S == nullptr || S->size != N)
    cout << "Size of tree returned by order_n_teams is wrong\n";
  else {
    cout << "Team ordering:\n";
    //    inorder=inorder_traversal(S);
    //    printVector(inorder);
    for (int i=0; i<N-1; i++) {
      Node *x = select(S, i);
      Node *y = select(S, i+1);
      if (!did_x_beat_y(x->key, y->key)) {
        cout << "Invalid sequence: team " << x->key << " (position " << i <<
	              ") lost to team " << y->key << " (position " << i+1 << ")\n";
      }
    }
  }  
  
  return 0;
}