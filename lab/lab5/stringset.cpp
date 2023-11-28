/*
 * Name: Mac Howe
 * Date Submitted: Oct 10 2023
 * Lab Section: 002
 * Assignment Name: Lab 5: Spell Checker Using a Hash Table
 */

#include "stringset.h"

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

void Stringset::insert(string word)
{
    if (Stringset::find(word) == false){
        if (size == num_elems + 1){
            Stringset::reHash();
        }
        int wordIndex = stringHash(word) % size;
        table[wordIndex].push_back(word);
        num_elems++;
    }
}

bool Stringset::find(string word) const
{
    int wordIndex = stringHash(word) % size;
    for (auto& x : table[wordIndex]) {
        if (x == word) {
            return true;
        }
    }
    return false;
}

void Stringset::remove(string word)
{
    int wordIndex = stringHash(word) % size;
    for (auto it = table[wordIndex].begin(); it != table[wordIndex].end(); ++it) {
        if (*it == word) {
            table[wordIndex].erase(it);
            num_elems--;
            break;
        }
    }
}

void Stringset::reHash(){
    size = size * 2;
    vector<list<string>> tempTable(size);
    for(auto& list : table){
        for (auto &word : list){
            int wordIndex = stringHash(word) % size;
            tempTable[wordIndex].push_back(word);
        }
    }
    table = tempTable;
}