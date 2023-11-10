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
    // �˰��� 3���� ������ �˰������� ������ �� �߾Ӱ��� ���Ѵ�.
    // ������ ������ �˰��� ���
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
    // 2. ��ü ���Ҹ� 5������ ���Ҹ� ���� n/5���� �׷����� ������.
    // min ������� 5�� �̸��� �׷��� ��� ó��
    for (int i = p; i <= r; i += 5)
    {
        // 3. �� �׷쿡�� �߾Ӱ�(���Ұ� 5���̸� 3��° ����)�� ã�´�.
        int median_pos = SortAndGetMedian(A, i, min(r, i + 4));
        swap(A[median_pos], A[cursor]);
        cursor++;
    }
    // 4. m1, m2 ... ���� �߾Ӱ� M�� ��������� ���Ѵ�.
    return LinearEvenInWorstSelect(
        A, p, cursor - 1,
        (cursor + p - 1) / 2); // ������ �Ѽ��� ¦���� �� �߾Ӱ� �� ���Ƿ�
                               // �����Ѵ�. (���� index ����)
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
    // 1. ������ �Ѽ��� 5�� ���ϸ� i��° ���Ҹ� ã�� �˰����� ������.
    if (r - p + 1 <= 5)
    {
        cout << "TT" << p << "TT" << r << "TT" << A[p] << "TT" << A[r] << "TT"
             << endl;
        return AvgLinearSelect(A, p, r, i); // 5-1 �˰��� ���
    }

    int M_pos = ChoosePivot(A, p, r);
    // 5. M�� ���ؿ��ҷ� ��� ��ü���Ҹ� �����Ѵ�. (������ partition �Լ� ���)
    swap(A[M_pos], A[r]);
    int partition_result = Partition(A, p, r);

    // 6. ���ҵ� �� �׷� �� ������ ���� ������ ��������� �ݺ�
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
    cout << duration << "��" << endl;

    return 0;
}
