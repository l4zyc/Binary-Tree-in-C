#include <stdio.h>
#include <stdlib.h>

//Create a node
struct Node {
    struct Node *left, *right;
    int value;
} *root = NULL;

struct Node* newNode(int value) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}


//insert node
struct Node* insert(struct Node* root, int value) {
    if(!root) {
        return newNode(value);
    } else if(root->value > value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

struct Node* delete(struct Node* root, int value) {
    if(root == NULL) {
        return root;
    } else {
        if(root->value > value) {
            root->left = delete(root->left, value);
        } else if(root->value < value) {
            root->right = delete(root->right, value);
        } else {
            struct Node* child = root->left ? root->left : root->right;

            if(!child) {
                struct Node* temp = child;
                root = NULL;
                free(root);
            } else if(!root->left || !root->right) {
                *root = *child;
            } else {
                struct Node *ptr = root->left;
                while(ptr->right) ptr = ptr->right;
                root->value = ptr->value;

                root->left = delete(root->left, ptr->value);
            }
        }
    }

    return root;
}

void inOrder(struct Node* root) {
    if(root == NULL) {
        return;
    } else {
        inOrder(root->left);
        printf("%d\n", root->value);
        inOrder(root->right);
    }
}

void update(struct Node *root, int value, int newValue) {
    if(root == NULL) {
        return;
    } else {
        update(root->left, value , newValue);
        if(root->value == value) {
            root->value = newValue;
            return;
        }
        update(root->right, value , newValue);
    }
}

int main() {
    root = insert(root, 2);
    root = insert(root, 1);
    root = insert(root, 3);
    delete(root,1);
    inOrder(root);
    return 0;
}