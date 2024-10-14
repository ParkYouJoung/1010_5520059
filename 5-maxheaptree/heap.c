#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// ��� ����
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// �ִ� �� ����
void insertMaxHeapTree(TreeNode** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
        printf("%d ���Ե�.\n", value); // ù ��� ����
        return;
    }

    // ť ����ؼ� ù ��° �� �ڸ� ã��
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

    // ���� �� �ִ� �� ������ �����ϱ� ���� ��� �̵�
    int moveCount = 0;
    TreeNode* child = (parent->left && parent->left->data == value) ? parent->left : parent->right;
    while (parent && child->data > parent->data) {
        printf("%d <-> %d ��ȯ\n", child->data, parent->data);
        int temp = child->data;
        child->data = parent->data;
        parent->data = temp;

        // �̵��� Ƚ�� ����
        moveCount++;
        child = parent;
        parent = NULL; // �θ� Ž��
        for (int i = 0; i < front; i++) {
            if (queue[i]->left == child || queue[i]->right == child) {
                parent = queue[i];
                break;
            }
        }
    }

    printf("��尡 �̵��� Ƚ��: %d\n", moveCount);
}

// �ִ� �� ���� �Լ�
void deleteMaxHeapTree(TreeNode** root) {
    if (*root == NULL) {
        printf("���� ��� �ֽ��ϴ�.\n");
        return;
    }

    if ((*root)->left == NULL && (*root)->right == NULL) {
        free(*root);
        *root = NULL;
        printf("Ʈ���� ��� �ֽ��ϴ�.\n");
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

    printf("�ִ밪 %d ����\n", (*root)->data);

    (*root)->data = lastNode->data;

    if (parentNode->right == lastNode) {
        free(parentNode->right);
        parentNode->right = NULL;
    }
    else if (parentNode->left == lastNode) {
        free(parentNode->left);
        parentNode->left = NULL;
    }

    // ��Ʈ�������� �� �籸��
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
            printf("%d <-> %d ��ȯ\n", current->data, largerChild->data);
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

    printf("��尡 �̵��� Ƚ��: %d\n", moveCount);
}

// �ִ� �� Ʈ�� ����
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        insertMaxHeapTree(&root, inputData[i]);
    }
    return root;
}

// ���� ������� ���
void printLevelOrder(TreeNode* root) {
    if (root == NULL) {
        printf("Ʈ���� ��� �ֽ��ϴ�.\n");
        return;
    }

    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    int level = 1;
    printf("Ʈ�� ������ ���\n");
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