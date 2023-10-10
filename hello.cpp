#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>

using namespace std;
int n, m;

// 연결리스트를 만들기 위한 구조체
struct node
{
    int num;
    node *nextNode;
};

// 값을 받아 새로운 노드를 생성해서 현재 노드에 연결해주는 함수
node *makeAndLinkNode(node *currentNode, int num)
{
    //new 연산자 사용
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

        // 각 연결리스트의 헤드를 저장하는 크기가 10인 포인터 배열을 생성
        node *numHead[10] = {nullptr};

        // 각 연결리스트의 테일을 저장하는 크기가 10인 포인터 배열을 생성
        node *numTail[10] = {nullptr};

        // 랜덤 숫자 생성, 동적 메모리 할당을 통한 연결리스트 생성
        for (int j = 0; j < n; j++)
        {
            int a = rand() % 10000;
            currentNode = makeAndLinkNode(currentNode, a);
        }
        cout<<"정렬 전->";
        currentNode = randHead->nextNode;
        while (currentNode != nullptr)
        {
            cout << currentNode->num << " ";
            currentNode = currentNode->nextNode;
        }
        cout << "\n";

        // 기수정렬 시행

        for (int j = 1; j < 5; j++)
        {

            // 각 자릿수에 해당하는 10개의 연결리스트를 동적 메모리 할당으로 생성
            for (int j = 0; j < 10; j++)
            {
                numHead[j] = new node;
                numHead[j]->num = -1;
                numHead[j]->nextNode = nullptr;
                numTail[j] = numHead[j];
            }

            //몇번째 링크드리스트에 들어갈건지 구하기
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



            // tail과 head 연결
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

            // savenode 메모리 해제
            while (saveCurrent != nullptr)
            {
                node *temp = saveCurrent;
                saveCurrent = saveCurrent->nextNode;
                delete temp;
            }


        }
        // 정렬 후 출력
        cout << "정렬 후->";
        currentNode = randHead->nextNode;
        while (currentNode != nullptr)
        {
            cout << currentNode->num << " ";
            currentNode = currentNode->nextNode;
        }
        cout << "\n\n";
        // 메모리 해제
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