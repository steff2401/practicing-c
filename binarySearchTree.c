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

struct Node* minChild(struct Node *root) {
    if (root == NULL || root->left == NULL) {
        return root;
    }
    return minChild(root->left);
}

struct Node* delete(struct Node *root, int val) {
    if (root == NULL) {
        return root;
    }

    if (root->val == val) {
        // node to be deleted has no children
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        
        // node has one or more children
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;

        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;

        } else {
            struct Node *min = minChild(root->right);
            root->val = min->val;
            root->right = delete(root->right, min->val);
        }
        return root;
    }

    if (val < root->val) {
        root->left = delete(root->left, val);
    } else if (val > root->val) {
        root->right = delete(root->right, val);
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

    // Create a binary search tree
    struct Node *root = NULL;

    // Test inserting values
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, -5);
    root = insert(root, 0);
    root = insert(root, 30);
    root = insert(root, 25);

    printf("In-order traversal of the constructed tree is: ");
    printInorder(root);
    printf("\n");

    // Test deleting leaf node
    root = delete(root, -5);
    printf("In-order traversal of the tree after deleting -5: ");
    printInorder(root);
    printf("\n");

    // Test deleting node with one child
    root = delete(root, 30);
    printf("In-order traversal of the tree after deleting 30: ");
    printInorder(root);
    printf("\n");

    // Test deleting node with two children
    root = delete(root, 10);
    printf("In-order traversal of the tree after deleting 10: ");
    printInorder(root);
    printf("\n");

    // Test deleting root node
    root = delete(root, 20);
    printf("In-order traversal of the tree after deleting 20: ");
    printInorder(root);
    printf("\n");

    // Test deleting node that doesn't exist
    root = delete(root, 500);
    printf("In-order traversal of the tree after trying to delete 500: ");
    printInorder(root);
    printf("\n");

    // Test insert after delete
    root = insert(root, 100);
    printf("In-order traversal of the tree after inserting 100: ");
    printInorder(root);
    printf("\n");

    // Free memory
    destroyTree(root);

    return 0;
}
