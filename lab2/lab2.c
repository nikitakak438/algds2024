#include <stdio.h>
#include <stdlib.h>

// ����������� ��������� ���� ������-������� ������
typedef struct Node {
    int data;
    enum { RED, BLACK } color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

// �������� ������ ����
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "������: �� ������� �������� ������ ��� ������ ����\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->color = RED; // ����� ���� ������ �������
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// ������������ ������ ����� �������
void fixInsert(Node** root, Node* newNode) {
    while (newNode != *root && newNode->parent->color == RED) {
        if (newNode->parent == newNode->parent->parent->left) {
            Node* uncle = newNode->parent->parent->right;
            if (uncle != NULL && uncle->color == RED) {
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            }
            else {
                if (newNode == newNode->parent->right) {
                    newNode = newNode->parent;
                    leftRotate(root, newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                rightRotate(root, newNode->parent->parent);
            }
        }
        else {
            Node* uncle = newNode->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
                newNode->parent->color = BLACK;
                uncle->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            }
            else {
                if (newNode == newNode->parent->left) {
                    newNode = newNode->parent;
                    rightRotate(root, newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                leftRotate(root, newNode->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}


// ���������� �������� � ������-������ ������
void insert(Node** root, int data) {
    // ������� ���� ��� � ������� �������� ������
    Node* newNode = createNode(data);
    Node* parent = NULL;
    Node* current = *root;
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    newNode->parent = parent;
    if (parent == NULL) {
        *root = newNode;
    }
    else if (data < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
    fixInsert(root, root); //&&&&&&&&&&&&&&&&&&&
}

// �������� �������� �� ������-������� ������
// �������� �������� �� ������-������� ������
void deleteNode(Node** root, int data) {
    Node* current = *root;
    Node* parent = NULL;
    Node* nodeToDelete = NULL;
    // ������� ���� ��� ��������
    while (current != NULL) {
        if (data == current->data) {
            nodeToDelete = current;
            break;
        }
        parent = current;
        if (data < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    // ���� �� ������
    if (nodeToDelete == NULL) {
        printf("���� ��� �������� �� ������\n");
        return;
    }
    // � ���� ���� ��� �������
    if (nodeToDelete->left != NULL && nodeToDelete->right != NULL) {
        Node* successor = nodeToDelete->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
        nodeToDelete->data = successor->data;
        nodeToDelete = successor;
    }
    // � ���� ���� ������ ���� ������� ��� �� ��������
    Node* child = (nodeToDelete->left != NULL) ? nodeToDelete->left : nodeToDelete->right;
    if (child != NULL) {
        child->parent = nodeToDelete->parent;
    }
    if (nodeToDelete->parent == NULL) {
        *root = child;
    }
    else if (nodeToDelete == nodeToDelete->parent->left) {
        nodeToDelete->parent->left = child;
    }
    else {
        nodeToDelete->parent->right = child;
    }
    // ���� ��������� ������� ����, ������ �������� ��������
    if (nodeToDelete->color == BLACK) {
        // �������� ������� ������������ ������ ���� ���� ������ �� ������
        if (child != NULL && child->color == RED) {
            child->color = BLACK;
        }
        else {
            fixDelete(root, child, nodeToDelete->parent);
        }
    }
    free(nodeToDelete);
}

// �������������� ������� ������-������� ������ ����� �������� ����
void fixDelete(Node** root, Node* node, Node* parent) {
    Node* sibling;
    while ((node == NULL || node->color == BLACK) && node != *root) {
        if (node == parent->left) {
            sibling = parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                leftRotate(root, parent);
                sibling = parent->right;
            }
            if ((sibling->left == NULL || sibling->left->color == BLACK) &&
                (sibling->right == NULL || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = parent;
                parent = node->parent;
            }
            else {
                if (sibling->right == NULL || sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rightRotate(root, sibling);
                    sibling = parent->right;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                sibling->right->color = BLACK;
                leftRotate(root, parent);
                node = *root;
                break;
            }
        }
        else {
            sibling = parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                rightRotate(root, parent);
                sibling = parent->left;
            }
            if ((sibling->left == NULL || sibling->left->color == BLACK) &&
                (sibling->right == NULL || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = parent;
                parent = node->parent;
            }
            else {
                if (sibling->left == NULL || sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    leftRotate(root, sibling);
                    sibling = parent->left;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                sibling->left->color = BLACK;
                rightRotate(root, parent);
                node = *root;
                break;
            }
        }
    }
    if (node != NULL) {
        node->color = BLACK;
    }
}


void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}


int main() {
    Node* root = NULL;

    // ������ �������������: ���������� ���������
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);

    // ������ �������������: �������� ��������
    delete(&root, 20);

    // ������������ ������ ��� ����� ������

    freeTree(root);

    return 0;
}