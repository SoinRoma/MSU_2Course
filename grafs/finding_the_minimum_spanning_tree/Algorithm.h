#include <vector>
#include <string>
#include "Function.h"

class Algorithm {
public:
    void print(string filename, int p, vector<vector<int>> &g);
    void printforvector(string filename, int p, vector<vector<int>> &g);
    vector<vector<int>> read(string filename);
    bool cycle(vector<vector<int>> &r, int target, int  current, int previous, int &steps);
    int algo(vector<vector<int>> &g, vector<vector<int>> &r, int &steps);
    int solveformatrica(string input, string output);
    int solveforvector(string input, string output);
};



