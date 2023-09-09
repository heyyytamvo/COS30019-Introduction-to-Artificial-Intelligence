#ifndef TruthTableGKB_H
#define TruthTableGKB_H

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include "logicalExpression.h"
#include "AdvancedKB.h"

using namespace std;

class TruthTableGenericKB
{
    private:
        /* data */
        int kbCount;
    
        

        bool PL_TrueAlpha(string _query, map<string, bool> model){
        
            return model[_query];
        }
        
        bool LogicalExpressionChecking(logicalExpression LE, map<string, bool> model){
            if (LE.containOnlySymbol()){
                return model[LE.getOriginalExpression()];
            }

            
            vector<logicalExpression> listOfChild = LE.getChildren();
            if (listOfChild.size() == 2){
                string connective = LE.gettingConnective();
                // if the connective is <=>
                if (connective == "<=>"){
                    logicalExpression leftChild = listOfChild[0];
                    logicalExpression rightChild = listOfChild[1];

                    bool valueOfLeftChild = LogicalExpressionChecking(leftChild, model);
                    bool valueOfRightChild = LogicalExpressionChecking(rightChild, model);

                    if (valueOfLeftChild && valueOfRightChild){
                        return true;
                    }else if (!valueOfLeftChild && !valueOfRightChild){
                        return true;
                    }

                    return false;
                }
                // if the connective is =>
                else if (connective == "=>"){
                    logicalExpression leftChild = listOfChild[0];
                    logicalExpression rightChild = listOfChild[1];

                    bool valueOfLeftChild = LogicalExpressionChecking(leftChild, model);
                    bool valueOfRightChild = LogicalExpressionChecking(rightChild, model);

                    return (!valueOfLeftChild || valueOfRightChild);
                }
                // if the connective is ||
                else if (connective == "||"){
                    logicalExpression leftChild = listOfChild[0];
                    logicalExpression rightChild = listOfChild[1];

                    bool valueOfLeftChild = LogicalExpressionChecking(leftChild, model);
                    bool valueOfRightChild = LogicalExpressionChecking(rightChild, model);

                    return (valueOfLeftChild || valueOfRightChild);
                }
                // if the connective is &
                else if (connective == "&"){
                    logicalExpression leftChild = listOfChild[0];
                    logicalExpression rightChild = listOfChild[1];

                    bool valueOfLeftChild = LogicalExpressionChecking(leftChild, model);
                    bool valueOfRightChild = LogicalExpressionChecking(rightChild, model);

                    return (valueOfLeftChild && valueOfRightChild);
                }

            }
            // connective is ~
            bool result = LogicalExpressionChecking(listOfChild[0], model);
            return !result;
            
        }

        
        /// PL_TrueKB returns true in case that: with this model, our KB is TRUE
        bool PL_TrueKB(AdvancedKB kb, map<string, bool> model){
            // getting clauses list
            vector<logicalExpression> listOfLEs = kb.getAllLogicalExpression();
            bool output = true;

        
            // traverse every logical expression
            for (int i = 0; i < listOfLEs.size(); i++){
                
                logicalExpression currentLE = listOfLEs[i];
                bool valueOfCurrentLEWithThisModel = LogicalExpressionChecking(currentLE, model); 

                output = output && valueOfCurrentLEWithThisModel;
            }

            // DEBUG print out the output of this model
            // cout << "With this model, our KB value is " << output << endl;
            // DEBUG print out the output of this model
            if (output){
                kbCount++;
                cout << "With this model, our KB is true" << endl;
                for (const auto& pair : model) {
                    cout << pair.first << ": " << pair.second << endl;
                }
            }
            return output;
        }

        map<string, bool> extendModel(string key, bool value, map<string, bool> model){
            // Adding a new key-value pair using the insert() method
            map<string, bool> result;
            result.insert(model.begin(), model.end());
            result.insert(make_pair(key, value));

            return result;
        }

        bool TTCheckAll(AdvancedKB kb, string alp, vector<string> symbols, map<string, bool> model){
            /// if list of symbols is empty
            if (symbols.empty()){
                if (PL_TrueKB(kb, model)){
                    return PL_TrueAlpha(alp, model);
                }
                return true;
            }
            ///else, list of symbols is not empty

            vector<string> listOfSymbolCopy;
            listOfSymbolCopy.assign(symbols.begin(), symbols.end());
            string P = listOfSymbolCopy[0];
            listOfSymbolCopy.erase(listOfSymbolCopy.begin());

            // Generating new model where P is true
            map<string, bool> restUnionWithPTrue = extendModel(P, true, model);

            // Generating new model where P is false
            map<string, bool> restUnionWithPFalse = extendModel(P, false, model);

            return (TTCheckAll(kb, alp, listOfSymbolCopy, restUnionWithPTrue)) && (TTCheckAll(kb, alp, listOfSymbolCopy, restUnionWithPFalse));
        }

        bool TT_Entails(AdvancedKB kb, string alpha){
            /// a list of propositional symbols in KB and alpha
            vector<string> symbols = kb.getSymbolsOfAdvancedKB();

            // checking that alpha is contained in the symbols list or not, if 
            // not, add it to the symbols list
            if (count(symbols.begin(), symbols.end(), alpha) == 0){
                symbols.push_back(alpha);
            }

            map<string, bool> model;
            bool result = TTCheckAll(kb, alpha, symbols, model);
            return result;
        }
    public:
        TruthTableGenericKB(/* args */){
            kbCount = 0;
        }

    void solve(AdvancedKB kb, string query){
        bool result = TT_Entails(kb, query);
        if (result){
            cout << "YES: " << kbCount << endl;
        }
    }
    
};  

#endif