#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(void)
{
    int n, m; // 4자리 정수를 받을 개수 n, 실행할 횟수 m

    cout << "n과 m을 입력하세요: ";
    cin >> n >> m;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
    {
        cout << rand() % 10000 << " ";
    }
    return 0;
}