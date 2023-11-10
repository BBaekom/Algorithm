#include <ctime>
#include <iostream>

using namespace std;
int LinearEvenInWorstSelect(int A[], int p, int r, int i);
void Heapify(int A[], int k, int n)
{
    int left = 2 * k;
    int right = 2 * k + 1;
    int smaller;
    if (right <= n)
    {
        if (A[left] < A[right])
        {
            smaller = left;
        }
        else
        {
            smaller = right;
        }
    }
    else if (left <= n)
    {
        smaller = left;
    }
    else
    {
        return;
    }
    if (A[smaller] < A[k])
    {
        swap(A[k], A[smaller]);
        Heapify(A, smaller, n);
    }
}
void BuildHeap(int A[], int n)
{
    for (int i = n / 2; i >= 1; i--)
    {
        Heapify(A, i, n);
    }
}

void HeapSort(int A[], int n)
{
    BuildHeap(A, n);

    for (int i = n; i >= 1; i--)
    {
        swap(A[0], A[i]);
        n--;
        Heapify(A, 0, n);
    }
}

int SortAndGetMedian(int A[], int p, int r)
{
    int len = r - p + 1;
    int *tmp = new int[r - p + 1 + 1];
    for (int i = 0; i < len; i++)
    {
        tmp[i + 1] = A[p + i];
    }
    // 알고리즘 3에서 힙정렬 알고리즘으로 정렬한 후 중앙값을 구한다.
    // 교재의 힙정렬 알고리즘 사용
    HeapSort(tmp, len + 1);
    for (int i = 0; i < len; i++)
    {
        A[p + i] = tmp[i];
    }
    delete[] tmp;
    return (p + r) / 2;
}

int Partition(int A[], int p, int r)
{
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (A[j] <= x)
        {
            swap(A[++i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

int ChoosePivot(int A[], int p, int r)
{
    if (r - p < 5)
    {
        return SortAndGetMedian(A, p, r);
    }

    int cursor = p;
    // 2. 전체 원소를 5개씩의 원소를 가진 n/5개의 그룹으로 나눈다.
    // min 사용으로 5개 미만인 그룹인 경우 처리
    for (int i = p; i <= r; i += 5)
    {
        // 3. 각 그룹에서 중앙값(원소가 5개이면 3번째 원소)을 찾는다.
        int median_pos = SortAndGetMedian(A, i, min(r, i + 4));
        swap(A[median_pos], A[cursor]);
        cursor++;
    }
    // 4. m1, m2 ... 들의 중앙값 M을 재귀적으로 구한다.
    return LinearEvenInWorstSelect(
        A, p, cursor - 1,
        (cursor + p - 1) / 2); // 원소의 총수가 짝수면 두 중앙값 중 임의로
                               // 선택한다. (작은 index 선택)
}
int AvgLinearSelect(int A[], int p, int r, int i)
{
    int q = Partition(A, p, r);
    int k = q - p + 1;
    if (i < k)
    {
        return AvgLinearSelect(A, p, q - 1, i);
    }
    else if (i == k)
    {
        return q;
    }
    else
    {
        return AvgLinearSelect(A, q + 1, r, i - k);
    }
}

int LinearEvenInWorstSelect(int A[], int p, int r, int i)
{
    if (p == r)
    {
        return p;
    }
    // 1. 원소의 총수가 5개 이하면 i번째 원소를 찾고 알고리즘을 끝낸다.
    if (r - p + 1 <= 5)
    {
        cout << "TT" << p << "TT" << r << "TT" << A[p] << "TT" << A[r] << "TT"
             << endl;
        return AvgLinearSelect(A, p, r, i); // 5-1 알고리즘 사용
    }

    int M_pos = ChoosePivot(A, p, r);
    // 5. M을 기준원소로 삼아 전체원소를 분할한다. (교재의 partition 함수 사용)
    swap(A[M_pos], A[r]);
    int partition_result = Partition(A, p, r);

    // 6. 분할된 두 그룹 중 적합한 쪽을 선택해 재귀적으로 반복
    if (partition_result == i)
    {
        return partition_result;
    }
    else if (partition_result > i)
    {
        return LinearEvenInWorstSelect(A, p, partition_result - 1, i);
    }
    else if (partition_result < i)
    {
        return LinearEvenInWorstSelect(A, partition_result + 1, r, i);
    }
    return -1;
}

int main()
{
    srand(time(NULL));

    clock_t start, finish;
    double duration;

    int ARR_LEN = 100000;
    int ITER_COUNT = 1000;

    int A[100000];

    start = clock();
    for (; ITER_COUNT > 0; ITER_COUNT--)
    {
        for (int i = 0; i < ARR_LEN; i++)
        {
            A[i] = rand() % ARR_LEN;
        }

        cout << A[LinearEvenInWorstSelect(A, 0, ARR_LEN, 49999)] << ", ";
    }

    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << duration << "초" << endl;

    return 0;
}
