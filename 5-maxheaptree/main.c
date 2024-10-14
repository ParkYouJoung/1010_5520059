#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void runUserInterface(TreeNode* root) {
    char command;
    int value;

    while (1) {
        printf("\n메뉴를 선택하세요 (i: 노드 추가, d: 노드 삭제, p: 레벨별 출력, c: 종료): ");
        scanf(" %c", &command);

        switch (command) {
        case 'i': // 삽입
            printf("삽입할 값을 입력하세요: ");
            scanf("%d", &value);
            insertMaxHeapTree(&root, value);
            break;
        case 'd': // 삭제
            deleteMaxHeapTree(&root);
            break;
        case 'p': // 출력
            printLevelOrder(root);
            break;
        case 'c': // 종료
            printf("프로그램을 종료합니다.\n");
            return;
        default:
            printf("잘못된 명령입니다. 다시 시도하세요.\n");
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
