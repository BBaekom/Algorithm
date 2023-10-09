#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

struct Node
{
    int data;
    Node *next = nullptr;
};

class LinkedList
{ // head�� tail�� ���� ���Ḯ��Ʈ
private:
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    void printNums();      // ���ڵ��� ������ִ� �Լ�
    void makeRandNum(int); // n���� ���� ���Ḯ��Ʈ�� ����� �Լ�
    void addNode(int);
    void deleteAllNode();
    // void connectptrArray(LinkedList **, int);
    Node *getHead()
    {
        return head;
    }
    Node *getTail()
    {
        return tail;
    }
};

void radixSort(LinkedList *, int); // ������ľ˰���
int getLargestNum(LinkedList *);   // �ڸ����� �˾Ƴ��� �˰���
// void sortElement(LinkedList **, LinkedList **, LinkedList *, int);
// void initialization(LinkedList **, LinkedList **, LinkedList *, int);

int main(void)
{
    int n, m; // 4�ڸ� ������ ���� ���� n, ������ Ƚ�� m

    cout << "n�� m�� �Է��ϼ���: ";
    cin >> n >> m;

    LinkedList *randList = new LinkedList();

    randList->makeRandNum(n); // n���� ������ ���Ḯ��Ʈ�� ����� randN�� ����
    randList->printNums();    // n���� ���� ���� ������ֱ�
    radixSort(randList, n);
    randList->printNums();
    return 0;
}

void LinkedList::printNums()
{
    Node *start = this->head;
    while (start != nullptr)
    {
        cout << start->data << ' ';
        start = start->next;
    }
    cout << endl;
    return;
}

void LinkedList::makeRandNum(int n)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++)
    {
        Node *newNode = new Node();
        newNode->data = rand() % 10000; // 1000���� 9999 ������ ���� ����
        if (this->head == nullptr)
        {
            this->head = newNode;
            this->tail = newNode;
        }
        else
        {
            this->tail->next = newNode;
            this->tail = newNode;
        }
    }
    return;
}

void radixSort(LinkedList *randN, int n)
{ // n�� �Ⱦ��̸� ����
    int digit = getLargestNum(randN);
    LinkedList **headptr = new LinkedList *[10];
    LinkedList **tailptr = new LinkedList *[10];
    for (int i = 0; i < 10; i++)
    {
        headptr[i] = new LinkedList;
        tailptr[i] = new LinkedList;
    }
    for (int i = 0; i < digit; i++)
    {
        Node *start = randN->getHead();
        while (start != nullptr)
        {
            int rest = (start->data / (int)pow(10, i)) % 10;
            headptr[rest]->addNode(start->data); // �� �پ����^^
            start = start->next;
        }
    }
}

int getLargestNum(LinkedList *numbers)
{
    int digit = 0;
    int count = 0;
    Node *start = numbers->getHead();
    while (start != nullptr)
    {
        int n = start->data;
        while (n != 0)
        {
            n /= 10;
            count++;
        }
        if (digit < count)
        {
            digit = count;
        }
        start = start->next;
        count = 0;
    }
    return digit;
}

void LinkedList::addNode(int data)
{
    Node *newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    if (this->head == nullptr)
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        this->tail->next = newNode;
        this->tail = newNode;
    }
}

void LinkedList::deleteAllNode()
{
    Node *start = this->head;
    while (start != nullptr)
    {
        Node *deleteNode = start;
        start = start->next;
        delete deleteNode;
    }
    this->head = nullptr;
    this->tail = nullptr;
}
