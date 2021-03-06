#include "matching1.h"
#include <iostream>
#include <string>
#include <map>

using namespace cv;
using namespace std;

vector<pair<int, int> > bloques_0(string s, int pp) {
    vector<pair<int, int> > R;
    bool in = false;
    pair<int, int> temp;
    for (int i = 0; i < pp; i++) {
        if (s[i] == '1' && !in) {
            in = true;
            temp.first = i;
        }
        if (s[i] == '0' && in) {
            in = false;
            temp.second = i - 1;
            R.push_back(temp);
        }
        if (i + 1 == pp && in) {
            temp.second = i;
            R.push_back(temp);
        }
    }
    return R;
}

vector<pair<int, int> > bloques_1(string s, int pp) {
    vector<pair<int, int> > R;
    int cont = 0;
    for (int i = 0; i < pp; i++) {
        if (s[i] == '1') {
            cont++;
            if (s[i + 1] == '0' || i + 1 == pp) {
                R.push_back(make_pair(i + 1 - cont, i));
                cont = 0;
            }
        }
    }
    return R;
}

vector<pair<int, int> > bloques_2(string s, int pp) {
    vector<pair<int, int> > R;
    int first;
    for (int i = 0; i < pp; i++) {
        if (s[i] == '1') {
            first = i;
            while (s[i] == '1')i++;
            R.push_back(make_pair(first, i - 1));
        }
    }
    return R;
}

vector<pair<pair<int, int>, int >> bloques_final(string s, int pp) {
    vector<pair<pair<int, int>, int >> R;
    int first;
    for (int i = 0; i < pp; i++) {
        if (s[i] == '1') {
            first = i;
            while (s[i] == '1')i++;
            R.push_back(make_pair(make_pair(first, i - 1), i - first));
        }
    }
    return R;
}

vector<pair<pair<int, int>, int >> bloques_opencv(Mat s,int row, int pp) {
    vector<pair<pair<int, int>, int >> R;
    int first;
    Scalar gg;
    for (int i = 0; i < pp; i++) {
        gg = s.at<uchar>(row, i);        
        if (gg.val[0] == 0) {
            first = i;            
            while (gg.val[0] == 0 && i+1<pp) {
                i++;
                gg = s.at<uchar>(row, i);
            }
            R.push_back(make_pair(make_pair(first, i - 1), i - first));
        }
    }
    return R;
}





void marcador() {
    for (int i = 0; i < p - 1 + 4; i++) {
        cout << " ";
    }
    cout << (char)124 << endl;
}

void print_0(vector<pair<int, int> > V) {
    for (auto i : V) {
        cout << "(" << i.first << "," << i.second << ") ";
    }
}
void print_1(vector<pair<pair<int, int>, int >> V) {
    for (auto i : V) {
        cout << i.second << "(" << i.first.first << "," << i.first.second << ") ";
    }
    cout << endl;
}

void print_matching(pair<vector<pair<int, int>>, pair<double, bool>> matching) {
    cout << "Matching (";
    if (matching.second.second) {
        cout << "B->A) = ";
    }
    else {
        cout << "A->B) = ";
    }
    print_0(matching.first);
    cout << " Peso: " << matching.second.first << endl;
}

auto dirrecion(vector<pair<pair<int, int>, int >> A, vector<pair<pair<int, int>, int >> B) {
    /*
    Data data;
    data.M = B;
    data.m = A;
    data.direccion = 1;

    if(A.size() >= B.size()){
      data.M = A;
      data.m = B;
      data.direccion = 0;
    }
    */
    Data data;
    data.M = A;
    data.m = B;
    data.direccion = 0;
    return data;
}

