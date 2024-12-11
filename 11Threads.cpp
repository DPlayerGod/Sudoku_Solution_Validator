#include <iostream>
#include <pthread.h>
#include <vector>
#include <time.h>
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

// Cấu trúc dữ liệu để truyền tham số cho luồng
typedef struct {
    int row;
    int column;
} parameters;

// Mảng lưu kết quả của các luồng
bool results[11];

// Hàm kiểm tra hàng
void* checkRows(void* param) {
    bool seen[N + 1] = {false};
    for (int i = 0; i < N; i++) {
        fill(seen, seen + N + 1, false);
        for (int j = 0; j < N; j++) {
            if (seen[sudoku[i][j]]) {
                results[0] = false;
                pthread_exit(NULL);
            }
            seen[sudoku[i][j]] = true;
        }
    }
    results[0] = true;
    pthread_exit(NULL);
}

// Hàm kiểm tra cột
void* checkCols(void* param) {
    bool seen[N + 1] = {false};
    for (int j = 0; j < N; j++) {
        fill(seen, seen + N + 1, false);
        for (int i = 0; i < N; i++) {
            if (seen[sudoku[i][j]]) {
                results[1] = false;
                pthread_exit(NULL);
            }
            seen[sudoku[i][j]] = true;
        }
    }
    results[1] = true;
    pthread_exit(NULL);
}

// Hàm kiểm tra ô 3x3
void* checkGrid(void* param) {

    parameters* data = (parameters*)param;
    int startRow = data->row;
    int startCol = data->column;

    bool seen[N + 1] = {false};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int value = sudoku[startRow + i][startCol + j];
            if (seen[value]) {
                results[2 + startRow / 3 * 3 + startCol / 3] = false;
                pthread_exit(NULL);
            }
            seen[value] = true;
        }
    }
    results[2 + startRow / 3 * 3 + startCol / 3] = true;
    delete data;
  
    pthread_exit(NULL);

}

int main() {
    auto start = clock();
    pthread_t threads[11];
    int threadIndex = 0;

    // Tạo luồng kiểm tra hàng
    pthread_create(&threads[threadIndex++], NULL, checkRows, NULL);

    // Tạo luồng kiểm tra cột
    pthread_create(&threads[threadIndex++], NULL, checkCols, NULL);

    // Tạo luồng kiểm tra các ô 3x3
    for (int i = 0; i < N; i += 3) {
        for (int j = 0; j < N; j += 3) {
            parameters* data = new parameters{i, j};
            pthread_create(&threads[threadIndex++], NULL, checkGrid, data);
        }
    }

    // Chờ tất cả các luồng hoàn thành
    for (int i = 0; i < 11; i++) {
        pthread_join(threads[i], NULL);
    }

    // Kiểm tra kết quả
    for (int i = 0; i < 11; i++) {
        if (!results[i]) {
            cout << "Sudoku không hợp lệ." << endl;
            auto end = clock();
            cout << "Thời gian thực thi: " << (double)(end - start) / CLOCKS_PER_SEC << " giây" << endl;
            return 0;
        }
    }
    cout << "Sudoku hợp lệ." << endl;
    auto end = clock();
    cout << "Thời gian thực thi: " << (double)(end - start) / CLOCKS_PER_SEC << " giây" << endl;
    return 0;
}
