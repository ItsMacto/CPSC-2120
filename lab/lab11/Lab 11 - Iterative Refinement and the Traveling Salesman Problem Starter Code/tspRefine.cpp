/*
 * Name: Mac Howe 
 * Date Submitted: Dec 10
 * Lab Section: 002 
 * Assignment Name: Traveling Salesman Problem
 */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

const int N = 14; //Number of cities in cities.txt
typedef pair<double,double> Point; //<latitude,longitude> of a city
vector<Point> P(N), best; //P - current solution, best - best solution
map<Point, int> cities; //Point (latitude,longitude) -> index of city in cities.txt order
string cityNames[] = {"New York City",
                      "Chicago",
                      "Los Angeles",
                      "Toronto",
                      "Houston",
                      "Montreal",
                      "Mexico City",
                      "Vancouver",
                      "Atlanta",
                      "Denver",
                      "San Juan",
                      "New Orleans",
                      "Miami",
                      "Kansas City"}; //Index of a city -> city name

//Calculates "distance"
//Units are lat./long. "degrees" on an x-y plane
//to simplify calculations (not mi/km on globe)
double dist(int i, int j)
{
  double dx = P[(i+N)%N].first - P[(j+N)%N].first;
  double dy = P[(i+N)%N].second - P[(j+N)%N].second;
  return sqrt(dx*dx + dy*dy);
}

bool refine(double &len)
{
  //Implement this function
  //Should iterate through each pair of edges in the tour
  //checking if there is a decrease in tour length by
  //replacing these edges with their diagonals (see lab description)

  //If the decrease is more than a minimum threshold (such as 0.0001)
  //swap these edges for their diagonals (see description) and return true

  //Otherwise return false after iterating through all possible edge pairs
  //if swapping a pair of edges for their diagonals fails to decrease
  //tour length beyond a minimum threshold
 const double minThreshold = 0.001;
    bool improved = false;
    for (int i = 0; i < N-2; i++) {
        for (int j = i + 2; j < N-1; j++) {
            int next_i = (i + 1) % N;
            int next_j = (j + 1) % N;

            double oldDist = dist(i, next_i) + dist(j, (j + 1) % N);
            double newDist = dist(i, j) + dist(next_i, next_j);
            if (newDist + minThreshold < oldDist) {
                // Handle wrap-around case
                if (next_j == 0) {
                    reverse(P.begin() + next_i, P.end());
                    reverse(P.begin(), P.begin() + j + 1);
                } else {
                    reverse(P.begin() + next_i, P.begin() + next_j);
                }
                len -= (oldDist - newDist);
                improved = true;
            }
        }
    }
    return improved;
}

//Returns best length for test case
double tspRefine()
{
  double best_len = 999999999;
  ifstream fin("cities.txt");
  for (int i=0; i<N; i++)
  {
    fin >> P[i].first >> P[i].second;
    cities[P[i]] = i;
  }
  
  //Use a loop that will repeat a certain number of times starting with
  //a randomly generated tour (P)
  //First calculate the length of this randomly generated tour
  //Then run refine() to rearrange the ordering of the cities in the
  //tour until refine() returns false
  //Finally, if final tour length < best_len replace best with the
  //current tour (P) and update best_len


  random_device rd;
  mt19937 g(rd());

  int epoch = 2000;
  for (int i = 0; i < epoch; i++)
  {
    shuffle(P.begin(), P.end(), g);

    double current_len = 0;


    for (int j = 0; j < N; j++){
      current_len += dist(j, (j + 1) % N);
    }

    while (refine(current_len)){
    };

    if (current_len < best_len){
      best_len = current_len;
      best = P;
    }
    
  }
  

  for (auto p : best) cout << cityNames[cities[p]] << endl;
  cout << "\nTotal length: " << best_len << "\n";
  return best_len;
}

