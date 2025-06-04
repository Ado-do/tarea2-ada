#include <iostream>
#include <string>

using namespace std;

int editDistanceRecursive(string &s1, string &s2, int i, int j)
{
    if (i == 0 || j == 0) {
        if (i == 0) return j; // s1 recorrida completamente, se insertan los j caracteres restantes de s2
        if (j == 0) return i; // s2 recorrida completamente, se borran los i caracteres restantes de s1
    }

    if (s1[i-1] == s2[j-1])
        // s1 y s2 coinciden, no se necesita una operacion
        return editDistanceRecursive(s1, s2, i-1, j-1);
    else
        // s1 y s2 no coinciden, se elige la mejor opcion entre eliminar o insertar un caracter
        return 1 + min(editDistanceRecursive(s1, s2, i-1, j), editDistanceRecursive(s1, s2, i, j-1));
}

int main()
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);

    cout << "s1 = \"" << s1 << "\"\n"
         << "s2 = \"" << s2 << "\"\n"
         << "editDistanceRecursive(s1, s2) =" << editDistanceRecursive(s1, s2, s1.length(), s2.length()) << '\n';

    return 0;
}
