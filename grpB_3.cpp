/*Construct an expression tree from the given prefix expression eg. +--a*bc/def and traverse it using post order traversal (non recursive) and then delete the entire tree.*/

#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct Node {
    char data;
    Node *left = nullptr;
    Node *right = nullptr;
};

class Tree {
    public:
    Node *root = nullptr;
public:
    void buildTree(string prefix);
    void postOrderTraversal(Node *root);
    void deleteTree(Node *root);
};

void Tree::buildTree(string prefix) {
    stack<Node*> s;
    for (int i = prefix.length() - 1; i >= 0; i--) {
        Node *newNode = new Node;
        newNode->data = prefix[i];
        if (isalpha(prefix[i])) {
            s.push(newNode);
        } else {
            newNode->left = s.top();
            s.pop();
            newNode->right = s.top();
            s.pop();
            s.push(newNode);
        }
    }
    root = s.top();
}

void Tree::postOrderTraversal(Node *root) {
    stack<pair<Node*, bool>> s;
    s.push({ root, false });
    while (!s.empty()) {
        Node *node = s.top().first;
        bool visited = s.top().second;
        s.pop();
        if (node == nullptr) {
            continue;
        }
        if (visited) {
            cout << node->data << " ";
        } else {
            s.push({ node, true });
            s.push({ node->right, false });
            s.push({ node->left, false });
        }
    }
}

void Tree::deleteTree(Node *root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    cout <<endl<< "Deleting node : " << root->data;
    delete root;
}

int main() {
    string expr;
    cout << "Enter prefix expression: ";
    cin >> expr;
    Tree t;
    t.buildTree(expr);
    t.postOrderTraversal(t.root);
    t.deleteTree(t.root);
    return 0;
}
