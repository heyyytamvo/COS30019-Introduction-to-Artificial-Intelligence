#ifndef LogicalExpression_H
#define LogicalExpression_H

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;



class logicalExpression{
    private:
        /* data */

        string orginalString;
        string connective;
        vector<logicalExpression> listOfChildren;
        bool OnlySymbol;
        vector<string> listOfSymbols;

    // Function to remove whitespaces from a string
    string removeWhiteSpace(string inputString) {
        size_t firstNonSpace = inputString.find_first_not_of(" \t\n\r");
        size_t lastNonSpace = inputString.find_last_not_of(" \t\n\r");

        if (firstNonSpace == string::npos || lastNonSpace == string::npos) {
        // The string contains only whitespaces or is empty
            return "";
        }

        return inputString.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
    }

    // function that splits the logical expression into smaller part
    void split(string sentence){
        int bracketCount = 0;
        int operatorIndex = -1;
        sentence = removeWhiteSpace(sentence);
        bool dontHaveConnective = true;
        /// traverse the sentence
        for (int i = 0; i < sentence.size(); i++){
            char currentChar = sentence[i];

            // open bracket
            if (currentChar == '('){
                bracketCount++;
            }

            // close bracket
            else if (currentChar == ')')
            {
                bracketCount--;
            }

            // the connective is <=>
            else if (currentChar == '<' && bracketCount == 0 && dontHaveConnective){
                operatorIndex = i;
                dontHaveConnective = false;
                // cout << "NUCLEAR" << endl;
            }

            // the connective is =>
            else if (currentChar == '=' && sentence[i + 1] == '>' && bracketCount == 0 && dontHaveConnective){
                // cout << "BOOM" << endl;
                dontHaveConnective = false;
                operatorIndex = i;
            }

            // the connective is &
            else if (currentChar == '&' && bracketCount == 0){
                operatorIndex = i;
            }

            // the connective is || 
            else if (currentChar == '|' && sentence[i + 1] == '|' && bracketCount == 0){
                operatorIndex = i;
            }

            // the connective is ~
            else if (currentChar == '~' && bracketCount == 0 && operatorIndex < 0){
                operatorIndex = i;
            }
        }
        // cout << operatorIndex << endl;
        // if 
        if (operatorIndex < 0){
            sentence = removeWhiteSpace(sentence);
            if (sentence[0] == '('){
                string newSentence = sentence.substr(1, sentence.size() - 2);
                split(newSentence);
            }
        }else{
            // connective is <=>
            if (sentence[operatorIndex] == '<'){
                string leftSide = removeWhiteSpace(sentence.substr(0, operatorIndex - 1));
                string rightSide = removeWhiteSpace(sentence.substr(operatorIndex + 3, sentence.size()));

                logicalExpression leftChild = logicalExpression(leftSide);
                logicalExpression rightChild = logicalExpression(rightSide);
                listOfChildren.push_back(leftChild);
                listOfChildren.push_back(rightChild);
                connective = "<=>";
            }
            // connective is =>
            else if (sentence[operatorIndex] == '='){
                string leftSide = removeWhiteSpace(sentence.substr(0, operatorIndex));
                string rightSide = removeWhiteSpace(sentence.substr(operatorIndex + 2, sentence.size()));

                logicalExpression leftChild = logicalExpression(leftSide);
                logicalExpression rightChild = logicalExpression(rightSide);
                listOfChildren.push_back(leftChild);
                listOfChildren.push_back(rightChild);
                connective = "=>";
                // cout << "LOLO" << endl;
            }
            // connective is &
            else if (sentence[operatorIndex] == '&'){
                string leftSide = removeWhiteSpace(sentence.substr(0, operatorIndex));
                string rightSide = removeWhiteSpace(sentence.substr(operatorIndex + 1, sentence.size()));

                logicalExpression leftChild = logicalExpression(leftSide);
                logicalExpression rightChild = logicalExpression(rightSide);
                listOfChildren.push_back(leftChild);
                listOfChildren.push_back(rightChild);
                connective = "&";
            }
            // connective is ||
            else if (sentence[operatorIndex] == '|'){
                string leftSide = removeWhiteSpace(sentence.substr(0, operatorIndex));
                string rightSide = removeWhiteSpace(sentence.substr(operatorIndex + 2, sentence.size()));

                logicalExpression leftChild = logicalExpression(leftSide);
                logicalExpression rightChild = logicalExpression(rightSide);
                listOfChildren.push_back(leftChild);
                listOfChildren.push_back(rightChild);
                connective = "||";
            }
            // connective is ~
            else if (sentence[operatorIndex] == '~'){
                string leftSide = removeWhiteSpace(sentence.substr(operatorIndex + 1, sentence.size()));
                logicalExpression leftChild = logicalExpression(leftSide);
                listOfChildren.push_back(leftChild);
                connective = "~";
            }
        }
    }



    public:
        logicalExpression(string sentence){
            orginalString = removeWhiteSpace(sentence);

            /// if the current logical expression contains a connective
            if ((orginalString.find("<=>") != string::npos) || (orginalString.find("=>") != string::npos) || (orginalString.find("&") != string::npos) || (orginalString.find("||") != string::npos) || (orginalString.find("~") != string::npos)){
                OnlySymbol = false;
                split(orginalString);
            }else{
                OnlySymbol = true;
            }

            /// intialising the list off all symbols
            for (int i = 0; i < listOfChildren.size(); i++){
                logicalExpression current = listOfChildren[i];
            }
        }

        // get original string
        string getOriginalExpression(){
            return orginalString;
        }

        vector<logicalExpression> getChildren(){
            return listOfChildren;
        }

        bool containOnlySymbol(){
            return OnlySymbol;
        }

        string gettingConnective(){
            return connective;
        }

    };

#endif