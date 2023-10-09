#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

class LinkedList // ???????? ???????? ??????? ???�Ḯ??????
{
public:
    Node *head;
    Node *tail;
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void insert(int data)
    {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;

        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void display()
    {
        Node *current = head;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main()
{
    srand((unsigned int)time(NULL));
    int n, m;
    cout << "n���� ???????? ???????????????:";
    cin >> n;
    cout << "?????? ?????? m:";
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        LinkedList *linkedList = new LinkedList;       // n���� ???????? ??????????? ?????? ??????�޸�?? ????????? ?????? ???�Ḯ??????
        LinkedList **digitList = new LinkedList *[10]; // 0~9��??? ???���� ???�Ḯ?????? ?????? ??????????? ??????
        LinkedList **headList = new LinkedList *[10];  // ???????? ???????????? ????? 10 ????????? �迭
        LinkedList **tailList = new LinkedList *[10];  // ???????? ???????????? ????? 10 ????????? �迭

        for (int i = 0; i < 10; i++)
        {
            digitList[i] = new LinkedList;
            headList[i] = nullptr;
        }

        for (int i = 0; i < n; i++)
        {
            linkedList->insert(rand() % 10000); // n���� ?????? ?????? ??????
        }
        cout << "??????????? ??????:";
        linkedList->display();

        for (int count = 0; count < 4; count++)
        {
            Node *current = linkedList->head;

            for (int i = 0; i < 10; i++)
            {
                digitList[i]->head = nullptr;
                headList[i] = nullptr;
                tailList[i] = nullptr;
            }

            for (int k = 0; k < n; k++)
            {
                int sortNum;
                if (count == 0)
                {
                    sortNum = current->data % 10;
                }
                else
                {
                    sortNum = current->data / (int)pow(10, count) % 10;
                }
                digitList[sortNum]->insert(current->data);

                if (headList[sortNum] == nullptr)
                {
                    headList[sortNum] = digitList[sortNum];
                }
                tailList[sortNum] = digitList[sortNum];

                current = current->next;
            }

            linkedList->head = nullptr;
            linkedList->tail = nullptr;

            for (int i = 0; i < 10; i++)
            {
                if (headList[i] != nullptr)
                {
                    if (linkedList->head == nullptr)
                    {
                        linkedList->head = headList[i]->head;
                        linkedList->tail = tailList[i]->tail;
                    }
                    else
                    {
                        linkedList->tail->next = headList[i]->head;
                        linkedList->tail = tailList[i]->tail;
                    }
                }
            }
        }
        cout << "���?????? ???:";
        linkedList->display();
        cout << endl;

        // ??????????? ????????? �޸�?? ??????
        for (int i = 0; i < 10; i++)
        {
            delete digitList[i];
        }
        delete[] digitList;
        delete[] headList;
        delete[] linkedList;
        delete[] tailList;
    }
    return 0;
}