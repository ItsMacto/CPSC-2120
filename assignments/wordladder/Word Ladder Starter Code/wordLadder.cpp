#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<string> V;
unordered_map<string, vector<string>> adjList;
unordered_map<string, string> predecessor;
unordered_map<string, int> wordDistance;

bool differByOne(const string &a, const string &b)
{
  int count = 0;
  for (int i = 0; i < a.length(); i++)
  {
    if (a[i] != b[i])
      count++;
    if (count > 1)
      return false;
  }
  return count == 1;
}

void createGraph()
{
  for (const string &word1 : V)
  {
    for (const string &word2 : V)
    {
      if (differByOne(word1, word2))
      {
        adjList[word1].push_back(word2);
      }
    }
  }
}

void bfs(const string &s, const string &t)
{
  queue<string> q;
  q.push(s);
  wordDistance[s] = 0;

  while (!q.empty())
  {
    string current = q.front();
    q.pop();

    for (const string &neighbor : adjList[current])
    {
      if (wordDistance.find(neighbor) == wordDistance.end())
      {
        wordDistance[neighbor] = wordDistance[current] + 1;
        predecessor[neighbor] = current;
        q.push(neighbor);

        if (neighbor == t)
          return;
      }
    }
  }
}

void wordLadder(string s, string t, int &steps, vector<string> &path)
{
  ifstream file("wordlist05.txt");
  string word;
  while (file >> word)
  {
    V.push_back(word);
  }
  file.close();

  createGraph();

  bfs(s, t);

  if (wordDistance.find(t) != wordDistance.end())
  {
    steps = wordDistance[t];
    while (t != s)
    {
      path.insert(path.begin(), t);
      t = predecessor[t];
    }
    path.insert(path.begin(), s);
  }
  else
  {
    steps = 0;
  }
}
