#include "pch.h"

#include <gtest/gtest.h>
extern "C" {
#include "C:\Users\nikib\source\repos\tests1\rb_test\rb_tree_test\rb_tree.h" 
}

// Глобальная переменная для корня дерева
Node* root;

// Вспомогательная функция для очистки дерева
void freeTree(Node* node) {
    if (node != NIL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

// Функция инициализации для тестов
void init_suite() {
    NIL = (Node*)malloc(sizeof(Node));
    NIL->color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    root = NIL;
}

// Функция очистки для тестов
void clean_suite() {
    freeTree(root);
    free(NIL);
}

// Тест функции insert
TEST(RBTreeTest, InsertTest) {
    init_suite();

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 15);
    insert(&root, 25);

    EXPECT_EQ(root->data, 20);
    EXPECT_EQ(root->left->data, 10);
    EXPECT_EQ(root->right->data, 30);
    EXPECT_EQ(root->right->left->data, 25);
    EXPECT_EQ(root->left->right->data, 15);

    clean_suite();
}

// Тест функции deleteNode
TEST(RBTreeTest, DeleteTest) {
    init_suite();

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 15);
    insert(&root, 25);

    Node* node_to_delete = root->right->left; // Узел с данными 25
    deleteNode(&root, node_to_delete);

    EXPECT_EQ(root->right->left, NIL);
    EXPECT_EQ(root->right->data, 30);
    EXPECT_EQ(root->left->right->data, 15);

    clean_suite();
}

