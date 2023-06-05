//
// Created by mango on 03.06.23.
//

#include "BST.h"

BST::BST() noexcept {
    comparisions = 0;
    swapOrView = 0;
}


BST::~BST() noexcept
{
    deleteTree(root);
}

void BST::deleteTree(Node *node) noexcept
{
    if(node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

bool BST::compare(size_t a, size_t b){
    comparisions++;
    return a < b;
}

void BST::insert(size_t val) noexcept
{
    Node* y = nullptr;
    Node* x = root;
    Node* z = new Node;

    z->key = val;

    swapOrView++;
    while(x != nullptr)
    {
        swapOrView++;
        y = x;
        if(compare(z->key, x->key))
            x = x->left;
        else
            x = x->right;
    }

    swapOrView++;
    z->parent = y;

    swapOrView+=2;
    if (y == nullptr)
        root = z;
    else if(compare(z->key, y->key))
        y->left = z;
    else
        y->right = z;
}

Node * BST::deleteFirstOf(size_t val) noexcept
{
    Node* z = iterativeTreeSearch(root, val);
    swapOrView++;
    if(z == nullptr)
    {
        return nullptr;
    }

    Node *y, *x;

    swapOrView+=2;
    if(z->left == nullptr || z->right == nullptr)
        y = z;
    else
        y = successor(z);


    swapOrView++;
    if(y->left != nullptr)
        x = y->left;
    else
        x = y->right;
    swapOrView++;
    if(x != nullptr) {
        swapOrView++;
        x->parent = y->parent;
    }

    swapOrView+=2;
    if (y->parent == nullptr)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    swapOrView++;
    if (y != z) {
        z->key = y->key;
    }

    return y;
}

size_t BST::height(Node *node) noexcept
{
    if(node == nullptr)
        return 0;

    size_t hLeft = height(node->left);
    size_t hRight = height(node->right);

    if(hLeft > hRight)
        return hLeft + 1;
    else
        return hRight + 1;
}

Node *BST::iterativeTreeSearch(Node *x, size_t k) noexcept
{
    swapOrView++;
    while(x != nullptr && k != x->key)
    {
        swapOrView++;
        if(compare(k,x->key))
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

Node *BST::successor(Node *x) noexcept
{
    swapOrView++;
    if(x->right != nullptr)
        return minimum(x->right);

    Node* y = x->parent;
    swapOrView++;
    while(y != nullptr && x == y->right)
    {
        swapOrView+=2;
        x = y;
        y = y->parent;
    }
    return y;
}

Node *BST::minimum(Node *x) noexcept
{
    swapOrView++;
    while (x->left != nullptr)
        swapOrView++;
        x = x->left;
    return x;
}

Node *BST::maximum(Node *x) noexcept
{
    swapOrView++;
    while (x->right != nullptr)
        swapOrView++;
        x = x->right;
    return x;
}

void BST::print(Node *node, int depth, char prefix, char *leftTrace, char *rightTrace) noexcept
{
    if (node == nullptr || leftTrace == nullptr || rightTrace == nullptr)
        return;
    if (node->left != nullptr)
        print(node->left, depth + 1, '/', leftTrace, rightTrace);
    if (prefix == '/')
        leftTrace[depth-1] = '|';
    if (prefix == '\\')
        rightTrace[depth-1] = ' ';
    if (depth == 0)
        std::printf("-");
    if (depth > 0)
        std::printf(" ");
    for (int i = 0; i < depth - 1; ++i)
    {
        if (leftTrace[i] == '|' || rightTrace[i] == '|')
            printf("| ");
        else
            printf("  ");
    }
    if (depth > 0)
        printf("%c-", prefix);
    printf("[%zu]\n", node->key);
    leftTrace[depth]=' ';
    if( node->right != nullptr ){
        rightTrace[depth]='|';
        print(node->right, depth + 1, '\\', leftTrace, rightTrace);
    }
}
