#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int editDistanceMemo(string &s1, string &s2, int i, int j, vector<vector<int>> &memo)
{
    if (i < 0) return j + 1;  // s1 recorrida completamente, se insertan los j caracteres restantes de s2
    if (j < 0) return i + 1;  // s2 recorrida completamente, se borran los i caracteres restantes de s1

    if (memo[i][j] != -1) return memo[i][j];  // solucion ya computada

    if (s1[i] == s2[j])
        // s1 y s2 coinciden, no se necesita una operacion
        return memo[i][j] = editDistanceMemo(s1, s2, i-1, j-1, memo);
    else
        // s1 y s2 no coinciden, se elige la mejor opcion entre eliminar o insertar un caracter
        return memo[i][j] = 1 + min(editDistanceMemo(s1, s2, i-1, j, memo), editDistanceMemo(s1, s2, i, j-1, memo));
}

int main()
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    vector<vector<int>> memo(s1.length(), vector<int>(s2.length(), -1));
    auto start = std::chrono::high_resolution_clock::now();
    int edit_distance = editDistanceMemo(s1, s2, s1.length() - 1, s2.length() - 1, memo);
    auto end = std::chrono::high_resolution_clock::now();

    cout << "s1 = \"" << s1 << "\"\n"
         << "s2 = \"" << s2 << "\"\n"
         << "editDistanceMemo(s1, s2) = " << edit_distance << '\n';

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Tiempo utilizado: " << duration.count() << " ns" << endl;
    return 0;
}
