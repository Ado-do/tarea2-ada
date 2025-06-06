#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int editDistanceDPOptimized(const string& s1, const string& s2)
{
    int n = s1.length(), m = s2.length();

    // Siempre trabajamos con la menor cadena como fila para ahorrar espacio (menos columnas)
    if (m < n) return editDistanceDPOptimized(s2, s1);  // intercambiamos

    vector<int> anterior(m + 1), actual(m + 1);

    // convertir "" en s2[..] mediante inserciones
    for (int j = 0; j <= m; ++j) anterior[j] = j;

    for (int i = 1; i <= n; ++i) {
        actual[0] = i;  // borrar todos los de s1[..] para volverse ""

        for (int j = 1; j <= m; ++j) {  // Mismos casos que en la versión no optimizada (cuando el caracter coincide o no)
            if (s1[i - 1] == s2[j - 1]) {
                actual[j] = min({anterior[j] + 1, actual[j - 1] + 1, anterior[j - 1]});

            } else {
                actual[j] = min(anterior[j] + 1, actual[j - 1] + 1);
            }
        }

        // Intercambiar filas: la actual se vuelve la anterior
        swap(anterior, actual);
    }

    int resultado = anterior[m];

    return resultado;
}

int main()
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    auto start = chrono::high_resolution_clock::now();
    int dist = editDistanceDPOptimized(s1, s2);
    auto end = chrono::high_resolution_clock::now();

    auto duration_ns = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Distancia de edicion optimizada: " << dist << '\n'
         << "Tiempo utilizado: " << duration_ns.count() << endl;

    return 0;
}
