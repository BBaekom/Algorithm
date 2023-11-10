#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int select(int[], int, int, int);
int partition(int[], int, int);
int linearSelect(int[], int, int, int);
void heapSort(int[], int);
void buildHeap(int[], int);
void heapify(int[], int, int);

#define NUM 100

void makeRandNum(int randArr[], int num)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < num; i++)
    {
        randArr[i] = rand() % 100;
    }
}

int main(void)
{
    clock_t start, finish;
    double duration;

    // // 5-1 코드
    // int randArr[NUM];
    // int repeatCount;
    // cout << "Repeat Count : ";
    // cin >> repeatCount;
    // makeRandNum(randArr, NUM);
    // start = clock();
    // for (int i = 0; i < repeatCount; i++) {
    //     for (int k = 1; k <= (NUM / 2); k++) {
    //         int q = select(randArr, 0, NUM - 1, k);
    //         // cout << q << " ";
    //     }
    // }

    // 5-2 코드
    int randArr2[NUM];
    int repeatCount;
    cout << "Repeat Count : ";
    cin >> repeatCount;
    makeRandNum(randArr2, NUM);

    cout << endl;
    start = clock();
    for (int i = 0; i < repeatCount; i++)
    {
        for (int k = 1; k <= (NUM / 2); k++) {
            int q = linearSelect(randArr2, 0, NUM - 1, NUM / 2);
        }
    }

    finish = clock();

    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << endl;
    cout << duration << "초" << endl;

    return 0;
}

// select 함수
int select(int randArr[], int first, int last, int i_Small)
{
    int partitionNum;
    int k;
    if (first == last)
    {
        return randArr[first];
    }
    partitionNum = partition(randArr, first, last);
    k = partitionNum - first + 1;
    if (i_Small < k)
    {
        return select(randArr, first, partitionNum - 1, i_Small);
    }
    else if (i_Small == k)
    {
        return randArr[partitionNum];
    }
    else
    {
        return select(randArr, partitionNum + 1, last, i_Small - k);
    }
}

// partition 함수
int partition(int randArr[], int first, int last)
{
    int key = randArr[last];
    int i = first - 1;
    for (int j = first; j <= last - 1; j++)
    {
        if (randArr[j] <= key)
        {
            i++;
            swap(randArr[i], randArr[j]);
        }
    }
    swap(randArr[i + 1], randArr[last]);
    return i + 1;
}

// M을 찾았을 때 처음 partition
int partition(int randArr[], int first, int last, int middleOfmiddle)
{
    int middleOfmiddleNumIndex;
    for (int i = first; i <= last; i++)
    {
        if (randArr[i] == middleOfmiddle)
        {
            middleOfmiddleNumIndex = i;
            break;
        }
    }
    swap(randArr[middleOfmiddleNumIndex], randArr[last]);
    int key = randArr[last];
    int i = first - 1;
    for (int j = first; j <= last - 1; j++)
    {
        if (randArr[j] <= key)
        {
            i++;
            swap(randArr[i], randArr[j]);
        }
    }
    swap(randArr[i + 1], randArr[last]);
    return i + 1;
}

// buildHeap 함수
void buildHeap(int randArr[], int elementNum)
{
    for (int i = elementNum / 2 - 1; i >= 0; i--)
    {
        heapify(randArr, i, elementNum - 1);
    }
}

// heapify 함수 -> 책대로 하면 내림차순 돼서 부등호 방향 바꿈
void heapify(int randArr[], int parent, int indexNum)
{
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;
    int smaller;
    if (right <= indexNum)
    {
        if (randArr[left] < randArr[right])
        {
            smaller = left;
        }
        else
        {
            smaller = right;
        }
    }
    else if (left <= indexNum)
    {
        smaller = left;
    }
    else
    {
        return;
    }

    if (randArr[smaller] < randArr[parent])
    {
        swap(randArr[parent], randArr[smaller]);
        heapify(randArr, smaller, indexNum);
    }
}

// heapSort 함수
void heapSort(int randArr[], int elementNum)
{
    buildHeap(randArr, elementNum);
    for (int i = elementNum - 1; i >= 0; i--)
    {
        swap(randArr[i], randArr[0]);
        heapify(randArr, 0, i - 1);
    }
}

int total_num = NUM;
// linearSelect 함수
int linearSelect(int randArr[], int firstIndex, int lastIndex, int i_Small)
{
    int totalNum = lastIndex - firstIndex + 1;
        // 1. 원소 개수가 5 이하일 때 select함수 사용
    if (totalNum <= 5)
    {
        // cout << "원소가 5개 이하" << '\n';
        return select(randArr, firstIndex, lastIndex, i_Small);
    }
    // 2. 그룹 수 구하기
    int groupNum = (totalNum % 5 == 0) ? totalNum / 5 : totalNum / 5 + 1;

    // 중앙값들을 모은 배열
    int *middleNum = new int[groupNum];

    // 3. 중앙값 처리 부분 - 배열에서 5개씩 힙정렬 해주고 middleNum에 정렬한 5개 중에서 중앙값 넣어줌. 마지막에 5개 이하의 원소가 남으면 그 중에서 중앙값 찾음
    int j = 0;
    for (int i = 0; i < totalNum; i += 5)
    {
        int groupLastIndex = min(i + 4, lastIndex);
        int groupSize = groupLastIndex - i + 1;
        heapSort(&randArr[i], groupSize);
        middleNum[j++] = randArr[i + groupSize / 2];
    }

    // 4. 중앙값들의 중앙값 찾기
    int middleOfmiddleNum = linearSelect(middleNum, 0, groupNum - 1, (groupNum / 2) + 1);
    delete[] middleNum;

    // 5. M을 기준삼아 전체 원소를 분할한다.
    int partitionNum = partition(randArr, firstIndex, lastIndex, middleOfmiddleNum); // 새로 구한 M 인덱스 = partitionNum
    int k = partitionNum - firstIndex + 1; // M은 배열에서 k번째의 수이다.
   
    if (i_Small == k)
    {
        return randArr[partitionNum];
    } // k와 찾고자하는 i_Small 번째 수가 같으면 바로 그 수를 리턴
    else if (i_Small < k)
    {
        total_num = partitionNum - firstIndex;
        return linearSelect(randArr, firstIndex, partitionNum - 1, i_Small);
    }
    else
    {
        total_num = lastIndex - partitionNum;
        return linearSelect(randArr, partitionNum + 1, lastIndex, i_Small - k);
    }
}