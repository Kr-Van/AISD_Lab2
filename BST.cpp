#include <iostream>

using namespace std;

struct BST_Node {
    int data;
    BST_Node* left;
    BST_Node* right;
};

BST_Node* new_one(int data) {
    BST_Node* newNode = new BST_Node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

BST_Node* insert_node(BST_Node* root, int data) {
    if (root == nullptr) {
        return new_one(data);
    }

    if (data < root->data) {
        root->left = insert_node(root->left, data);

    }

    else if (data > root->data) {
        root->right = insert_node(root->right, data);
    }

    return root;
}

void in_order(BST_Node* root) {
    if (root != nullptr) {
        in_order(root->left);
        cout << root->data << " ";
        in_order(root->right);
    }
}

void pre_order(BST_Node* node) {
    if (node) {
        cout << node->data << " ";
        pre_order(node->left);
        pre_order(node->right);
    }
    else { return; }
}

void post_order(BST_Node* node) {
    if (node) {
        post_order(node->left);
        post_order(node->right);
        cout << node->data << " ";
    }
    else { return; }
}

BST_Node* search_node(BST_Node* root, int key) {
    if (root == nullptr || root->data == key) {
        return root;
    }

    if (root->data < key) {
        return search_node(root->right, key);
    }

    return search_node(root->left, key);
}

BST_Node* min_val(BST_Node* node) {
    BST_Node* cur = node;
    while (cur && cur->left != nullptr) {
        cur = cur->left;
    }
    return cur;
}

BST_Node* delete_n(BST_Node* root, int data) {
    if (root == nullptr)
        return root;

    if (data < root->data) {
        root->left = delete_n(root->left, data);
    }

    else if (data > root->data) {
        root->right = delete_n(root->right, data);
    }

    else {
        if (root->left == nullptr) {
            BST_Node* temp = root->right;
            delete root;
            return temp;
        }

        else if (root->right == nullptr) {
            BST_Node* temp = root->right;
            delete root;
            return temp;
        }

        BST_Node* temp = min_val(root->right);
        root->data = temp->data;
        root->right = delete_n(root->right, temp->data);
    }
    return root;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    BST_Node* root = nullptr;

    root = insert_node(root, 44);
    root = insert_node(root, 33);
    root = insert_node(root, 10);
    root = insert_node(root, 81);
    root = insert_node(root, 4);
    root = insert_node(root, 16);
    root = insert_node(root, 3);
    root = insert_node(root, 55);

    cout << "Дерево по порядку:";
    in_order(root);
    cout << endl;

    root = delete_n(root, 3);
    cout << "После удаления 3: ";
    in_order(root);
    cout << endl;

    root = insert_node(root, 0);
    cout << "После вставки 0: ";
    in_order(root);
    cout << endl;

    cout << "3 есть в дереве? " << (search_node(root, 3) ? "Да" : "Нет") << endl;
    cout << "0 есть в дереве? " << (search_node(root, 0) ? "Да" : "Нет") << endl;
    cout << "16 есть в дереве? " << (search_node(root, 16) ? "Да" : "Нет") << endl;

    return 0;

}
