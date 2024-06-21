#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <stack>
#include <thread>
#include <chrono>

using namespace std;

int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

// Función para imprimir el laberinto y la solución en su estado actual
void imprimirLaberinto(const vector<vector<int>>& matriz, const vector<vector<int>>& solucion, int delay = 100) {
    system("cls"); // Limpia la pantalla
    int filas = matriz.size();
    int columnas = matriz[0].size();
    
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (solucion[i][j] == 1) {
                cout << " .";
            } else if (matriz[i][j] == 1) {
                cout << (char)178 << (char)178;
            } else {
                cout << "  ";
            }
        }
        cout << "\n";
    }
    cout << "\n";
    this_thread::sleep_for(chrono::milliseconds(delay)); // Pausa para visualizar el progreso
}

// Generar laberinto
void generarLaberinto(int filas, int columnas, vector<vector<int>>& matriz) {
    matriz.resize(filas, vector<int>(columnas, 1));
    
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = 1;
        }
    }

    srand(static_cast<unsigned int>(time(0)));

    stack<pair<int, int>> pila;
    int x = 1, y = 1;
    matriz[x][y] = 0;
    pila.push({x, y});

    while (!pila.empty()) {
        int cx = pila.top().first;
        int cy = pila.top().second;
        pila.pop();

        int dir[] = { 0, 1, 2, 3 };
        for (int i = 3; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(dir[i], dir[j]);
        }

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[dir[i]] * 2;
            int ny = cy + dy[dir[i]] * 2;

            if (nx > 0 && nx < filas - 1 && ny > 0 && ny < columnas - 1 && matriz[nx][ny] == 1) {
                matriz[nx][ny] = 0;
                matriz[cx + dx[dir[i]]][cy + dy[dir[i]]] = 0;
                pila.push({nx, ny});
            }
        }
    }

    // Crear una entrada y salida claras
    matriz[1][0] = 0;  // Entrada
    matriz[filas - 2][columnas - 1] = 0;  // Salida
}

// Verificar si una celda es válida
bool esValido(const vector<vector<int>>& matriz, int x, int y, const vector<vector<int>>& solucion) {
    int filas = matriz.size();
    int columnas = matriz[0].size();
    return (x >= 0 && x < filas && y >= 0 && y < columnas && matriz[x][y] == 0 && solucion[x][y] == 0);
}

// Algoritmo de backtracking para resolver el laberinto
bool resolverLaberinto(vector<vector<int>>& matriz, int x, int y, vector<vector<int>>& solucion) {
    int filas = matriz.size();
    int columnas = matriz[0].size();

    if (x == filas - 2 && y == columnas - 1) { // Condición de salida 
        solucion[x][y] = 1;
        imprimirLaberinto(matriz, solucion, 0); // Imprimir la solución final
        return true;
    }

    if (esValido(matriz, x, y, solucion)) {
        solucion[x][y] = 1;
        imprimirLaberinto(matriz, solucion); // Imprimir cada paso

        if (resolverLaberinto(matriz, x + 1, y, solucion)) {
            return true;
        }

        if (resolverLaberinto(matriz, x, y + 1, solucion)) {
            return true;
        }

        if (resolverLaberinto(matriz, x - 1, y, solucion)) {
            return true;
        }

        if (resolverLaberinto(matriz, x, y - 1, solucion)) {
            return true;
        }

        // Retroceso
        solucion[x][y] = 0;
        imprimirLaberinto(matriz, solucion); // Imprimir cada paso de retroceso
    }

    return false;
}

int main() {
    int filas = 20;
    int columnas = 20;

    vector<vector<int>> matriz;
    generarLaberinto(filas, columnas, matriz);

    vector<vector<int>> solucion(filas, vector<int>(columnas, 0));

    if (resolverLaberinto(matriz, 1, 0, solucion)) { // Comenzar desde la entrada
        cout << "Solucion encontrada:\n";
    } else {
        cout << "No se encontro solucion.\n";
    }

    system("pause");
    return 0;
}
