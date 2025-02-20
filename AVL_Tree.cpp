#include <iostream>

using namespace std;

struct AVL_Node {
    int key;
    size_t height;
    AVL_Node* left;
    AVL_Node* right;
    AVL_Node(int k) { key = k; left = right = nullptr; height = 1; }
};

size_t height(AVL_Node* p) {
    return p ? p->height : 0;
}

int balance_factor(AVL_Node* p) {
    return height(p->right) - height(p->left);
}

void fix_height(AVL_Node* p) {
    size_t h_left = height(p->left);
    size_t h_right = height(p->right);
    p->height = (h_left > h_right ? h_left : h_right) + 1;
}

AVL_Node* rotate_left(AVL_Node* q) {
    AVL_Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fix_height(q);
    fix_height(p);
    return p;
}

AVL_Node* rotate_right(AVL_Node* p) {
    AVL_Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fix_height(p);
    fix_height(q);
    return q;
}

AVL_Node* balance(AVL_Node* p) {
    fix_height(p);
    if (balance_factor(p) == 2) {
        if (balance_factor(p->right) < 0)
            p->right = rotate_right(p->right);
        return rotate_left(p);
    }
    if (balance_factor(p) == -2) {
        if (balance_factor(p->left) > 0)
            p->left = rotate_left(p->left);
        return rotate_right(p);
    }
    return p;
}

AVL_Node* insert(AVL_Node* p, int k) {
    if (p == nullptr) return new AVL_Node(k);
    if (k < p->key) {
        p->left = insert(p->left, k);
    }
    else {
        p->right = insert(p->right, k);
    }
    return balance(p);
}

AVL_Node* find_min(AVL_Node* p) {
    return p->left ? find_min(p->left) : p;
}

AVL_Node* remove_min(AVL_Node* p) {
    if (p->left == nullptr)
        return p->right;
    p->left = remove_min(p->left);
    return balance(p);
}

AVL_Node* remove(AVL_Node* p, int k) {
    if (p == nullptr) return 0;
    if (k < p->key) {
        p->left = remove(p->left, k);
    }
    else if (k > p->key) {
        p->right = remove(p->right, k);
    }
    else {
        AVL_Node* left = p->left;
        AVL_Node* right = p->right;
        delete p;
        if (right == nullptr) return left;
        AVL_Node* min = find_min(right);
        min->right = remove_min(right);
        min->left = left;
        return balance(min);
    }
    return balance(p);
}

void in_order(AVL_Node* p) {
    if (p != nullptr) {
        in_order(p->left);
        cout << p->key << " ";
        in_order(p->right);
    }
}

void pre_order(AVL_Node* node) {
    if (node) {
        cout << node->key << " ";
        pre_order(node->left);
        pre_order(node->right);
    }
    else { return; }
}

void post_order(AVL_Node* node) {
    if (node) {
        post_order(node->left);
        post_order(node->right);
        cout << node->key << " ";
    }
    else { return; }
}

bool search(AVL_Node* p, int key) {
    if (p == nullptr) return false;
    if (key == p->key) return true;
    if (key < p->key) return search(p->left, key);
    return search(p->right, key);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    AVL_Node* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 20);
    root = insert(root, 12);

    cout << "Дерево по порядку: ";
    in_order(root);
    cout << endl;

    root = remove(root, 10);
    cout << "После удаления 10: ";
    in_order(root);
    cout << endl;

    root = insert(root, 0);
    cout << "После вставки 0: ";
    in_order(root);
    cout << endl;

    cout << "Есть ли 10 в дереве?" << (search(root, 10) ? " Да" : " Нет") << endl;
    cout << "Есть ли 5 в дереве?" << (search(root, 5) ? " Да" : " Нет") << endl;
    cout << "Есть ли 0 в дереве?" << (search(root, 0) ? " Да" : " Нет") << endl;

    return 0;
}
