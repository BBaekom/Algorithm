#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node // ���
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
    Node *head[10] = {}; // 3)��带 �����ϴ� ������ �迭
    Node *tail[10] = {}; // 4)������ �����ϴ� ������ �迭
    Node *temp = nullptr;
    Node *newHead;

    Node *firstHead = cursor;

    while (cursor != nullptr) // 2)�ڸ����� �ش��ϴ� ���Ḯ��Ʈ ���� �޸� �Ҵ�
    {

        int radix = cursor->getData() / divisor % 10;

        if (head[radix] == nullptr)
        {
            head[radix] = new Node(cursor->getData()); // 2)��� ����
            tail[radix] = head[radix];                 // 2)���� ����
        }
        else
        {
            tail[radix]->addNode(cursor->getData());
            tail[radix] = tail[radix]->getNext();
        }
        cursor = cursor->getNext();
    }

    for (int i = 0; i < 10; i++) // ���ĵ� ���Ḯ���� ����
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

    for (int i = 0; i < 10; i++) // ���ο� ���� ����Ʈ�� head
    {
        if (head[i] != nullptr)
        {
            newHead = head[i];
            break;
        }
    }

    while (firstHead != nullptr) // ���� �޸� �Ҵ� ����
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
        Node *head = new Node(rand() % 10000); // 1)���� �޸� �Ҵ��� ���� ���Ḯ��Ʈ ����
        Node *cursor = head;
        Node *radixSortCompleted;

        while (i < n) // 1)���� �޸� �Ҵ��� ���� ���Ḯ��Ʈ ����
        {
            cursor->addNode(rand() % 10000);
            cursor = cursor->getNext();
            i++;
        }

        cursor = head; // ���Ḯ��Ʈ ���
        cout << "���� ��: ";
        while (cursor != nullptr)
        {
            cout << cursor->getData() << " ";
            cursor = cursor->getNext();
        }
        cout << endl;

        radixSortCompleted = radixSort(head);

        cursor = radixSortCompleted; // ���Ḯ��Ʈ ���
        cout << "���� ��: ";
        while (cursor != nullptr)
        {
            cout << cursor->getData() << " ";
            cursor = cursor->getNext();
        }
        cout << endl;

        cursor = radixSortCompleted; // ���� �޸� �Ҵ� ����
        while (cursor != nullptr)
        {
            Node *temp = cursor;
            cursor = cursor->getNext();
            delete temp;
        }
        j++;
    }
}