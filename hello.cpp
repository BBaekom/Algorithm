#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node // 노드
{

private:
    int data;
    Node *link;

public:
    Node(int data)
    {
        this->data = data;
        this->link = nullptr;
    }

    void addNode(int data)
    {
        this->link = new Node(data);
    }

    Node *getNext()
    {
        return link;
    }

    int getData()
    {
        return data;
    }

    void setNext(Node *nextNode)
    {
        this->link = nextNode;
    }
};

Node *stepOfRadixSort(Node *cursor, int divisor)
{
    Node *head[10] = {}; // 3)헤드를 저장하는 포인터 배열
    Node *tail[10] = {}; // 4)테일을 저장하는 포인터 배열
    Node *temp = nullptr;
    Node *newHead;

    Node *firstHead = cursor;

    while (cursor != nullptr) // 2)자릿수에 해당하는 연결리스트 동적 메모리 할당
    {

        int radix = cursor->getData() / divisor % 10;

        if (head[radix] == nullptr)
        {
            head[radix] = new Node(cursor->getData()); // 2)헤드 연결
            tail[radix] = head[radix];                 // 2)테일 연결
        }
        else
        {
            tail[radix]->addNode(cursor->getData());
            tail[radix] = tail[radix]->getNext();
        }
        cursor = cursor->getNext();
    }

    for (int i = 0; i < 10; i++) // 정렬된 연결리스들 연결
    {
        if (head[i] == nullptr)
        {
            continue;
        }
        else
        {
            if (temp != nullptr)
            {
                temp->setNext(head[i]);
                temp = tail[i];
            }
            else
            {
                temp = tail[i];
            }
        }
    }

    for (int i = 0; i < 10; i++) // 새로운 연결 리스트의 head
    {
        if (head[i] != nullptr)
        {
            newHead = head[i];
            break;
        }
    }

    while (firstHead != nullptr) // 동적 메모리 할당 해제
    {
        Node *remover = firstHead;
        firstHead = firstHead->getNext();
        delete remover;
    }

    return newHead;
}

int maxRadixCount(Node *cursor)
{
    int max = 1;
    int data;
    int temp;

    while (cursor != nullptr)
    {
        data = cursor->getData();
        if (data / 10 == 0)
        {
            cursor = cursor->getNext();
        }
        else
        {
            temp = 1;
            while (data / 10 != 0)
            {
                data = data / 10;
                temp++;
            }
            if (temp > max)
            {
                max = temp;
            }
            cursor = cursor->getNext();
        }
    }
    return max;
}

Node *radixSort(Node *head)
{
    int maxRadix;
    int digit = 1;
    Node *newHead = head;

    maxRadix = maxRadixCount(head);

    for (int i = 0; i < maxRadix; i++)
    {
        newHead = stepOfRadixSort(newHead, digit);
        digit = digit * 10;
    }
    return newHead;
}

int main()
{
    srand((unsigned int)time(NULL));
    int n;
    int m;
    int j = 0;

    cout << "n: ";
    cin >> n;

    cout << "m: ";
    cin >> m;

    while (j < m)
    {
        int i = 1;
        Node *head = new Node(rand() % 10000); // 1)동적 메모리 할당을 통한 연결리스트 생성
        Node *cursor = head;
        Node *radixSortCompleted;

        while (i < n) // 1)동적 메모리 할당을 통한 연결리스트 생성
        {
            cursor->addNode(rand() % 10000);
            cursor = cursor->getNext();
            i++;
        }

        cursor = head; // 연결리스트 출력
        cout << "정렬 전: ";
        while (cursor != nullptr)
        {
            cout << cursor->getData() << " ";
            cursor = cursor->getNext();
        }
        cout << endl;

        radixSortCompleted = radixSort(head);

        cursor = radixSortCompleted; // 연결리스트 출력
        cout << "정렬 후: ";
        while (cursor != nullptr)
        {
            cout << cursor->getData() << " ";
            cursor = cursor->getNext();
        }
        cout << endl;

        cursor = radixSortCompleted; // 동적 메모리 할당 해제
        while (cursor != nullptr)
        {
            Node *temp = cursor;
            cursor = cursor->getNext();
            delete temp;
        }
        j++;
    }
}