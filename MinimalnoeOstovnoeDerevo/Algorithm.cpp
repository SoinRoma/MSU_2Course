//Сам Алгоритм нашей задачи для нахождения минимального дерева
#include "Algorithm.h"

using namespace std;

void Algorithm::print(string filename, int p, vector<vector<int>> &g) {
    ofstream fout(filename);
    fout << p << endl;
    int max_weight = 0;
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g[i].size(); j++) {
            if (g[i][j] > max_weight) {
                max_weight = g[i][j];
            }
        }
    }
    space(g, g.size(), fout, max_weight);
    fout.close();
}

void Algorithm::printforvector(string filename, int p, vector<vector<int>> &g) {
    ofstream fout(filename);
    fout << p << endl;
    int max_weight = 0;
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g[i].size(); j++) {
            if (g[i][j] > max_weight) {
                max_weight = g[i][j];
            }
        }
    }
    spaceforvector(g, g.size(), fout, max_weight);
    fout.close();
}

//---------------------------------------------------------------
vector<vector<int>> Algorithm::read(string filename) {
    ifstream fin(filename);
    int n;
    fin >> n;
    // Считываем матрицу
    vector<vector<int>> g(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> g[i][j];
        }
    }
    fin.close();
    return g;
}

//target - то,куда мы хотим прийти, current - то, из какой вершины мы проверяем сейчас, previous - то, откуда мы пришли
//Проверяет, будет ли цикл при добавлении ребра (target, current, -1)
bool Algorithm::cycle(vector<vector<int>> &r, int target, int current, int previous, int &steps) {
    steps += 1;
    if (target == current) {
        return true;
    }

    for (int i = 0; i < r[current].size(); i++) {
        if (i != previous && r[current][i] > 0 && cycle(r, target, i, current, steps)) {
            return true;
        }
    }
    return false;
}

int Algorithm::algo(vector<vector<int>> &g, vector<vector<int>> &r, int &steps) {
    int p = 0;
    while (true) {
        int min = INT_MAX, k = -1, l = -1;
        for (int i = 0; i < g.size(); i++) {
            for (int j = i + 1; j < g.size(); j++) {
                steps += 1;
                if (0 < g[i][j] && g[i][j] < min) {
                    min = g[i][j];
                    k = i;
                    l = j;
                }
            }
        }
        if (k < 0) {
            break;
        }
        int d = g[k][l]; // вес минимального ребра
        g[k][l] = g[l][k] = 0;
        if (!cycle(r, k, l, -1, steps)) {
            r[k][l] = r[l][k] = d;
            p += d;
        }
    }
    return p;
}

int Algorithm::solveformatrica(string input, string output) {
    //vector<vector<int>> g = read("Input.txt");
    vector<vector<int>> g = read(input);
    vector<vector<int>> r(g.size(),
                          vector<int>(g.size(), 0)); //создаем вектор векторов(такой же как и у примера по размерам)
    int steps = 0;  //переменная для шагов
    int p = algo(g, r, steps);
    print(output, p, r);
    return steps;
}

int Algorithm::solveforvector(string input, string output) {
    vector<vector<int>> g = read(input);
    vector<vector<int>> r(g.size(),
                          vector<int>(g.size(), 0)); //создаем вектор векторов(такой же как и у примера по размерам)
    int steps = 0;  //переменная для шагов
    int p = algo(g, r, steps);
    printforvector(output, p, r);
    return steps;
}
