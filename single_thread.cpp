#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
using namespace std;

#define N 9

// Dữ liệu đầu vào: Bảng Sudoku
int sudoku[N][N] = {
    {1, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6} 
};

// Hàm kiểm tra hàng
bool checkRows() {
    bool seen[N + 1] = {false};
    for (int i = 0; i < N; i++) {
        fill(seen, seen + N + 1, false);
        for (int j = 0; j < N; j++) {
            if (seen[sudoku[i][j]]) return false;
            seen[sudoku[i][j]] = true;
        }
    }
    return true;
}

// Hàm kiểm tra cột
bool checkCols() {
    bool seen[N + 1] = {false};
    for (int j = 0; j < N; j++) {
        fill(seen, seen + N + 1, false);
        for (int i = 0; i < N; i++) {
            if (seen[sudoku[i][j]]) return false;
            seen[sudoku[i][j]] = true;
        }
    }
    return true;
}

// Hàm kiểm tra ô 3x3
bool checkGrid() {
    bool seen[N + 1] = {false};
    for (int row = 0; row < N; row += 3) {
        for (int col = 0; col < N; col += 3) {
            fill(seen, seen + N + 1, false);
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    int value = sudoku[row + i][col + j];
                    if (seen[value]) return false;
                    seen[value] = true;
                }
            }
        }
    }
    return true;
}

int main() {
    auto start = clock();

    // Kiểm tra hàng, cột, và các ô 3x3
    if (checkRows() && checkCols() && checkGrid()) {
        cout << "Sudoku hợp lệ." << endl;
    } else {
        cout << "Sudoku không hợp lệ." << endl;
    }

    auto end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Thời gian thực thi: " << fixed << setprecision(10) << time << endl;
    return 0;
}
