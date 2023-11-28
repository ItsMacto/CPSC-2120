#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> numbers;
    vector<string> rNum(numbers.size());
    for (int i = 0; i < numbers.size(); i++)
    {
       
    }
    
    {
        
    }
    
}


vector<string> romanizer(vector<int> numbers) {
    
    const vector<pair<int, string>> roman{
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    vector<string> rNum(numbers.size());
    
    for (int i = 0; i < numbers.size(); i++){
        for (const auto &value : roman) {
            while (numbers[i] >= value.first) {
                rNum[i] += value.second;
                numbers[i] -= value.first;
            }
        }
    }
    return rNum;
}