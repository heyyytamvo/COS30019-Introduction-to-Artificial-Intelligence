#include <iostream>
using namespace std;

struct Node {
    string data; // Data of the node (operator or propositional symbol)

    Node* left;  // Left child (for binary operators)
    Node* right; // Right child (for binary operators)

    Node(string data) : data(data), left(nullptr), right(nullptr) {}
};

Node* constructAST(string expression, int& index) {
    Node* node = nullptr;

    while (index < expression.size()) {
        char currentChar = expression[index];

        if (currentChar == '(') {
            // Recursively construct the left subtree for binary operators
            index++; // Move to the next character after '('
            node = constructAST(expression, index);
        } else if (currentChar == ')') {
            // End of the subtree, return the current node
            index++; // Move to the next character after ')'
            return node;
        } else if (currentChar == '&' || currentChar == '|' || currentChar == '<' || currentChar == '=') {
            // Binary operator nodes
            node = new Node(expression.substr(index, 1)); // Operator node
            index++; // Move to the next character after the operator

            // Construct the left and right subtrees
            node->left = constructAST(expression, index);
            node->right = constructAST(expression, index);
            return node;
        } else {
            // Propositional symbol node (e.g., a, b, c, etc.)
            node = new Node(expression.substr(index, 1)); // Symbol node
            index++; // Move to the next character after the symbol
            return node;
        }
    }

    return node;
}

int main() {
    string logicalExpression = "(a <=> (c => ~d)) & b & (b => a)";
    int index = 0;

    Node* root = constructAST(logicalExpression, index);

    // Use the root node of the AST for further processing or evaluation.

    return 0;
}
