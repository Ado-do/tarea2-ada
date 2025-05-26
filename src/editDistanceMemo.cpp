#include <format>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int RecursiveMemoStep(string &s1, string &s2, int n, int m, vector<vector<int>> &memo)
{
    // Caso sub-secuencia no encontrada
    if (n == 0 || m == 0) return 0;

    // Case solución ya computado anteriormente
    if (memo[n-1][m-1] != -1) return memo[n-1][m-1];

    // Caso coinciden al final (restar a los dos)
    if (s1[n-1] == s2[m-1]) {
        return memo[n-1][m-1] = RecursiveMemoStep(s1, s2, n-1, m-1, memo) + 1;
    }

    // Caso no coinciden al final (se resta a la mas conveniente)
    return memo[n-1][m-1] = max(RecursiveMemoStep(s1, s2, n-1, m, memo), RecursiveMemoStep(s1, s2, n, m-1, memo));
}

int LCSLength(string &s1, string &s2)
{
    int n = s1.length(), m = s2.length();

    // Este es el vector que se utilizará para realizar la memorización de soluciones ya computadas
    vector<vector<int>> memo(n, vector<int>(m, -1));

    return RecursiveMemoStep(s1, s2, n, m, memo);
}

int main()
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    // Tamaño de la Longest Common Subsequence
    // (Subsequence de una string: es la secuencia de caracteres de una string,
    // no necesariamente continua, que mantiene su orden relativo respecto a la
    // string original (ex. "Alonso" -> "Aoso")) en este caso buscamos la mas
    // larga en común entre las strings
    int lcs_length = LCSLength(s1, s2);

    int deletes = s1.length() - lcs_length;
    int inserts = s2.length() - lcs_length;
    int total = deletes + inserts;

    cout << "EditDistance entre\n"
         << format("s1 ({:2}) =\n\t\"{}\"\n", s1.length(), s1) << format("s2 ({:2}) =\n\t\"{}\"\n", s2.length(), s2)
         << format("es\n\t{} (deletes = {}, inserts = {})\n", total, deletes, inserts);

    return 0;
}
