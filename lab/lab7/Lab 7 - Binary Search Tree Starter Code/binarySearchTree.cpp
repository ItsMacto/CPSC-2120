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
  if (T->left)
    T->size += T->left->size;
  if (T->right)
    T->size += T->right->size;
}

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr)
    return new Node(k);
  if (k < T->key)
    T->left = insert(T->left, k);
  else
    T->right = insert(T->right, k);
  fix_size(T);
  return T;
}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  vector<int> rhs;
  if (T == nullptr)
    return inorder;
  inorder = inorder_traversal(T->left);
  inorder.push_back(T->key);
  rhs = inorder_traversal(T->right);
  inorder.insert(inorder.end(), rhs.begin(), rhs.end());
  return inorder;
}

// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node *find(Node *T, int k)
{

  if (T == nullptr)
  {
    return T;
  }

  if (T->key == k)
    return T;
  else if (k < T->key)
    return find(T->left, k);
  else
    return find(T->right, k);
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T != nullptr && r >= 0 && r < T->size);

  int leftSize = (T->left != nullptr) ? T->left->size : 0;

  if (r < leftSize)
  {
    return select(T->left, r);
  }

  else if (r > leftSize)
  {
    return select(T->right, r - leftSize - 1);
  }

  return T;
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.
Node *join(Node *L, Node *R)
{
  if (L == nullptr)
    return R;
  if (R == nullptr)
    return L;

  double probability = L->size / (L->size + R->size);
  double randomValue = rand() / (double)RAND_MAX;
  if (randomValue <= probability)
  {
    L->right = join(L->right, R);
    fix_size(L);
    return L;
  }
  else
  {
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

  if (T->key == k)
  {
    Node *L = T->left;
    Node *R = T->right;

    delete T;

    return join(L, R);
  }
  else if (k < T->key)
  {
    T->left = remove(T->left, k);
  }
  else
  {
    T->right = remove(T->right, k);
  }

  fix_size(T);
  return T;
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R)
{
  if (T == nullptr)
  {
    *L = nullptr;
    *R = nullptr;
    return;
  }

  if (T->key <= k)
  {

    *L = T;
    split(T->right, k, &(T->right), R);
  }
  else
  {

    *R = T;
    split(T->left, k, L, &(T->left));
  }

  fix_size(T);
}

// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k)
{

  if (T == nullptr)
  {
    return new Node(k);
  }

  int N = T->size + 1;

  int r = rand() % N;

  if (r == 0)
  {
    Node *newNode = new Node(k);
    split(T, k, &(newNode->left), &(newNode->right));
    fix_size(newNode);
    return newNode;
  }
  else
  {
    if (k < T->key)
    {
      T->left = insert_random(T->left, k);
    }
    else
    {
      T->right = insert_random(T->right, k);
    }
    fix_size(T);
    return T;
  }
}

void printVector(vector<int> v)
{
  for (int i = 0; i < v.size(); i++)
  {
    cout << v[i] << endl;
  }
}
