/*
 * Name: Mac Howe 
 * Date Submitted:Oct 29
 * Lab Section: 002
 * Assignment Name: Closest Pair of points
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
  double x;
  double y;
};

/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
                  remaining (#of points) lines: x-value and y-value of point
                  one point per line
                  x-value and y-value are double-precision values and
                  bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/
double closestPair(string filename);
double checkPoints(double min, point p1, point p2);


double closestPair(string filename)
{
  ifstream inFile(filename);
  if (!inFile)
  {
    cerr << "Unable to open file";
    exit(1);
  }

  int numPoints;
  inFile >> numPoints;

  int b = sqrt(numPoints); // use numPoints

  vector<vector<vector<point>>> grid(b, vector<vector<point>>(b));

  double x, y;

  for (int i = 0; i < numPoints; i++) {
    inFile >> x >> y;
    point p = {x, y};

    int xi = static_cast<int>(x * b);
    int yi = static_cast<int>(y * b);

    grid[yi][xi].push_back(p);
  }

  double minDistance = 1;

  for (int i = 0; i < b; i++)
  {
    for (int j = 0; j < b; j++)
    {
      for (auto &point : grid[i][j])
      {
        for (int dx = -1; dx <= 1; dx++)
                {
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        int ni = i + dy;
                        int nj = j + dx;
                        if (ni >= 0 && ni < b && nj >= 0 && nj < b)
                        {
                            for (const auto &compareP : grid[ni][nj])
                            {
                                minDistance = checkPoints(minDistance, point,
                                 compareP);
                            }
                        }
                    }
                }
            }
        }
    }

    return minDistance;
}

double checkPoints(double min, point p1, point p2)
{
  double distance;
  if (p1.x != p2.x && p1.y != p2.y)
  {
    distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    if (distance < min)
      min = distance;
  }
  return min;
}
