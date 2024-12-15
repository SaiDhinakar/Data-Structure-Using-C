// Tree Traversal using C
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node *CreateNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the binary tree
struct Node *InsertToTree(struct Node *root, struct Node *node) {
    if (root == NULL) {
        return node; // Return the node as the new root
    }

    if (node->data < root->data) {
        // Insert into the left subtree
        root->left = InsertToTree(root->left, node);
    } else if (node->data > root->data) {
        // Insert into the right subtree
        root->right = InsertToTree(root->right, node);
    }

    return root; // Return the (unchanged) root node
}

// Function to print the tree (in-order traversal)
void InOrderTraversal(struct Node *root) {
    if (root != NULL) {
        InOrderTraversal(root->left);
        printf("%d ", root->data);
        InOrderTraversal(root->right);
    }
}

void PostOrderTraversal(struct Node *root){
    if (root != NULL){
        PostOrderTraversal(root->left);
        PostOrderTraversal(root->right);
        printf("%d ", root->data);
    }
}

void PreOrderTraversal(struct Node *root){
    if (root != NULL){
        printf("%d ", root->data);
        PreOrderTraversal(root->left);
        PreOrderTraversal(root->right);
    }
}

int main() {
    struct Node *root = NULL; // Initialize root as NULL
    int n = 7;

    int num[] = {100,50,150,25,125,55,160};

    for (int i = 0; i < n; i++) {
        struct Node *newNode = CreateNode(num[i]); // Create a new node
        root = InsertToTree(root, newNode);    // Insert into the tree
    }

    printf("In-order traversal of the tree: ");
    InOrderTraversal(root);
    printf("\n");

    printf("Pre-order traversal of the tree: ");
    PreOrderTraversal(root);
    printf("\n");

    printf("Post-order traversal of the tree: ");
    PostOrderTraversal(root);
    printf("\n");

    return 0;
}
