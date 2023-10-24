#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int select(int *, int, int, int);
int partition(int *, int, int);
// void linearSelet(int *, int, int, int);
// void heapSort();

int main(void) {
    srand((unsigned int)time(NULL));
    int randArr[100000];
    int repeatCount;
    cout << "Repeat Count : ";
    cin >> repeatCount;
    for (int i = 0; i < repeatCount; i++) {
        for (int i = 0; i < 100000; i++) {
            randArr[i] = rand();
        }
        int q = select(randArr, 0, 99999, 50000);
        cout << q << " ";
    }
}

int select(int * randArr, int first, int last, int i_Small) {
    int partitionNum;
    int k;
    if (first == last) { return randArr[first]; }
    partitionNum = partition(randArr, first, last);
    k = partitionNum - first + 1;
    if (i_Small < k){
        return select(randArr, first, partitionNum - 1, i_Small);
    } else if (i_Small == k){
        return randArr[partitionNum];
    } else {
        return select(randArr, partitionNum + 1, last, i_Small - k);
    }
}

int partition(int * randArr, int first, int last) {
    int key = randArr[last];
    int i = first - 1;
    int tmp;
    for (int j = first; j <= last - 1; j++) {
        if (randArr[j] <= key) {
            i++;
            int tmp = randArr[i];
            randArr[i] = randArr[j];
            randArr[j] = tmp;
        }
    }
    tmp = randArr[i + 1];
    randArr[i + 1] = randArr[last];
    randArr[last] = tmp;
    return i + 1;
}