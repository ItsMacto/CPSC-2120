/*
 * Name: Mac Howe
 * Date Submitted: 9/10/23
 * Lab Section: 002
 * Assignment Name: Linked List Based Stacks and Queues
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List{

 private:
  Node<T> * start; //pointer to the first node in this list
  int mySize;  //size (or length) of this list

 public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);

  //Print the name and this list's size and values to stdout
  //This function is already implemented (no need to change it)
  void print(string name){
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> * iterator = start;
    while(iterator != nullptr){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)

//Implement all of the functions below
//Construct an empty list by initializig this list's instance variables
template <class T>
List<T>::List(){
  start = nullptr;
  mySize = 0;
}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List(){
  Node<T> *node = start;
    while (node != nullptr) {
      Node<T> *next = node->next;
      delete node;
      node = next;
    }
}

//Return the size of this list
template <class T>
int List<T>::size(){
  return mySize;
}

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty(){
  return mySize == 0;
}

//Create a new node with value, and insert that new node
//into this list at start
template <class T>
void List<T>::insertStart(T value){
  Node<T> *newNode = new Node<T>(value);
  newNode->next = start;
  start = newNode;
  mySize++;
}

//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value){
  Node<T> *newNode = new Node<T>(value);
  if (start == nullptr) {
    start = newNode;
  }else {
    Node<T> *current = start;
    while (current->next != nullptr){
      current = current->next;
    }
    current->next = newNode;
  }
  mySize++;
}

//Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j){
  if(j<0 || j>mySize){
    return;
  }
  if(j == 0){
    insertStart(value);
  } else if(j == mySize){
    insertEnd(value);
  }else{
    Node<T> *newNode = new Node<T>(value);
    Node<T> *current = start;
    for (int i = 0; i < j - 1; i++){
      current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    mySize++;
  }
}

//Remove node at start
//Make no other changes to list
template <class T>
void List<T>::removeStart(){
  if (start == nullptr){
    return;
  }
  Node<T> *temp = start;
  start = start->next;
  delete temp; //memory leak
  mySize--;
}

//Remove node at end
//Make no other changes to list
template <class T>
void List<T>::removeEnd(){
  if (start == nullptr){
    return;
  }
  if(start->next == nullptr){
    delete start;
    start = nullptr;
} else {
    Node<T> *current = start;
    while (current->next->next != nullptr){
      current = current->next;
    }
    delete current->next;
    current->next = nullptr;
  }
  mySize--;
}

//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j){
    if (j < 0 || j >= mySize) {
        return;
    }
    if (j == 0) {
        removeStart();
    } else if (j == mySize - 1) {
        removeEnd();
    } else {
        Node<T> *current = start;
        for (int i = 0; i < j - 1; i++) {
            current = current->next;
        }
        Node<T> *temp = current->next;
        current->next = temp->next;
        delete temp;
        mySize--;
    }
}

//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst(){
    if (start == nullptr) {
        return T();
    }
    return start->value;
}

//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast(){
    if (start == nullptr) {
        return T();
    }
    Node<T> *current = start;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current->value;
}

//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j){
    if (j < 0 || j >= mySize) {
        return T();
    }
    Node<T> *current = start;
    for (int i = 0; i < j; i++) {
        current = current->next;
    }
    return current->value;
}

//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
template <class T>
int List<T>::find(T value){
    Node<T> *current = start;
    int index = 0;
    while (current != nullptr) {
        if (current->value == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}
