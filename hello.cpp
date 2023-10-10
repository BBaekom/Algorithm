#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>

using namespace std;
int n, m;

// ���Ḯ��Ʈ�� ����� ���� ����ü
struct node
{
    int num;
    node *nextNode;
};

// ���� �޾� ���ο� ��带 �����ؼ� ���� ��忡 �������ִ� �Լ�
node *makeAndLinkNode(node *currentNode, int num)
{
    //new ������ ���
    node *newNode = new node;
    newNode->num = num;
    newNode->nextNode = nullptr;

    if (currentNode != nullptr)
    {
        currentNode->nextNode = newNode;
    }
    return newNode;
}

int main(void)
{
    srand(time(NULL));

    cout << "n:";
    cin >> n;
    cout << "m:";
    cin >> m;

    for (int i = 0; i < m; i++)
    {
        node *randHead = makeAndLinkNode(nullptr, -1);
        node *currentNode = randHead;

        // �� ���Ḯ��Ʈ�� ��带 �����ϴ� ũ�Ⱑ 10�� ������ �迭�� ����
        node *numHead[10] = {nullptr};

        // �� ���Ḯ��Ʈ�� ������ �����ϴ� ũ�Ⱑ 10�� ������ �迭�� ����
        node *numTail[10] = {nullptr};

        // ���� ���� ����, ���� �޸� �Ҵ��� ���� ���Ḯ��Ʈ ����
        for (int j = 0; j < n; j++)
        {
            int a = rand() % 10000;
            currentNode = makeAndLinkNode(currentNode, a);
        }
        cout<<"���� ��->";
        currentNode = randHead->nextNode;
        while (currentNode != nullptr)
        {
            cout << currentNode->num << " ";
            currentNode = currentNode->nextNode;
        }
        cout << "\n";

        // ������� ����

        for (int j = 1; j < 5; j++)
        {

            // �� �ڸ����� �ش��ϴ� 10���� ���Ḯ��Ʈ�� ���� �޸� �Ҵ����� ����
            for (int j = 0; j < 10; j++)
            {
                numHead[j] = new node;
                numHead[j]->num = -1;
                numHead[j]->nextNode = nullptr;
                numTail[j] = numHead[j];
            }

            //���° ��ũ�帮��Ʈ�� ������ ���ϱ�
            currentNode = randHead->nextNode;
            int nanoogi = pow(10, j);
            int makeNanoogi = pow(10, j - 1);
            while (currentNode != nullptr)
            {
                if (currentNode->num == -1)
                {
                    currentNode = currentNode->nextNode;
                    continue;
                }
                int nodeWhere = (currentNode->num) % nanoogi / makeNanoogi;
                makeAndLinkNode(numTail[nodeWhere], currentNode->num);
                numTail[nodeWhere] = numTail[nodeWhere]->nextNode;
                numTail[nodeWhere]->nextNode = nullptr;
                currentNode = currentNode->nextNode;
            }



            // tail�� head ����
            node *saveNode = makeAndLinkNode(nullptr, -1);
            node *saveCurrent = saveNode;

            for (int i = 0; i < 10; i++)
            {
                if (numTail[i]->num == -1)
                {
                    continue;
                }
                saveCurrent->nextNode = numHead[i];
                saveCurrent = numTail[i];
            }
            saveCurrent->nextNode = nullptr;

            saveCurrent = saveNode;
            currentNode = randHead->nextNode;
            while (saveCurrent != nullptr)
            {
                if (saveCurrent->num >= 0)
                {
                    currentNode->num = saveCurrent->num;
                    currentNode = currentNode->nextNode;
                    saveCurrent = saveCurrent->nextNode;
                }
                else
                {
                    saveCurrent = saveCurrent->nextNode;
                }
            }

            // savenode �޸� ����
            while (saveCurrent != nullptr)
            {
                node *temp = saveCurrent;
                saveCurrent = saveCurrent->nextNode;
                delete temp;
            }


        }
        // ���� �� ���
        cout << "���� ��->";
        currentNode = randHead->nextNode;
        while (currentNode != nullptr)
        {
            cout << currentNode->num << " ";
            currentNode = currentNode->nextNode;
        }
        cout << "\n\n";
        // �޸� ����
        currentNode = randHead;
        while (currentNode != nullptr)
        {
            node *temp = currentNode;
            currentNode = currentNode->nextNode;
            delete temp;
        }
    }

    return 0;
}