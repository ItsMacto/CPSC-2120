/*
 * Name: Mac Howe
 * Date Submitted:
 * Assignment Name: Single-Word Anagram Finder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> loadWordlist(string filename);

/*Implement the following function:
  anagram() takes a word (string) and a wordlist of all words (vector of strings)
  and builds a dictionary/map where the key is a specific number of times each
  letter occurs in a word and the associated value is a vector of strings
  containing all words using those letters (anagrams).
  The value returned is a vector of strings containing the corresponding
  set of anagrams
*/
vector<string> anagram(string word, vector<string> wordlist);

// int main()
// {
//     vector<string> words;
//     vector<string> anagrams;
//     string inputWord;
//     words=loadWordlist("wordlist.txt");
//     do
//     {
//     cout << "Find single-word anagrams for the following word: ";
//     cin >> inputWord;
//     anagrams = anagram(inputWord, words);
//     for (int i=0; i<anagrams.size(); i++)
//     {
//         cout << anagrams[i] << endl;
//     }
//     } while(1);

//     return 0;
// }

vector<string> loadWordlist(string filename)
{
    vector<string> words;
    ifstream inFile;
    string word;
    inFile.open(filename);
    if(inFile.is_open())
    {
        while(getline(inFile,word))
        {
            if(word.length() > 0)
            {
                words.push_back(word);
            }
        }
        inFile.close();
    }
    return words;
}

//Implement this function
vector<string> anagram(string anagramWord, vector<string> wordlist)
{
unordered_map<string, vector<string>> map;
    auto createKey = [](string word) {
        vector<int> count(26, 0);
        for (char c : word)
        {
            count[c - 'a']++;
        }
        string key = "";
        for (int i = 0; i < 26; i++)
        {
            if (count[i] > 0)
            {
                key += ('a' + i);
                key += to_string(count[i]);
            }
        }
        return key;
    };
    

    for (string word : wordlist)
    {
        string key = createKey(word);
        map[key].push_back(word);
    }

    return map[createKey(anagramWord)];

}
