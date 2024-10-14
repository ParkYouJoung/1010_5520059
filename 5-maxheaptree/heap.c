#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// 노드 생성
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 최대 힙 삽입
void insertMaxHeapTree(TreeNode** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
        printf("%d 삽입됨.\n", value); // 첫 노드 삽입
        return;
    }

    // 큐 사용해서 첫 번째 빈 자리 찾기
    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = *root;

    TreeNode* parent = NULL;
    while (front < rear) {
        TreeNode* current = queue[front++];

        if (current->left == NULL) {
            parent = current;
            current->left = createNode(value);
            break;
        }
        else {
            queue[rear++] = current->left;
        }

        if (current->right == NULL) {
            parent = current;
            current->right = createNode(value);
            break;
        }
        else {
            queue[rear++] = current->right;
        }
    }

    // 삽입 후 최대 힙 구조를 유지하기 위해 노드 이동
    int moveCount = 0;
    TreeNode* child = (parent->left && parent->left->data == value) ? parent->left : parent->right;
    while (parent && child->data > parent->data) {
        printf("%d <-> %d 교환\n", child->data, parent->data);
        int temp = child->data;
        child->data = parent->data;
        parent->data = temp;

        // 이동한 횟수 증가
        moveCount++;
        child = parent;
        parent = NULL; // 부모 탐색
        for (int i = 0; i < front; i++) {
            if (queue[i]->left == child || queue[i]->right == child) {
                parent = queue[i];
                break;
            }
        }
    }

    printf("노드가 이동된 횟수: %d\n", moveCount);
}

// 최대 힙 삭제 함수
void deleteMaxHeapTree(TreeNode** root) {
    if (*root == NULL) {
        printf("힙이 비어 있습니다.\n");
        return;
    }

    if ((*root)->left == NULL && (*root)->right == NULL) {
        free(*root);
        *root = NULL;
        printf("트리가 비어 있습니다.\n");
        return;
    }

    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = *root;

    TreeNode* lastNode = NULL, * parentNode = NULL;
    while (front < rear) {
        lastNode = queue[front++];

        if (lastNode->left) {
            parentNode = lastNode;
            queue[rear++] = lastNode->left;
        }

        if (lastNode->right) {
            parentNode = lastNode;
            queue[rear++] = lastNode->right;
        }
    }

    printf("최대값 %d 삭제\n", (*root)->data);

    (*root)->data = lastNode->data;

    if (parentNode->right == lastNode) {
        free(parentNode->right);
        parentNode->right = NULL;
    }
    else if (parentNode->left == lastNode) {
        free(parentNode->left);
        parentNode->left = NULL;
    }

    // 루트에서부터 힙 재구성
    int moveCount = 0;
    TreeNode* current = *root;
    while (current->left || current->right) {
        TreeNode* largerChild = NULL;
        if (current->right == NULL || (current->left && current->left->data > current->right->data)) {
            largerChild = current->left;
        }
        else {
            largerChild = current->right;
        }

        if (largerChild->data > current->data) {
            printf("%d <-> %d 교환\n", current->data, largerChild->data);
            int temp = current->data;
            current->data = largerChild->data;
            largerChild->data = temp;

            moveCount++;
            current = largerChild;
        }
        else {
            break;
        }
    }

    printf("노드가 이동된 횟수: %d\n", moveCount);
}

// 최대 힙 트리 생성
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        insertMaxHeapTree(&root, inputData[i]);
    }
    return root;
}

// 레벨 순서대로 출력
void printLevelOrder(TreeNode* root) {
    if (root == NULL) {
        printf("트리가 비어 있습니다.\n");
        return;
    }

    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int level = 1;
    printf("트리 레벨별 출력\n");
    while (front < rear) {
        int nodeCount = rear - front;
        printf("[%d] ", level++);
        while (nodeCount > 0) {
            TreeNode* current = queue[front++];
            printf("%d ", current->data);

            if (current->left != NULL) {
                queue[rear++] = current->left;
            }
            if (current->right != NULL) {
                queue[rear++] = current->right;
            }
            nodeCount--;
        }
        printf("\n");
    }
}