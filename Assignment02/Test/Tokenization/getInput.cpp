#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

vector<string> getEveryExpression(string _input){
    
    // Split the string using ';' as the delimiter
    vector<string> output;
    istringstream iss(_input);
    string temp;
    while (getline(iss, temp, ';')) {
        output.push_back(temp);
    }

    /// removing the "\n"
    output.pop_back();
    return output;
}

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


////CLASS Clause
class Clause{
    private:
    vector<string> premise;
    string conclusion;
    public:
    ///CONSTRUCTION
    Clause(vector<string> _premise, string _conclusion){
        premise = _premise;
        conclusion = _conclusion;
    }

    /// Function returns true if the clause contains premise
    bool containPremise(){
        return (premise.size() > 0);
    }
    
    /// Function returns the list of symbol in premise
    vector<string> getPremise(){
        return premise;
    }

    /// Function returns the conclusion
    string getConclusion(){
        return conclusion;
    }

};


/// CLASS Knowledgebase
class KnowledgeBase{
    private:
        vector<Clause> clauses;
    public:
       /// CONSTRUCTION
        KnowledgeBase(vector<Clause> _clauses){
            clauses = _clauses;
        }

        /// Function returns ALL clauses
        vector<Clause> getAllClauses(){
            return clauses;
        }

        /// Function returns all symbols that are contained in the KB
        vector<string> getSymbols(){
            vector<string> output;

            /// Checking every clause in the knowledge base
            for (int i = 0; i < clauses.size(); i++){
                
                Clause currentClause = clauses[i];
            
                /// if that clause contains premise, else, ignore the premise
                if (currentClause.containPremise()){
                    vector<string> listOfSymbolsInPremise = currentClause.getPremise();
                
                    for (int j = 0; j < listOfSymbolsInPremise.size(); j++){
                        string currentSymbol = listOfSymbolsInPremise[j];

                        ///checking the current symbo is contained in the output or not
                        auto it = find(output.begin(), output.end(), currentSymbol);
                        if (it == output.end()){
                            output.push_back(currentSymbol);
                        }
                    }
                }

                ///checking the current conclusion is contained in the output or not
                string conclusion = currentClause.getConclusion();
                auto it = find(output.begin(), output.end(), conclusion);
                if (it == output.end()){
                    output.push_back(conclusion);
                }
            }

            return output;
        }
};


//// Class TruthTable
class TruthTable{
    private:
        // string kb;
        // string alpha;

    
        bool PL_TrueAlpha(string _query, map<string, bool> model){
            
            ///DEBUG
            cout << "PL_TrueAlpha called, current query is: " << _query << endl;
            cout << "For this model, alpha value is: " << model[_query] << endl;

            // ///checking whether query is contained in the model
            // auto it = model.find(query);

            // /// if the query is in the model
            // if (it != model.end()){
            //     return model[query];
            // }
            

            return model[_query];
        }

        // bool PL_TrueKB(KnowledgeBase kb, map<string, bool> model){
        //     vector<Clause> listOfClause = kb.getAllClauses();
        //     bool finalResult = true;
        //     /// traverse every clause in the knowledge base
        //     for (int i = 0; i < listOfClause.size(); i++){
        //         bool clauseResult;
        //         Clause currentClause = listOfClause[i];
                
        //         /// if the current clause does not contain the premise
        //         if (currentClause.containPremise() == false){
        //             clauseResult = PL_TrueAlpha(currentClause.getConclusion(), model);
        //         }
                
        //         /// if the current clause contains the premise
        //         else{
        //             bool premiseIsTrue = true;
        //             /// traverse every symbol in the premise
        //             vector<string> listOfSymbolsInPremise = currentClause.getPremise();

        //             for (int j = 0; j < listOfSymbolsInPremise.size(); j++){
        //                 string currentPremiseSymbol = listOfSymbolsInPremise[j];
        //                 premiseIsTrue = premiseIsTrue && PL_TrueAlpha(currentPremiseSymbol, model);   
        //             }

        //             clauseResult = !(premiseIsTrue && !PL_TrueAlpha(currentClause.getConclusion(), model));
        //         }

        //         finalResult = finalResult && clauseResult;
        //     }

        //     return finalResult;
        // }

        /// PL_TrueKB returns true in case that: with this model, our KB is TRUE

