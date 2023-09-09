// #include <iostream>

// using namespace std;

// struct Node{
//     string value;
//     Node* left;
//     Node* right;
// };

// Node* newNode(string _value){
//     Node* output;
//     output->value = _value;
//     output->left = NULL;
//     output->right = NULL;

//     return output;
// }

// int main(){
//     Node* root = newNode("&");

//     cout << root->value << endl; 
//     cout << root->left << endl;
//     return 0;
// }

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Function to evaluate the logical implication (=>)
bool implication(bool p, bool q) {
    return !p || q;
}

// Function to perform truth table checking for the expression
void truthTableCheck(const string& expression) {
    vector<string> tokens;
    unordered_map<string, bool> truthValues;

    // Tokenization
    string token;
    for (char c : expression) {
        if (c == '&' || c == ' ' || c == '=' || c == '>' || c == ';' || c == '(' || c == ')') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            if (c != ' ') {
                tokens.push_back(string(1, c));
            }
        } else {
            token += c;
        }
    }
    if (!token.empty()) tokens.push_back(token);

    // Generate the truth table
    int numPropositions = 0;
    for (const string& token : tokens) {
        if (token != "&" && token != "(" && token != ")" && token != "=" && token != ">" && token != ";" && !truthValues.count(token)) {
            truthValues[token] = false;
            numPropositions++;
        }
    }

    int numRows = 1 << numPropositions;
    cout << "Truth Table:" << endl;

    for (int i = 0; i < numRows; i++) {
        int mask = 1;
        for (const auto& pair : truthValues) {
            truthValues[pair.first] = i & mask;
            mask <<= 1;
        }

        // Evaluate the expressions
        vector<string>::const_iterator it = tokens.cbegin();
        bool expressionValue = true;
        while (it != tokens.cend()) {
            string token = *it;
            if (token == "(") {
                vector<string>::const_iterator subExpressionStart = it;
                vector<string>::const_iterator subExpressionEnd = tokens.cend();
                int countOpenParentheses = 1;
                int countCloseParentheses = 0;
                while (++it != tokens.cend()) {
                    if (*it == "(") {
                        countOpenParentheses++;
                    } else if (*it == ")") {
                        countCloseParentheses++;
                        if (countOpenParentheses == countCloseParentheses) {
                            subExpressionEnd = it;
                            break;
                        }
                    }
                }
                vector<string> subExpression(subExpressionStart + 1, subExpressionEnd);
                bool subExpressionValue = true;
                for (size_t i = 0; i < subExpression.size(); i++) {
                    if (subExpression[i] == "&") {
                        continue;
                    } else if (subExpression[i] == "=") {
                        continue;
                    } else if (subExpression[i] == ">") {
                        continue;
                    } else if (subExpression[i] == ";") {
                        continue;
                    } else {
                        string prop = subExpression[i];
                        if (prop == "0" || prop == "1") {
                            subExpressionValue &= prop == "1";
                        } else {
                            subExpressionValue &= truthValues[prop];
                        }
                    }
                }
                expressionValue &= subExpressionValue;
            } else {
                it++;
            }
        }

        // Output the truth table row
        for (const auto& pair : truthValues) {
            cout << pair.second << " ";
        }
        cout << "| " << expressionValue << endl;
    }
}

int main() {
    string expression = "p1 & p2 => a; a => b";

    truthTableCheck(expression);

    return 0;
}

