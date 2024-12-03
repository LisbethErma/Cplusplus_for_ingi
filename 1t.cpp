#include <iostream>
#include <vector>

using namespace std;

// Функция поиска всех элементов в трехмерном массиве, которые равны заданному значению
vector<vector<int>> findElements(int*** mtrx, int l, int m, int n, int z) {
    vector<vector<int>> coordinates; // Для хранения координат всех элементов, которые равны z

    // Перебор всех элементов трехмерного массива
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                if (mtrx[i][j][k] == z) { // Если элемент равен z
                    // Добавление координат элемента в результирующий вектор
                    coordinates.push_back({i, j, k});
                }
            }
        }
    }

    return coordinates; // Возвращение всех найденных координат
}

int main() {
    // Пример использования функции
    int l = 2, m = 2, n = 2;
    int z = 5;

    // Создание трехмерного массива размером 2x2x2
    int*** mtrx = new int**[l];
    for (int i = 0; i < l; ++i) {
        mtrx[i] = new int*[m];
        for (int j = 0; j < m; ++j) {
            mtrx[i][j] = new int[n];
            for (int k = 0; k < n; ++k) {
                mtrx[i][j][k] = (i + j + k) % 6; // Инициализация массива (пример)
            }
        }
    }

    // Вызов функции поиска
    vector<vector<int>> result = findElements(mtrx, l, m, n, z);

    // Вывод найденных координат
    if (result.empty()) {
        cout << "Элементы со значением " << z << " не найдены." << endl;
    } else {
        cout << "Элементы со значением " << z << " найдены на следующих координатах:" << endl;
        for (const auto& coord : result) {
            cout << "(" << coord[0] << ", " << coord[1] << ", " << coord[2] << ")" << endl;
        }
    }

    // Освобождение памяти
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < m; ++j) {
            delete[] mtrx[i][j];
        }
        delete[] mtrx[i];
    }
    delete[] mtrx;

    return 0;
}
