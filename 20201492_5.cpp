#include <iostream>
using namespace std;

#define NO_PATH 0;

int matrixPath(int, int **);

void matrixPathPrint(int, int, int **);

int maxNum(int, int);

int main() {
    int n;
    cout << "n 값 입력 : ";
    cin >> n;
    int ** m = new int*[n+1];
    for (int i = 0; i <= n; i++) {
        m[i] = new int[n+1];
    }
    for (int i = 1; i <= n; i++) {
        cout << i << "행 입력 : ";
        for (int j = 1; j <= n; j++) {
            cin >> m[i][j];
        }
    }

    int num = matrixPath(n, m);

    cout << "\n";
    cout << "최대값 : " << num << endl;
    cout << "\n";

    matrixPathPrint(n, n, m);
    cout << "\n";

    // 동적할당 해제 코드
    for (int i = 0; i <= n; i++) {
        delete[] m[i];
    }
    delete[] m;
    return 0;
}

int maxNum(int i, int j) {
    if (i >= j) { return i; }
    else { return j; }
}

int matrixPath(int n, int ** m) {
    for (int i = 0; i <= n; i++) {
        m[i][0] = NO_PATH;
    }
    for (int j = 1; j <= n; j++) {
        m[0][j] = NO_PATH;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            m[i][j] = m[i][j] + maxNum(m[i - 1][j], m[i][j - 1]);
        }
    }
    return m[n][n];
}

void matrixPathPrint(int i, int j, int **m) {
    if (i == 1 && j == 1) {
        cout << "경로 : " << "(" << i << ", " << j << ")";
        return;
    } else if (m[i - 1][j] > m[i][j - 1]) {
        matrixPathPrint(i - 1, j, m);
        cout << "->" << "(" << i << ", " << j << ")";
        return;
    } else if (m[i - 1][j] < m[i][j - 1]) {
        matrixPathPrint(i, j - 1, m);
        cout << "->" << "(" << i << ", " << j << ")";
        return;
    }
}