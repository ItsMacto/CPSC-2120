/*
 * Name: Mac Howe
 * Date Submitted: 11/20/23
 * Lab Section: 002
 * Assignment Name: nQueens
 */

#include <iostream>
#include <vector>

using namespace std;

bool isSafe(int row, int col, const vector<int> &position)
{
    for (int i = 0; i < row; ++i)
    {
        if (position[i] == col ||
            position[i] - i == col - row ||
            position[i] + i == col + row)
        {
            return false;
        }
    }
    return true;
}

int nQueens(int row, int n, vector<int> &position)
{
    if (row == n)
        return 1;
    int count = 0;
    for (int col = 0; col < n; ++col)
    {
        if (isSafe(row, col, position))
        {
            position[row] = col;
            count += nQueens(row + 1, n, position);
        }
    }
    return count;
}

int nQueens(int n)
{
    vector<int> position(n);
    int count = 0;
    int half = n / 2;

    // first half
    for (int i = 0; i < half; ++i)
    {
        position[0] = i;
        count += nQueens(1, n, position);
    }

    count *= 2;
    // if odd
    if (n % 2 != 0)
    {
        position[0] = half;
        count += nQueens(1, n, position);
    }
    return count;
}

int main()
{
    cout << "1: " << nQueens(1) << endl;
    cout << "2: " << nQueens(2) << endl;
    cout << "3: " << nQueens(3) << endl;
    cout << "4: " << nQueens(4) << endl;
    cout << "5: " << nQueens(5) << endl;
    cout << "6: " << nQueens(6) << endl;
    cout << "7: " << nQueens(7) << endl;
    cout << "8: " << nQueens(8) << endl;
    cout << "9: " << nQueens(9) << endl;
    cout << "10: " << nQueens(10) << endl;
    cout << "11: " << nQueens(11) << endl;
    cout << "12: " << nQueens(12) << endl;
    return 0;
}