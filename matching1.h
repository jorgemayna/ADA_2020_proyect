#pragma once

#include <vector>
#include <utility>
#include <string> 
#include <opencv2/core.hpp>

using namespace std;
#define p 9
#define INF 9999999


struct Data {
    vector<pair<pair<int, int>, int >> M;
    vector<pair<pair<int, int>, int >> m;
    bool direccion;
};

void marcador();
void print_1(vector<pair<pair<int, int>, int >> V);
void print_matching(pair<vector<pair<int, int>>, pair<double, bool>> matching);


vector<pair<pair<int, int>, int >> bloques_final(string s, int pp);
vector<pair<pair<int, int>, int >> bloques_opencv(cv::Mat s, int row, int pp);
pair<vector<pair<int, int>>, pair<double, bool>> greedy(vector<pair<pair<int, int>, int >> A, vector<pair<pair<int, int>, int >> B);
pair<vector<pair<int, int>>, pair<double, bool>> recursivo(vector<pair<pair<int, int>, int >> A, vector<pair<pair<int, int>, int >> B);
pair<vector<pair<int, int>>, pair<double, bool>> memoizado(vector<pair<pair<int, int>, int >> A, vector<pair<pair<int, int>, int >> B);
pair<vector<pair<int, int>>, pair<double, bool>> p_dinamica(vector<pair<pair<int, int>, int >> A, vector<pair<pair<int, int>, int >> B);