        bool PL_TrueKB(KnowledgeBase kb, map<string, bool> model){
            // getting clauses list
            vector<Clause> listOfClause = kb.getAllClauses();
            bool output = true;

            ///DEBUG print out the model
            // Traverse and access the keys using a range-based for loop
            cout << "current model is: " << endl;
            for (const auto& pair : model) {
                const string& key = pair.first;
                cout << key << ": " << model[key] << endl;
            }

        
            // traverse every clause
            for (int i = 0; i < listOfClause.size(); i++){
                Clause currentClause = listOfClause[i];
                bool valueOfCurrentClauseWithThisModel = true; 

                /// DEBUG print out the current clause
        
                // if the clause only has the conclusion, 
                if (currentClause.containPremise() == false){
                    cout << currentClause.getConclusion() << endl;
                    valueOfCurrentClauseWithThisModel = model[currentClause.getConclusion()];
                    // cout << "No premise, our conclusion: " << currentClause.getConclusion() << endl;
                } // if the clause has the premise and conclusion
                
                else{
                    vector<string> listOfSymbolsInPremise = currentClause.getPremise();
                    string conclusionOfThisClause = currentClause.getConclusion();

                    // a => b equivalent to !a or b
                    // if the conclusion is true, then this clause is true

                    if (model[conclusionOfThisClause]){
                        // DEBUG

                        // cout << "This clause is: ";
                        // cout << "Premise: ";
                        // for (const string& symbol : listOfSymbolsInPremise){
                        //     cout << symbol << " ";
                            
                        // }
                        // cout << endl << "Conclusion is: " << conclusionOfThisClause << endl;
                        // cout << "The conclusion is true, this clause is true" << endl;
                        valueOfCurrentClauseWithThisModel = true;
                    }
                    /// if the conjunction of every symbol in the premise is false, then this clause is True
                    else{
                        /// traverse every symbols in the premise
                        bool _conjunction = true;
                        // cout << "List of symbols: ";
                        for (const string& symbol : listOfSymbolsInPremise){
                            // cout << symbol << " ";
                            _conjunction = _conjunction && model[symbol];
                        }
                        // cout << endl;
                        valueOfCurrentClauseWithThisModel = valueOfCurrentClauseWithThisModel && !_conjunction;
                    }
                }

                output = output && valueOfCurrentClauseWithThisModel;
            }

            /// print out the output of this model
            cout << "With this model, our KB value is " << output << endl;

            return output;
        }


        map<string, bool> extendModel(string key, bool value, map<string, bool> model){
            // Adding a new key-value pair using the insert() method
            map<string, bool> result;
            result.insert(model.begin(), model.end());
            result.insert(make_pair(key, value));

            return result;
        }
    
        bool TTCheckAll(KnowledgeBase kb, string alp, vector<string> symbols, map<string, bool> model){

            /// if list of symbols is empty
            if (symbols.empty()){
                cout << "empty List reached" << endl;
                if (PL_TrueKB(kb, model)){
                    return PL_TrueAlpha(alp, model);
                }
                cout << "KB is false, return true" << endl;
                return true;
            }
            ///else, list of symbols is not empty
            
            vector<string> listOfSymbolCopy;
            listOfSymbolCopy.assign(symbols.begin(), symbols.end());
            string P = listOfSymbolCopy[0];
            listOfSymbolCopy.erase(listOfSymbolCopy.begin());


            map<string, bool> restUnionWithPTrue = extendModel(P, true, model);
            // Traverse and access the keys using a range-based for loop
            // cout << "P is: " << P << endl;
            // for (const auto& pair : restUnionWithPTrue) {
            //     const string& key = pair.first;
            //     cout << key << ": " << restUnionWithPTrue[key] << endl;
            // }

            map<string, bool> restUnionWithPFalse = extendModel(P, false, model);

            // for (const auto& pair : restUnionWithPFalse) {
            //     const string& key = pair.first;
            //     cout << key << ": " << restUnionWithPFalse[key] << endl;
            // }

            bool a = TTCheckAll(kb, alp, listOfSymbolCopy, restUnionWithPTrue);
            bool b = TTCheckAll(kb, alp, listOfSymbolCopy, restUnionWithPFalse);
            cout << a << " & " << b << endl;
            return (a && b);
            
        }

