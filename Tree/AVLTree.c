#include <stdlib.h>
#include <stdio.h>

struct Node{
    int key;
    struct Node *left, *right;
    int height;
};

int height(struct Node *node){
    return node == NULL ? 0 : node->height;
}

int max(int a, int b){
    return (a < b) ? a : b;
}

struct Node* createNode(int key){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key   = key;
    node->left  = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node* rightrotate(struct Node* y){
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

struct Node* leftrotate(struct Node* x){
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct Node* node){
    return node ? height(node->left) - height(node->right) : 0;
}

struct Node* insert(struct Node* node, int key){
    if(node == NULL){
        return createNode(key);
    }
    if (key < node->key){
        node -> left = insert(node->left, key);
    }
    else if (key > node->key){
        node -> right = insert(node->right, key);
    }
    else
        return node;

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightrotate(node);
        
    if (balance < -1 && key > node->right->key)
        return leftrotate(node);

    if (balance > 1  && key > node->left->key){
        node->left = leftrotate(node->left);
        return rightrotate(node);
    }

    if (balance < -1 && key < node->right->key){
        node->right = rightrotate(node->right);
        return leftrotate(node);
    }

    return node;
}

void inorder(struct Node* node){
    if(node != NULL){
        inorder(node->left);
        printf("%d ->", node->key);
        inorder(node->right);
    }
}

int main() {
    struct Node* root = NULL;

    // Insert nodes
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Print the tree
    printf("Inorder traversal of the AVL tree is:\n");
    inorder(root);

    return 0;
}
