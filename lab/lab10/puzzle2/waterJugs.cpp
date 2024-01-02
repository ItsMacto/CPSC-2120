/*
 * Name: Mac Howe
 * Date Submitted: Nov 29 2023
 * Lab Section: 002
 * Assignment Name: Water Jugs
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int, int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;       // have we queued up this state for visitation?
map<state, state> pred;         // predecessor state we came from
map<state, int> dist;           // distance (# of hops) from source node
map<state, vector<state>> nbrs; // vector of neighboring states

map<pair<state, state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;

  while (!to_visit.empty())
  {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n])
      {
        pred[n] = curnode;
        dist[n] = 1 + dist[curnode];
        visited[n] = true;
        to_visit.push(n);
      }
  }
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t)
  {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": "
         << "[" << t.first << "," << t.second << "]\n";
  }
  else
  {
    cout << "Initial state: "
         << "[" << s.first << "," << s.second << "]\n";
  }
}

// A = size 3 and B = size 4
// goal to fill to 5
void build_graph(void)
{
  int capacityA = 3, capacityB = 4;

  for (int a = 0; a <= capacityA; a++)
  {
    for (int b = 0; b <= capacityB; b++)
    {
      state current = make_pair(a, b);

      // Fill jug A
      if (a < capacityA)
      {
        state new_state = make_pair(capacityA, b);
        nbrs[current].push_back(new_state);
        edge_label[make_pair(current, new_state)] = actions[0];
      }

      // Fill jug B
      if (b < capacityB)
      {
        state new_state = make_pair(a, capacityB);
        nbrs[current].push_back(new_state);
        edge_label[make_pair(current, new_state)] = actions[1];
      }

      // Empty jug A
      if (a > 0)
      {
        state new_state = make_pair(0, b);
        nbrs[current].push_back(new_state);
        edge_label[make_pair(current, new_state)] = actions[2];
      }

      // Empty jug B
      if (b > 0)
      {
        state new_state = make_pair(a, 0);
        nbrs[current].push_back(new_state);
        edge_label[make_pair(current, new_state)] = actions[3];
      }

      // Pour A -> B
      int pour = min(a, capacityB - b);
      if (pour > 0)
      {
        state new_state = make_pair(a - pour, b + pour);
        nbrs[current].push_back(new_state);
        edge_label[make_pair(current, new_state)] = actions[4];
      }

      // Pour B -> A
      pour = min(b, capacityA - a);
      if (pour > 0)
      {
        state new_state = make_pair(a + pour, b - pour);
        nbrs[current].push_back(new_state);
        edge_label[make_pair(current, new_state)] = actions[5];
      }
    }
  }
}

int main(void)
{
  build_graph();

  state start = make_pair(0, 0);

  for (int i = 0; i < 5; i++)
    nbrs[make_pair(i, 5 - i)].push_back(make_pair(-1, -1));
  search(start);
  if (visited[make_pair(-1, -1)])
    print_path(start, pred[make_pair(-1, -1)]);
  else
    cout << "No path!\n";

  return 0;
}
