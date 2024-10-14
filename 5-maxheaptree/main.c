#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void runUserInterface(TreeNode* root) {
    char command;
    int value;

    while (1) {
        printf("\n�޴��� �����ϼ��� (i: ��� �߰�, d: ��� ����, p: ������ ���, c: ����): ");
        scanf(" %c", &command);

        switch (command) {
        case 'i': // ����
            printf("������ ���� �Է��ϼ���: ");
            scanf("%d", &value);
            insertMaxHeapTree(&root, value);
            break;
        case 'd': // ����
            deleteMaxHeapTree(&root);
            break;
        case 'p': // ���
            printLevelOrder(root);
            break;
        case 'c': // ����
            printf("���α׷��� �����մϴ�.\n");
            return;
        default:
            printf("�߸��� ����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }
}

int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 13, 21, 18, 5 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = generateMaxHeapTree(inputData, size);

    runUserInterface(root);

    return 0;
}
