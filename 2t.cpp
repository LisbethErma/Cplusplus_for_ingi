#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Matrix {
private:
    vector<vector<int>> mat;
    int size;

public:
    Matrix(int n) : size(n), mat(n, vector<int>(n, 0)) {}

    void fillSpiral(bool clockwise) {
        int num = 1;
        int left = 0, right = size - 1;
        int top = 0, bottom = size - 1;

        if (clockwise) {
            while (left <= right && top <= bottom) {
                // Заполнение верхней строки слева направо
                for (int i = left; i <= right; ++i) {
                    mat[top][i] = num++;
                }
                ++top;

                // Заполнение правого столбца сверху вниз
                for (int i = top; i <= bottom; ++i) {
                    mat[i][right] = num++;
                }
                --right;

                // Заполнение нижней строки справа налево
                if (top <= bottom) {
                    for (int i = right; i >= left; --i) {
                        mat[bottom][i] = num++;
                    }
                    --bottom;
                }

                // Заполнение левого столбца снизу вверх
                if (left <= right) {
                    for (int i = bottom; i >= top; --i) {
                        mat[i][left] = num++;
                    }
                    ++left;
                }
            }
        } else {
            while (left <= right && top <= bottom) {
                // Заполнение левого столбца сверху вниз
                for (int i = top; i <= bottom; ++i) {
                    mat[i][left] = num++;
                }
                ++left;

                // Заполнение нижней строки слева направо
                for (int i = left; i <= right; ++i) {
                    mat[bottom][i] = num++;
                }
                --bottom;

                // Заполнение правого столбца снизу вверх
                if (left <= right) {
                    for (int i = bottom; i >= top; --i) {
                        mat[i][right] = num++;
                    }
                    --right;
                }

                // Заполнение верхней строки справа налево
                if (top <= bottom) {
                    for (int i = right; i >= left; --i) {
                        mat[top][i] = num++;
                    }
                    ++top;
                }
            }
        }
    }

    void print() const {
        for (const auto& row : mat) {
            for (int val : row) {
                cout << val << "\t";
            }
            cout << endl;
        }
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));
    int N = 3 + rand() % 8; // Случайное число от 3 до 10
    bool clockwise = rand() % 2; // Случайный выбор направления обхода

    Matrix matrix(N);
    matrix.fillSpiral(clockwise);

    cout << "Размер матрицы: " << N << " x " << N << endl;
    cout << (clockwise ? "Обход по часовой стрелке:" : "Обход против часовой стрелки:") << endl;
    matrix.print();

    return 0;
}