pair<vector<pair<int, int>>, pair<double, bool>> greedy(vector<pair<pair<int, int>, int >> A, vector<pair<pair<int, int>, int >> B) {
    auto d = dirrecion(A, B);
    vector<pair<int, int>> matching;
    double cont = 0;

    for (int i = 0; i < d.m.size(); i++) {
        matching.push_back(make_pair(i, i));
        cont = cont + (double)d.M[i].second / d.m[i].second;
    }
    for (int i = d.m.size(); i < d.M.size(); i++) {
        matching.push_back(make_pair(i, d.m.size() - 1));
        cont = cont + (double)d.M[i].second / d.m[d.m.size() - 1].second;
    }
    return make_pair(matching, make_pair(cont, d.direccion));
}
bool dividir(int tamano, int cantidad) {
    if (tamano >= cantidad)return true;
    return false;
}
double opt(int i, int j, vector<pair<pair<int, int>, int >>* A, vector<pair<pair<int, int>, int >>* B, vector<vector<vector<pair<int, int>>>>* ma_vec) {
    if (i == 0) {
        if (!dividir((*A)[i].second, j + 1))return INF;
        double cont = 0;
        for (int z = 0; z <= j; z++) {
            cont = cont + (*B)[z].second;
            (*ma_vec)[i][j].push_back(make_pair(i, z));
        }
        return ((double)(*A)[i].second) / cont;
    }
    if (j == 0) {
        double cont = 0;
        for (int z = 0; z <= i; z++) {
            cont = cont + (*A)[z].second;
            (*ma_vec)[i][j].push_back(make_pair(z, j));
        }
        return cont / (double)(*B)[j].second;
    }

    double uno = INF;
    vector<pair<int, int>> op1;
    for (int z = 0; z <= j - 1; z++) {
        if (!dividir((*A)[i].second, j - z))continue;
        double temp = 0;
        vector<pair<int, int>> v_temp;
        for (int zz = z + 1; zz <= j; zz++) {
            temp = temp + (*B)[zz].second;
            v_temp.push_back(make_pair(i, zz));
        }
        temp = opt(i - 1, z, A, B, ma_vec) + ((double)(*A)[i].second / temp);
        if (temp < uno) {
            uno = temp;
            op1 = (*ma_vec)[i - 1][z];
            op1.insert(op1.end(), v_temp.begin(), v_temp.end());
        }
    }

    double dos = INF;
    vector<pair<int, int>> op2;
    for (int z = 0; z <= i - 2; z++) {
        double temp = 0;
        vector<pair<int, int>> v_temp;
        for (int zz = z + 1; zz <= i; zz++) {
            temp = temp + (*A)[zz].second;
            v_temp.push_back(make_pair(zz, j));
        }
        temp = opt(z, j - 1, A, B, ma_vec) + (temp / (double)(*B)[j].second);
        if (temp < dos) {
            dos = temp;
            op2 = (*ma_vec)[z][j - 1];
            op2.insert(op2.end(), v_temp.begin(), v_temp.end());
        }
    }

    if (uno <= dos) {
        (*ma_vec)[i][j] = op1;
        return uno;
    }
    else {
        (*ma_vec)[i][j] = op2;
        return dos;
    }
}

pair<vector<pair<int, int>>, pair<double, bool>> recursivo(vector<pair<pair<int, int>, int >> A, vector<pair<pair<int, int>, int >> B) {
    auto d = dirrecion(A, B);
    vector<vector<vector<pair<int, int>>>> ma_vec;
    for (int i = 0; i < d.M.size(); i++) {
        ma_vec.push_back(vector<vector<pair<int, int>>>(d.m.size(), vector<pair<int, int>>()));
    }
    double peso = opt(d.M.size() - 1, d.m.size() - 1, &d.M, &d.m, &ma_vec);

    return make_pair(ma_vec[d.M.size() - 1][d.m.size() - 1], make_pair(peso, d.direccion));
}

double opt_m(int i, int j, vector<pair<pair<int, int>, int >>* A, vector<pair<pair<int, int>, int >>* B, vector<vector<vector<pair<int, int>>>>* ma_vec, vector<vector<double>>* memo) {
    if (i == 0) {
        if (!dividir((*A)[i].second, j + 1))return INF;
        double cont = 0;
        for (int z = 0; z <= j; z++) {
            cont = cont + (*B)[z].second;
            (*ma_vec)[i][j].push_back(make_pair(i, z));
        }
        (*memo)[i][j] = ((double)(*A)[i].second) / cont;
        return ((double)(*A)[i].second) / cont;
    }
    if (j == 0) {
        double cont = 0;
        for (int z = 0; z <= i; z++) {
            cont = cont + (*A)[z].second;
            (*ma_vec)[i][j].push_back(make_pair(z, j));
        }
        (*memo)[i][j] = cont / (double)(*B)[j].second;
        return cont / (double)(*B)[j].second;
    }

    double uno = INF;
    vector<pair<int, int>> op1;
    for (int z = 0; z <= j - 1; z++) {
        if (!dividir((*A)[i].second, j - z))continue;
        double temp = 0;
        vector<pair<int, int>> v_temp;
        for (int zz = z + 1; zz <= j; zz++) {
            temp = temp + (*B)[zz].second;
            v_temp.push_back(make_pair(i, zz));
        }
        double opt;
        if ((*memo)[i - 1][z] != -1) {
            opt = (*memo)[i - 1][z];
            cout << "memo" << endl;
        }
        else {
            cout << "nomemo" << endl;
            opt = opt_m(i - 1, z, A, B, ma_vec, memo);
        }
        temp = opt + ((double)(*A)[i].second / temp);
        if (temp < uno) {
            uno = temp;
            op1 = (*ma_vec)[i - 1][z];
            op1.insert(op1.end(), v_temp.begin(), v_temp.end());
        }
    }

    double dos = INF;
    vector<pair<int, int>> op2;
    for (int z = 0; z <= i - 2; z++) {
        double temp = 0;
        vector<pair<int, int>> v_temp;
        for (int zz = z + 1; zz <= i; zz++) {
            temp = temp + (*A)[zz].second;
            v_temp.push_back(make_pair(zz, j));
        }
        double opt;
        if ((*memo)[z][j - 1] != -1) {
            opt = (*memo)[z][j - 1];
            cout << "memo" << endl;
        }
        else {
            cout << "nomemo" << endl;
            opt = opt_m(z, j - 1, A, B, ma_vec, memo);
        }
        temp = opt + (temp / (double)(*B)[j].second);
        if (temp < dos) {
            dos = temp;
            op2 = (*ma_vec)[z][j - 1];
            op2.insert(op2.end(), v_temp.begin(), v_temp.end());
        }
    }

    if (uno <= dos) {
        (*ma_vec)[i][j] = op1;
        (*memo)[i][j] = uno;
        return uno;
    }
    else {
        (*ma_vec)[i][j] = op2;
        (*memo)[i][j] = dos;
        return dos;
    }
}

