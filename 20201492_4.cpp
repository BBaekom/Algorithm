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

    // // 5-1 �ڵ�
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

    // 5-2 �ڵ�
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
    cout << duration << "��" << endl;

    return 0;
}

// select �Լ�
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

// partition �Լ�
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

// M�� ã���� �� ó�� partition
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

// buildHeap �Լ�
void buildHeap(int randArr[], int elementNum)
{
    for (int i = elementNum / 2 - 1; i >= 0; i--)
    {
        heapify(randArr, i, elementNum - 1);
    }
}

// heapify �Լ� -> å��� �ϸ� �������� �ż� �ε�ȣ ���� �ٲ�
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

// heapSort �Լ�
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
// linearSelect �Լ�
int linearSelect(int randArr[], int firstIndex, int lastIndex, int i_Small)
{
    int totalNum = lastIndex - firstIndex + 1;
        // 1. ���� ������ 5 ������ �� select�Լ� ���
    if (totalNum <= 5)
    {
        // cout << "���Ұ� 5�� ����" << '\n';
        return select(randArr, firstIndex, lastIndex, i_Small);
    }
    // 2. �׷� �� ���ϱ�
    int groupNum = (totalNum % 5 == 0) ? totalNum / 5 : totalNum / 5 + 1;

    // �߾Ӱ����� ���� �迭
    int *middleNum = new int[groupNum];

    // 3. �߾Ӱ� ó�� �κ� - �迭���� 5���� ������ ���ְ� middleNum�� ������ 5�� �߿��� �߾Ӱ� �־���. �������� 5�� ������ ���Ұ� ������ �� �߿��� �߾Ӱ� ã��
    int j = 0;
    for (int i = 0; i < totalNum; i += 5)
    {
        int groupLastIndex = min(i + 4, lastIndex);
        int groupSize = groupLastIndex - i + 1;
        heapSort(&randArr[i], groupSize);
        middleNum[j++] = randArr[i + groupSize / 2];
    }

    // 4. �߾Ӱ����� �߾Ӱ� ã��
    int middleOfmiddleNum = linearSelect(middleNum, 0, groupNum - 1, (groupNum / 2) + 1);
    delete[] middleNum;

    // 5. M�� ���ػ�� ��ü ���Ҹ� �����Ѵ�.
    int partitionNum = partition(randArr, firstIndex, lastIndex, middleOfmiddleNum); // ���� ���� M �ε��� = partitionNum
    int k = partitionNum - firstIndex + 1; // M�� �迭���� k��°�� ���̴�.
   
    if (i_Small == k)
    {
        return randArr[partitionNum];
    } // k�� ã�����ϴ� i_Small ��° ���� ������ �ٷ� �� ���� ����
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