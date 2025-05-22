#include <iostream>
#include <string>

using namespace std;

int RecursiveStep(string &s1, string &s2, int n, int m) {
    // Caso subsecuencia no encontrada
    if (n == 0 || m == 0) return 0;

    // Caso coinciden al final (restar a los dos)
    if (s1[n - 1] == s2[m - 1]) {
        return RecursiveStep(s1, s2, n - 1, m - 1) + 1;
    }

    // Caso no coinciden al final (se resta a la mas conveniente)
    return max(RecursiveStep(s1, s2, n - 1, m), RecursiveStep(s1, s2, n, m - 1));
}

int LCSLength(string &s1, string &s2) {
    int n = s1.length(), m = s2.length();
    return RecursiveStep(s1, s2, n, m);
}

int EditDistanceDeleteInsert(string &s1, string &s2) {
    // Tamaño de la Longest Common Subsequence
    // (Subsequence de una string: es la secuencia de caracteres de una string, no necesariamente
    // continua, que mantiene su orden relativo respecto a la string original
    // (ex. "Alonso" -> "Aoso")) en este caso buscamos la mas larga en comun entre las strings

    int len = LCSLength(s1, s2);

    int minDeletions = s1.length() - len;
    int minInsertions = s2.length() - len;

    int total = minDeletions + minInsertions;
    return total;
}

int main() {
    string s1, s2;
    getline(cin, s1); getline(cin, s2);

    int editDist = EditDistanceDeleteInsert(s1, s2);
    printf("EditDistance entre\n\ts1 (%2ld) = \"%s\"\n\ts2 (%2ld) = \"%s\"\nes\n\t%d\n",
            s1.length(), s1.c_str(), s2.length(), s2.c_str(), editDist);

    return 0;
}
