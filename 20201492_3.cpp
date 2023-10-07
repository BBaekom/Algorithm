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
{ // head와 tail을 가진 연결리스트
private:
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    void printNums();             // 숫자들을 출력해주는 함수
    LinkedList *makeRandNum(int); // n개의 난수 연결리스트를 만드는 함수
    void addNode(int);
    void deleteAllNode();
    Node *getHead()
    {
        return head;
    }
    Node *getTail()
    {
        return tail;
    }
};

void radixSort(LinkedList *, int); // 기수정렬알고리즘
int getLargestNum(LinkedList *);   // 자릿수를 알아내는 알고리즘
void sortElement(LinkedList **, LinkedList **, LinkedList *, int);

int main(void)
{
    int n, m; // 4자리 정수를 받을 개수 n, 실행할 횟수 m

    cout << "n과 m을 입력하세요: ";
    cin >> n >> m;

    LinkedList *randList = new LinkedList();

    randList->makeRandNum(n); // n개의 난수를 연결리스트로 만들어 randN에 리턴
    randList->printNums();    // n개의 난수 먼저 출력해주기
    radixSort(randList, n);
    randList->printNums();
    // 마지막에 동적할당 해제해주기
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
        newNode->data = rand() % 10000; // 1000에서 9999 사이의 난수 생성
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

void radixSort(LinkedList *randN, int n)
{ // n이 안쓰이면 삭제
    LinkedList *headptr[10] = {nullptr};
    LinkedList *tailptr[10] = {nullptr};
    int digit = getLargestNum(randN);
    for (int i = 1; i <= digit; i++)
    {
        sortElement(headptr, tailptr, randN, i);
    }
    return;
}

void sortElement(LinkedList **headptr, LinkedList **tailptr, LinkedList *randN, int k)
{
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
    Node *start = this->getHead();
    while (start != nullptr)
    {
        Node *deleteNode = start;
        start = start->next;
        delete deleteNode;
    }
    head = nullptr;
    tail = nullptr;
}
