#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    int data;
    Node *next = nullptr;
};

class LinkedList { // head와 tail을 가진 연결리스트
private:
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    void printNums();               // 연결리스트 숫자 출력 함수
    void addNode(int);              // 노드 추가 함수
    void deleteAllNode();           // 모든 노드를 지우는 함수
    void connectLastNode(Node *);   // tail 포인터배열 연결함수
    Node *getHead() {
        return head;
    }
    Node *getTail() {
        return tail;
    }
};

void radixSort(LinkedList *);      // 기수정렬알고리즘
int getLargestNum(LinkedList *);   // 최대자릿수를 알아내는 알고리즘

int main(void) {
    srand((unsigned int)time(NULL));
    int n, m; // 4자리 정수를 받을 개수 n, 반복 실행할 횟수 m
    cout << "Enter n and m: ";
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        LinkedList *randList = new LinkedList();
        for (int j = 0; j < n; j++) {
            randList->addNode(rand() % 10000); // n개의 난수를 노드로 가지는 randList 동적할당으로 생성
        }
        cout << "Before Sorting: ";
        randList->printNums();          // n개의 난수 먼저 출력해주기
        cout << endl;
        radixSort(randList);            // 기수정렬 실행
        cout << "After Sorting: ";
        randList->printNums();          // 기수정렬 후의 결과 출력
        randList->deleteAllNode();      // 동적할당 해제
        cout << "-----------------------------------------------------------------" << endl;
    }
    return 0;
}

void LinkedList::printNums() {
    Node *start = this->head;
    while (start != nullptr) {
        cout << start->data << ' ';
        start = start->next;
    }
    cout << endl;
    return;
}

void radixSort(LinkedList *randN)
{
    int digit = getLargestNum(randN);
    LinkedList **headptr = new LinkedList *[10]; // 각 연결리스트의 헤드의 역할을 하는 크기가 10인 포인터 배열
    LinkedList **tailptr = new LinkedList *[10]; // 각 연결리스트의 테일의 역할을 하는 크기가 10인 포인터 배열
    for (int i = 0; i < 10; i++) {  // 0~9까지의 자릿수에 해당하는 10개의 연결리스트를 동적 메모리 할당으로 생성
        headptr[i] = new LinkedList;
        tailptr[i] = new LinkedList;
    }
    for (int i = 0; i < digit; i++) {
        Node *start = randN->getHead();
        while (start != nullptr) {
            int divisor = 1;
            for (int l = 0; l < i; l++) {
                divisor *= 10;
            }
            int rest = (start->data / divisor) % 10;
            headptr[rest]->addNode(start->data);
            start = start->next;
        }
        for (int j = 0; j < 10; j++) {
            tailptr[j]->connectLastNode(headptr[j]->getTail());
        }
        randN->deleteAllNode();
        for (int k = 0; k < 10; k++) { // 다시 randN에다가 초기화
            Node *ptrStart = headptr[k]->getHead();
            while (ptrStart != nullptr) {
                randN->addNode(ptrStart->data);
                ptrStart = ptrStart->next;
            }
            headptr[k]->deleteAllNode();
            tailptr[k]->deleteAllNode();
        }
    }
}

int getLargestNum(LinkedList *numbers) {
    int digit = 0;
    int count = 0;
    Node *start = numbers->getHead();
    while (start != nullptr) {
        int n = start->data;
        while (n != 0) {
            n /= 10;
            count++;
        }
        if (digit < count) {
            digit = count;
        }
        start = start->next;
        count = 0;
    }
    return digit;
}

void LinkedList::addNode(int data) {
    Node *newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    if (this->head == nullptr) {
        this->head = newNode;
        this->tail = newNode;
    }
    else {
        this->tail->next = newNode;
        this->tail = newNode;
    }
}

void LinkedList::deleteAllNode() {
    Node *start = this->head;
    while (start != nullptr) {
        Node *deleteNode = start;
        start = start->next;
        delete deleteNode;
    }
    this->head = nullptr;
    this->tail = nullptr;
}

void LinkedList::connectLastNode(Node *lastNode) {
    this->head = lastNode;
}