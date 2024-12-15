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

int main() {
    struct Node *root = NULL; // Initialize root as NULL
    int n, num;

    printf("Enter the number of nodes to insert: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter node value: ");
        scanf("%d", &num);
        struct Node *newNode = CreateNode(num); // Create a new node
        root = InsertToTree(root, newNode);    // Insert into the tree
    }

    printf("In-order traversal of the tree: ");
    InOrderTraversal(root);
    printf("\n");

    return 0;
}
