#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int editDistanceDP(const string& s1, const string& s2)
{
    int n = s1.length(), m = s2.length();
    vector<vector<int>> M(n + 1, vector<int>(m + 1));

    // convertir S1[0...n] a cadena vacía mediante función delete
    for (int i = 0; i <= n; ++i) M[i][0] = i;

    // convertir de "" a S2[0...m] mediante función insert
    for (int j = 0; j <= m; ++j) M[0][j] = j;

    // convertir de s1[...] a s2[...] mediante inserciones y borrados
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s1[i - 1] == s2[j - 1]) {          // Si un caracter de s1 coincide con otro de s2 hay 3 casos
                M[i][j] = min({M[i - 1][j] + 1,    // Se borra de s1 para que sea s2
                               M[i][j - 1] + 1,    // Se inserta en s2 para que se convierta en s1
                               M[i - 1][j - 1]});  // Son iguales en la misma posición por lo que se mantiene
            } else {
                // Si no coinciden, hay 2 casos
                M[i][j] = min(M[i - 1][j] + 1,   // Se borra de s1 para transformarlo a s2
                              M[i][j - 1] + 1);  // Se inserta en s2 para transformarlo a s1
            }
        }
    }

    return M[n][m];
}

int main()
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    auto start = chrono::high_resolution_clock::now();
    int dist = editDistanceDP(s1, s2);
    auto end = chrono::high_resolution_clock::now();

    auto duration_ns = chrono::duration_cast<chrono::nanoseconds>(end - start);

    cout << "Distancia de edicion: " << dist << '\n'
         << "Tiempo utilizado: " << duration_ns.count() << endl;

    return 0;
}
