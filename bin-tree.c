#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <malloc.h>

struct node {
    int data;
    int pos;
    struct node *left;
    struct node *right;
};

struct node *AddNode(int num, struct node *tree, int count) {
    if(tree == NULL) {
        tree = (struct node *)malloc(sizeof(struct node));
        tree->data = num;
        tree->pos = count;
        tree->left = NULL;
        tree->right = NULL;
    }
    else if(num < tree->data) tree->left = AddNode(num, tree->left, count + 1);
    else tree->right = AddNode(num, tree->right, count + 1);
    return tree;
}

void PrintTree(struct node *tree) {
    if (tree != NULL) {
        printf("(%d)%d ", tree->pos, tree->data);
        PrintTree(tree->left);
        PrintTree(tree->right);
    }
}

int FindKey(struct node *tree, int key) {
    int nearest = tree->data;
    while (tree != NULL) {
        if(key == tree->data) return tree->data;
        else if(tree->data < key && tree->data > nearest) nearest = tree->data;
        else if(tree->data > key && tree->data < nearest) nearest = tree->data;
        if(key < tree->data) tree = tree->left;
        else tree = tree->right;
    }
    return nearest;
}

struct node *FillTree(int n, int low, int high) {
    struct node *tree = NULL;
    for(int i = 0; i < n; i++) {
        tree = AddNode(low + rand()%(high - low + 1), tree, 0);
    }
    return tree;
}

void FreeTree(struct node *tree) {
    if(tree != NULL) {
        FreeTree(tree->left);
        FreeTree(tree->right);
        free(tree);
    }
}

int main() {
    srand(time(NULL));
    int n;
    printf("tree size: ");
    scanf("%d", &n);
    struct node *tree = FillTree(n, 0, 180);
    PrintTree(tree);

    int key;
    printf("\nvalue to find: ");
    scanf("%d", &key);
    int r = FindKey(tree, key);
    if(r == key) printf("exact value found: %d", r);
    else printf("nearest value found: %d", r);

    FreeTree(tree);
    getch();
    return 0;
}
