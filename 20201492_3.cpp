#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(void)
{
    int n, m; // 4�ڸ� ������ ���� ���� n, ������ Ƚ�� m

    cout << "n�� m�� �Է��ϼ���: ";
    cin >> n >> m;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
    {
        cout << rand() % 10000 << " ";
    }
    return 0;
}