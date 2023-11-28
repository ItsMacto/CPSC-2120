/*
 * Name: Mac Howe
 * Date Submitted: Oct 10 2023
 * Lab Section: 002
 * Assignment Name: Lab 5: Spell Checker Using a Hash Table
 */

#pragma once

#include <string>
#include <vector>
#include <list>
#include <functional>
using namespace std;

//Stringset class, do not modify definitions for existing members
class Stringset
{
    private:
        hash<string> stringHash;
        vector<list<string>> table;
        int num_elems;
        int size;
    public:
        Stringset();
        vector<list<string>> getTable() const;
        int getNumElems() const;
        int getSize() const;
        //inserts the word into the table
        void insert(string word);
        // returns true if the word exists
        bool find(string word) const;
        // will remove the word from the table
        void remove(string word);
        // will double the size of the table and re hash each word that was in it
        void reHash();
};