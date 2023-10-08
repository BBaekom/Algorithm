#include <iostream>
#include <cstdlib>
#include <ctime>
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
    void printNums();             // ���ڵ��� ������ִ� �Լ�
    LinkedList *makeRandNum(int); // n���� ���� ���Ḯ��Ʈ�� ����� �Լ�
    void addNode(int);
    void deleteAllNode();
    void connectptrArray(LinkedList **, int);
    Node *getHead()
    {
        return head;
    }
    Node *getTail()
    {
        return tail;
    }
};

void radixSort(LinkedList *); // ������ľ˰���
int getLargestNum(LinkedList *);   // �ڸ����� �˾Ƴ��� �˰���
void sortElement(LinkedList **, LinkedList **, LinkedList *, int);
void initialization(LinkedList **, LinkedList **, LinkedList *);

int main(void)
{
    int n, m; // 4�ڸ� ������ ���� ���� n, ������ Ƚ�� m

    cout << "n�� m�� �Է��ϼ���: ";
    cin >> n >> m;

    LinkedList *randList = new LinkedList();

    randList->makeRandNum(n); // n���� ������ ���Ḯ��Ʈ�� ����� randN�� ����
    randList->printNums();    // n���� ���� ���� ������ֱ�
    radixSort(randList);
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

LinkedList *LinkedList::makeRandNum(int n)
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
    return this;
}

void radixSort(LinkedList *randN)
{ // n�� �Ⱦ��̸� ����
    LinkedList *headptrArray[10] = {nullptr};
    LinkedList *tailptrArray[10] = {nullptr};
    int digit = getLargestNum(randN);
    for (int i = 1; i <= digit; i++)
    {
        sortElement(headptrArray, tailptrArray, randN, i);
        initialization(headptrArray, tailptrArray, randN);
    }
    return;
}

void sortElement(LinkedList **headptrArray, LinkedList **tailptrArray, LinkedList *randN, int k) {
    Node *start = randN->getHead();
    while (start != nullptr) {
        int divisor = 10;
        int dividend = 0, rest = 0;
        int data = start->data;
        for (int i = 0;  i < k; i++) { 
            rest = data % divisor; 
            if (i == k-1) { 
                headptrArray[rest]->addNode(start->data);
                tailptrArray[rest]->connectptrArray(headptrArray, rest);
            } else {
                data = data / divisor; 
            }
        }
        start = start->next;
    }
}

void LinkedList::connectptrArray(LinkedList ** headptrArray, int rest) {
    this->head = headptrArray[rest]->tail;
}

void initialization(LinkedList ** headptrArray, LinkedList ** tailptrArray, LinkedList * randN) {
    Node * start = randN->getHead();
    for (int i = 0; i < 9; i++) {
        while (start != nullptr) {
            Node * ptrStart = headptrArray[i]->getHead();
            while (ptrStart != nullptr) {
                start->data = ptrStart->data;
                start = start->next;
                ptrStart = ptrStart->next;
            }
        }
    }
    for (int i = 0; i < 9; i++) {
        headptrArray[i]->deleteAllNode();
        tailptrArray[i]->connectptrArray(headptrArray, i);
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
