#include <stdio.h>
#include <stdlib.h>

// Определение структуры узла красно-черного дерева
typedef struct Node {
    int data;
    enum { RED, BLACK } color;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
} Node;

// Создание нового узла
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Ошибка: Не удалось выделить память для нового узла\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->color = RED; // Новый узел всегда красный
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// Балансировка дерева после вставки
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


// Добавление элемента в красно-черное дерево
void insert(Node** root, int data) {
    // Вставка узла как в обычное бинарное дерево
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

// Удаление элемента из красно-черного дерева
// Удаление элемента из красно-черного дерева
void deleteNode(Node** root, int data) {
    Node* current = *root;
    Node* parent = NULL;
    Node* nodeToDelete = NULL;
    // Находим узел для удаления
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
    // Узел не найден
    if (nodeToDelete == NULL) {
        printf("Узел для удаления не найден\n");
        return;
    }
    // У узла есть два потомка
    if (nodeToDelete->left != NULL && nodeToDelete->right != NULL) {
        Node* successor = nodeToDelete->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
        nodeToDelete->data = successor->data;
        nodeToDelete = successor;
    }
    // У узла есть только один потомок или он листовой
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
    // Если удаляется красный узел, дерево остается валидным
    if (nodeToDelete->color == BLACK) {
        // Вызываем функцию балансировки только если узел удален не черный
        if (child != NULL && child->color == RED) {
            child->color = BLACK;
        }
        else {
            fixDelete(root, child, nodeToDelete->parent);
        }
    }
    free(nodeToDelete);
}

// Восстановление свойств красно-черного дерева после удаления узла
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

    // Пример использования: добавление элементов
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 5);

    // Пример использования: удаление элемента
    delete(&root, 20);

    // Освобождение памяти для всего дерева

    freeTree(root);

    return 0;
}