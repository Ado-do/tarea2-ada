#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

int editDistanceMemo(string &s1, string &s2, int i, int j, vector<vector<int>> &memo)
{
    if (i == 0 || j == 0) {
        if (i == 0) return j; // s1 recorrida completamente, se insertan los j caracteres restantes de s2
        if (j == 0) return i; // s2 recorrida completamente, se borran los i caracteres restantes de s1
    }

    if (memo[i-1][j-1] != -1) return memo[i-1][j-1]; // solucion ya computada

    if (s1[i-1] == s2[j-1])
        // s1 y s2 coinciden, no se necesita una operacion
        return memo[i-1][j-1] = editDistanceMemo(s1, s2, i-1, j-1, memo);
    else
        // s1 y s2 no coinciden, se elige la mejor opcion entre eliminar o insertar un caracter
        return memo[i-1][j-1] = 1 + min(editDistanceMemo(s1, s2, i-1, j, memo), editDistanceMemo(s1, s2, i, j-1, memo));
}

int main()
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    int s1_len = s1.length();
    int s2_len = s2.length();

    vector<vector<int>> memo(s1_len, vector<int>(s2_len, -1));
    auto start = std::chrono::high_resolution_clock::now();

    cout << "s1 = \"" << s1 << "\"\n"
         << "s2 = \"" << s2 << "\"\n"
         << "editDistanceMemo(s1, s2) = " << editDistanceMemo(s1, s2, s1_len, s2_len, memo) << '\n';
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    cout <<"Tiempo utilizado:" << duration.count() <<endl;
    return 0;
}
