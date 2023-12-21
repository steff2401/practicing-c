#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node *left;
    struct Node *right;
};

struct Node* insert(struct Node *root, int val) {
    
    // base case
    if (root == NULL) {
        struct Node *node = malloc(sizeof(struct Node));
        if (node == NULL) {
            printf("Memory allocation failed.");
            exit(EXIT_FAILURE);
        }
        node->val = val;
        node->right = NULL;
        node->left = NULL;
        return node;
    }

    // recursive case
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else if (val > root->val) {
        root->right = insert(root->right, val);
    }
    return root;
}

void printInorder(struct Node *root) {
    if (root == NULL) {
        return;
    }

    printInorder(root->left);
    printf("%d, ", root->val);
    printInorder(root->right);
}

void destroyTree(struct Node *root) {
    if (root == NULL) {
        return;
    }
    
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

int main(void) {

    struct Node *root = insert(NULL,10);
    insert(root,5);
    insert(root,15);
    insert(root,-10);

    printInorder(root);
    printf("\n");

    destroyTree(root);

    return 0;
}