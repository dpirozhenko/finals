#include <iostream>
#include <string>

using namespace std;

// Клас вузла бінарного дерева
class Node {
public:
    char data;
    Node* left;
    Node* right;

    Node(char value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Клас бінарного дерева
class Tree {
private:
    Node* root;

    Node* createBinaryTree(string str, int& index) {
        if (index >= str.length() || str[index] == '#') {
            return nullptr;
        }

        Node* newNode = new Node(str[index]);
        index++;
        newNode->left = createBinaryTree(str, index);
        index++;
        newNode->right = createBinaryTree(str, index);

        return newNode;
    }

    void preorderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }

        cout << node->data << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    void inorderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }

        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

public:
    Tree() {
        root = nullptr;
    }

    void createTree(string str) {
        int index = 0;
        root = createBinaryTree(str, index);
    }

    void preorder() {
        cout << "Preorder: ";
        preorderTraversal(root);
        cout << endl;
    }

    void inorder() {
        cout << "symetrical: ";
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    string input;
    cout << "enter a string: ";
    getline(cin, input);

    Tree tree;
    tree.createTree(input);

    tree.preorder();
    tree.inorder();

    return 0;
}