pair<vector<pair<int, int>>, pair<double, bool>> memoizado(vector<pair<pair<int, int>, int >> A, vector<pair<pair<int, int>, int >> B) {
    auto d = dirrecion(A, B);
    vector<vector<vector<pair<int, int>>>> ma_vec;
    vector<vector<double>> memo;
    for (int i = 0; i < d.M.size(); i++) {
        ma_vec.push_back(vector<vector<pair<int, int>>>(d.m.size(), vector<pair<int, int>>()));
        memo.push_back(vector<double>(d.m.size(), -1));
    }

    double peso = opt_m(d.M.size() - 1, d.m.size() - 1, &d.M, &d.m, &ma_vec, &memo);

    return make_pair(ma_vec[d.M.size() - 1][d.m.size() - 1], make_pair(peso, d.direccion));
}

pair<vector<pair<int, int>>, pair<double, bool>> p_dinamica(vector<pair<pair<int, int>, int >> A, vector<pair<pair<int, int>, int >> B) {
    auto d = dirrecion(A, B);
    vector<vector<vector<pair<int, int>>>> ma_vec;
    vector<vector<double>> memo;
    for (int i = 0; i < d.M.size(); i++) {
        ma_vec.push_back(vector<vector<pair<int, int>>>(d.m.size(), vector<pair<int, int>>()));
        memo.push_back(vector<double>(d.m.size(), -1));
    }

    for (int i = 0; i < d.M.size(); i++) {
        double cont1 = 0;
        for (int z = 0; z <= i; z++) {
            cont1 = cont1 + d.M[z].second;
            ma_vec[i][0].push_back(make_pair(z, 0));
        }
        memo[i][0] = cont1 / (double)d.m[0].second;

    }
    for (int i = 0; i < d.m.size(); i++) {
        /*
        if(!dividir(d.M[0].second,i+1)){
          memo[0][i] = INF;
          continue;
        }*/
        double cont2 = 0;
        for (int z = 0; z <= i; z++) {
            cont2 = cont2 + d.m[z].second;
            ma_vec[0][i].push_back(make_pair(0, z));
        }
        memo[0][i] = (double)d.M[0].second / cont2;
    }



    //cout << "pasa"<<endl;
    for (int j = 1; j < d.m.size(); j++) {
        for (int i = 1; i < d.M.size(); i++) {

            double uno = INF;
            vector<pair<int, int>> op1;
            for (int z = 0; z <= j - 1; z++) {
                //if(!dividir(d.M[i].second,j-z))continue;
                double temp = 0;
                vector<pair<int, int>> v_temp;
                for (int zz = z + 1; zz <= j; zz++) {
                    temp = temp + d.m[zz].second;
                    v_temp.push_back(make_pair(i, zz));
                }
                temp = memo[i - 1][z] + ((double)d.M[i].second / temp);
                if (temp < uno) {
                    uno = temp;
                    op1 = ma_vec[i - 1][z];
                    op1.insert(op1.end(), v_temp.begin(), v_temp.end());
                }
            }

            double dos = INF;
            vector<pair<int, int>> op2;
            for (int z = 0; z <= i - 2; z++) {
                double temp = 0;
                vector<pair<int, int>> v_temp;
                for (int zz = z + 1; zz <= i; zz++) {
                    temp = temp + d.M[zz].second;
                    v_temp.push_back(make_pair(zz, j));
                }
                temp = memo[z][j - 1] + (temp / (double)d.m[j].second);
                if (temp < dos) {
                    dos = temp;
                    op2 = ma_vec[z][j - 1];
                    op2.insert(op2.end(), v_temp.begin(), v_temp.end());
                }
            }

            if (uno <= dos) {
                ma_vec[i][j] = op1;
                memo[i][j] = uno;
            }
            else {
                ma_vec[i][j] = op2;
                memo[i][j] = dos;
            }

        }
    }

    return make_pair(ma_vec[d.M.size() - 1][d.m.size() - 1], make_pair(memo[d.M.size() - 1][d.m.size() - 1], d.direccion));
}