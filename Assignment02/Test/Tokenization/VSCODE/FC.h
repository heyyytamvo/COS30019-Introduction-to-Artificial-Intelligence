#ifndef FC_H
#define FC_H

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

#include "KnowledgeBase.h"
#include "Clause.h"
using namespace std;

class FC{
    private:
        queue<string> propositionalSymbol;


        bool FC_ENTAILS(KnowledgeBase kb, string query){
            vector<string> listOfAllSymbol = kb.getSymbols();
            vector<Clause> listOfAllClause = kb.getAllClauses();
            /// Define inferred
            map<string, bool> inferred;

            // adding to inferred
            for (int i = 0; i < listOfAllSymbol.size(); i++){
                string currentSymbol = listOfAllSymbol[i];
                inferred.insert(make_pair(currentSymbol, false));
            }

            // if query is not in the inferred, add it to the inferred
            // Check if query exists using find()
            map<std::string, bool>::iterator it = inferred.find(query);
            if (it == inferred.end()) {
                inferred.insert(make_pair(query, false));
            }

            // define count
            map<string, int> count;

            for (int i = 0; i < listOfAllClause.size(); i++){
                Clause currentClause = listOfAllClause[i];
                string stringClause = currentClause.getClauseAsString();
                count.insert(make_pair(stringClause, currentClause.getPremise().size()));
            }

            // define ageneda
            queue<string> agenda;
            for (int i = 0; i < listOfAllClause.size(); i++){
                Clause currentClause = listOfAllClause[i];
                if (currentClause.containPremise() == false){
                    agenda.push(currentClause.getConclusion());
                }
            }


            //
            while (agenda.empty() == false){
                /* code */
                string currentSymbol = agenda.front();
                agenda.pop();
                propositionalSymbol.push(currentSymbol);

                // cout << "Current symbol: " << currentSymbol << endl;

                if (currentSymbol == query){
                    return true;
                }

                if (inferred[currentSymbol] == false){
                    inferred[currentSymbol] = true;

                    // traverse every clause
                    for (int i = 0; i < listOfAllClause.size(); i++){
                        Clause currentClause = listOfAllClause[i];

                        /// checking "currentSymbol" is in the premise of the current Clause or not
                        if (currentClause.containedInPremise(currentSymbol)){
                            // cout << "Current symbol " << currentSymbol << " is contained in the premise of the clause: " << currentClause.getClauseAsString() << endl; 

                            count[currentClause.getClauseAsString()]--;

                            if (count[currentClause.getClauseAsString()] == 0){
                                agenda.push(currentClause.getConclusion());
                            }
                        } 

                    }
                }
            }
            
            return false;

        }
    public:
        FC(){

        }

        void solve(KnowledgeBase kb, string query){
            bool result = FC_ENTAILS(kb, query);
            if (result){
                cout << "YES: ";

                while (propositionalSymbol.empty() == false){
                    cout << propositionalSymbol.front() << " ";
                    propositionalSymbol.pop();
                }
            }
            else{
                cout << "NO";
            }
            cout << endl;
        }

};
#endif