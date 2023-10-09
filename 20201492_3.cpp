#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    int data;
    Node *next = nullptr;
};

class LinkedList { // head�� tail�� ���� ���Ḯ��Ʈ
private:
    Node *head = nullptr;
    Node *tail = nullptr;

public:
    void printNums();      // ���ڵ��� ������ִ� �Լ�
    void addNode(int);
    void deleteAllNode();
    void connectLastNode(Node *);
    Node *getHead() {
        return head;
    }
    Node *getTail() {
        return tail;
    }
};

void radixSort(LinkedList *); // ������ľ˰���
int getLargestNum(LinkedList *);   // �ڸ����� �˾Ƴ��� �˰���

int main(void) {
    srand((unsigned int)time(NULL));
    int n, m; // 4�ڸ� ������ ���� ���� n, ������ Ƚ�� m
    cout << "Enter n and m: ";
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        LinkedList *randList = new LinkedList();
        for (int j = 0; j < n; j++) {
            randList->addNode(rand() % 10000);
        }
        cout << "Before Sorting: ";
        randList->printNums(); // n���� ���� ���� ������ֱ�
        cout << endl;
        radixSort(randList);
        cout << "After Sorting: ";
        randList->printNums();
        randList->deleteAllNode();
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
    LinkedList **headptr = new LinkedList *[10];
    LinkedList **tailptr = new LinkedList *[10];
    for (int i = 0; i < 10; i++) {
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
            headptr[rest]->addNode(start->data); // �� �پ����^^
            start = start->next;
        }
        for (int j = 0; j < 10; j++) {
            tailptr[j]->connectLastNode(headptr[j]->getTail());
        }
        randN->deleteAllNode();
        for (int k = 0; k < 10; k++) { // �ٽ� randN���ٰ� �ʱ�ȭ
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