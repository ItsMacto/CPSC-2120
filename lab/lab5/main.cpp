/*
 * Name: Mac Howe
 * Date Submitted: Oct 10 2023
 * Lab Section: 002
 * Assignment Name: Lab 5: Spell Checker Using a Hash Table
 */
 
 #include "stringset.h"
 #include <iostream>
 #include <fstream>
 
 void testStringset(Stringset& words);
 void loadStringset(Stringset& words, string filename);
 vector<string> spellcheck(const Stringset& words, string word);
 
//  int main()
//  {
//      Stringset wordlist;
//     //  testStringset(wordlist);
//     loadStringset(wordlist, "wordlist.txt");
//     // cout << wordlist.getSize() << endl;
//     vector<string> spell =spellcheck(wordlist, "pointer");
//     for (auto &word : spell)
//     {
//         cout << word << endl;
//     }
    

//     return 0;
//  }
 
 void testStringset(Stringset& words)
 {
     string choice;
     string word;
     do
     {
         cout << "I: insert word" << endl;
         cout << "F: find word" << endl;
         cout << "R: remove word" << endl;
         cout << "P: print words in stringset" << endl;
         cout << "Q: quit" << endl;
         cin >> choice;
         switch (choice[0])
         {
             case 'I':  
             case 'i':
                cout << "Enter word to insert: ";
                cin >> word;
                words.insert(word);
                break;
             case 'F':
             case 'f':
                cout << "Enter word to find: ";
                cin >> word;
                if (words.find(word))
                {
                    cout << word << " in stringset" << endl;
                }
                else
                {
                    cout << word << " not in stringset" << endl;
                }
                break;
             case 'R':
             case 'r':
                cout << "Enter word to remove: ";
                cin >> word;
                words.remove(word);
                break;
             case 'P':
             case 'p':
                vector<list<string>> t = words.getTable();
                int numWords = words.getNumElems();
                int tSize = words.getSize();
                for(int i=0; i<tSize; ++i)
                {
                    list<string>::iterator pos;
                    for (pos = t[i].begin(); pos != t[i].end(); ++pos)
                    {
                        cout << *pos << endl;
                    }
                }
                cout << "Words: " << numWords << endl;
         }
     } while (choice[0] != 'Q' && choice[0] != 'q');
 }
 
 void loadStringset(Stringset& words, string filename)
 {
    ifstream inFile(filename);
    string word;
    while(getline(inFile, word)){
        words.insert(word);
    }
 }
 
 vector<string> spellcheck(const Stringset& words, string word)
 {
    vector<string> suggestions;
    
    for (size_t i = 0; i < word.length(); i++)
    {
        for (char c = 'a'; c <= 'z'; c++) {
            if (word[i] != c){
                string newWord = word;
                newWord[i] = c;
                if(words.find(newWord)) suggestions.push_back(newWord);
            }

        }
    }
    return suggestions;
 }