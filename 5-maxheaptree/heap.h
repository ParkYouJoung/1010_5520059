#pragma once

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

extern TreeNode* createNode(int data);
extern void insertMaxHeapTree(TreeNode** root, int value);
extern void deleteMaxHeapTree(TreeNode** root);
extern TreeNode* generateMaxHeapTree(int inputData[], int size);
extern void printLevelOrder(TreeNode* root);