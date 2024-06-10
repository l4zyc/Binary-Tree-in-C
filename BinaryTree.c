#include <stdlib.h>
#include <stdio.h>

struct Node {
    int value;  
    struct Node *right, *left;
} *root = NULL;

struct Node* newNode(int value) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->right = NULL;
    node->left = NULL;
    node->value = value;
    
    return node;
}

struct Node* insertNode(struct Node *root, int value) {
    if(root == NULL) {
        return newNode(value);
    } else if(root->value > value) {
        root->left = insertNode(root->left, value);
    } else {
        root->right = insertNode(root->right, value);
    }
    return root;
}

void inOrder(struct Node *root) {
    if(root == NULL) {
        return;
    } else {
        inOrder(root->left);
        printf("%d ", root->value);
        inOrder(root->right);
    }
}

struct Node* delete(struct Node *root, int value) {
    if(root == NULL) {
        return root;
    } else {
        if(root->value > value) {
            root->left = delete(root->left, value);
        } else if(root->value < value) {
            root->right = delete(root->right, value);
        } else {
            struct Node* child = root->left ? root->left : root->right;

            if(child == NULL) {
                struct Node* temp = root;
                root = NULL;
                free(temp);
            } else {
                if(!root->left || !root->right) {
                    *root = *child;
                } else {
                    struct Node *ptr = root->left;
                    while(ptr->right) ptr = ptr->right;

                    root->value = ptr->value;
                    root->left = delete(root->left, ptr->value);
                }
            }
        }
    }

    return root;
}

void update(struct Node *root, int value, int newValue) {
    if(root == NULL) {
        return;
    } else {
        update(root->left, value, newValue);
        if(root->value == value) {
            root->value = newValue;
        }
        update(root->right, value, newValue);
    }

}

int main() {
    root = insertNode(root, 1);
    root = insertNode(root, 3);
    root = insertNode(root, 2);
    delete(root,1);
    inOrder(root);

    return 0;
}