        bool TT_Entails(KnowledgeBase kb, string alpha){
            /// a list of propositional symbols in KB and alpha
            vector<string> symbols = kb.getSymbols();

            // checking that alpha is contained in the symbols list or not, if 
            // not, add it to the symbols list
            auto it = find(symbols.begin(), symbols.end(), alpha);
            if (it == symbols.end()){
                symbols.push_back(alpha);
            }
        
            map<string, bool> model;
            bool result = TTCheckAll(kb, alpha, symbols, model);
            return result;
        }
    
        public:
            TruthTable(){
    
            }

            string solve(KnowledgeBase kb, string query){
                bool result = TT_Entails(kb, query);

                cout << result << endl;
            }

    //
    
};


int main(){

    string test = "p2=> p3; p3 => p1; c => e; b&e => f; f&g => h; p1=>d; p1&p3 => c; a; b; p2;\n";
    // string test = "a=>b; b=>c; a=>c;\n";
    vector<string> temp = getEveryExpression(test);
    vector<Clause> listOfClauses;
    for (int i = 0; i < temp.size(); i++) {
        string currentClause = removeWhiteSpace(temp[i]);
        string premise;
        string conclusion;

        // cout << "Current clause: " << currentClause << endl;

        // ONLY READ Horn clause
        // If a clause contains "=>", its length must be greater than 3
        if (currentClause.length() > 3) {

            vector<string> listOfSymbolsInPremise;
            // Get the index of '=' in "=>"
            int indexOfEqualSign = -1;
            for (int j = 0; j < currentClause.size(); j++) {
                char current = currentClause[j];
                if (current == '=') {
                    indexOfEqualSign = j;
                    break;
                }
            }

            // Ensure '=' is found, and it's not the first or last character
            if (indexOfEqualSign > 0 && indexOfEqualSign < currentClause.size() - 1) {
                // Getting the list of all symbol in premise 
                premise = removeWhiteSpace(currentClause.substr(0, indexOfEqualSign));
                
                istringstream iss(premise);

                string symbol;
                while (getline(iss, symbol, '&')) {
                    symbol = removeWhiteSpace(symbol);
                    listOfSymbolsInPremise.push_back(symbol);
                }
                // Determine the conclusion of the Horn Clause
                conclusion = removeWhiteSpace(currentClause.substr(indexOfEqualSign + 2));

                Clause newClause = Clause(listOfSymbolsInPremise, conclusion);
                listOfClauses.push_back(newClause);

            } else {
                // // Invalid Horn clause format
                cout << "Invalid Horn clause format: " << currentClause << endl;
                continue;
            }

        } else { // else, the clause contains only one symbol
            // Determine the conclusion of the Horn Clause
            conclusion = currentClause;
            // cout << "YEYSYEYS " << conclusion << endl;
            vector<string> listOfSymbolsInPremise;
            Clause newClause = Clause(listOfSymbolsInPremise, conclusion);
            listOfClauses.push_back(newClause);
        }
    }

    // for (int i = 0; i < listOfClauses.size(); i++){
    //     Clause currentClause = listOfClauses[i];
    //     vector<string> listOfSymbolsInPremise = currentClause.getPremise();
    //     string conclusion = currentClause.getConclusion();


    //     cout << "symbol in premises: ";
    //     for (int j = 0; j < listOfSymbolsInPremise.size(); j++){
    //         cout << listOfSymbolsInPremise[j] << " ";
    //     }
    //     cout << endl << "conclusion: " << conclusion << endl;
    //     cout << "---------------" << endl;
    // }

    KnowledgeBase kb = KnowledgeBase(listOfClauses);
    vector<string> listOfSymbols = kb.getSymbols();

    for (int i = 0; i < listOfSymbols.size(); i++){
        cout << listOfSymbols[i] << " ";
    }
    cout << endl;

    TruthTable tt = TruthTable();
    tt.solve(kb, "d");

    // DEBUG
    // for (int i = 0; i < listOfClauses.size(); i++){
    //     cout << "Current clause is:" << endl;
    //     vector<string> listSymbolsInPremise = listOfClauses[i].getPremise();
    //     cout << "Premise symbols: ";
    //     for (int j = 0; j < listSymbolsInPremise.size(); j++){
    //         cout << listSymbolsInPremise[j] << " ";
    //     }

    //     cout << endl << "Conclusion is: " << listOfClauses[i].getConclusion() << endl;
    // }
    return 0;
}


