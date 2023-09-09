#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

#include "Clause.h"
#include "KnowledgeBase.h"
#include "TruthTableHornClause.h"
#include "GetKnowledgeBase.h"
#include "FC.h"
#include "BC.h"
#include "GetAdvancedKnowledgeBase.h"
#include "AdvancedKB.h"
#include "TruthTableGenericKB.h"


int main(){
    // string test = "p2=> p3; p3 => p1; c => e; b&e => f; f&g => h; p1=>d; p1&p3 => c; a; b; p2;\n";
    // string test = "p1&p2&p3=> p4; p5&p4 => p7; p1 => p2; p1&p2 => p3; p5&p1 => p6; p2&p3=>p5; p1;\n";
    
    // GetKnowledgeBase KBGettingAgent = GetKnowledgeBase();
    // KnowledgeBase kb = KBGettingAgent.getKB(test);
    
    // vector<string> listOfSymbols = kb.getSymbols();


    // TruthTableHornClause tt = TruthTableHornClause();
    // tt.solve(kb, "u");

    // vector<Clause> listClause = kb.getAllClauses();

    // for (int i = 0; i < listClause.size(); i++){
    //     cout << listClause[i].getClauseAsString() << endl;
    // }

    // FC FCAgent = FC();
    // FCAgent.solve(kb, "p7");
    // BC BCAgent = BC();
    // BCAgent.solve(kb, "p7");


    //// GENERIC TESTING
    // string test = "p2 => p3; p3 => p1; c => e; b & e => f; f & g => h; p1 => d; (p1 & p3) => c; a; b; p2;\n";
    string test = "(a <=> (c & d)) & b & (b => a); c; ~f || g;";
    // string test = "(a <=> (c => ~d)) & b & (b => a);\n";
    // string test = "(a => (c & d)) & b & (b => a); c; ~f || g;\n";
    GetAdvancedKnowledgeBase AdvanceKBGettingAgent = GetAdvancedKnowledgeBase();
    AdvancedKB adKB = AdvanceKBGettingAgent.getAdvancedKB(test);

    // vector<logicalExpression> listOfAllLogicalExpression = adKB.getAllLogicalExpression();
    // for (int i = 0; i < listOfAllLogicalExpression.size(); i++){
    //      cout << listOfAllLogicalExpression[i].getOriginalExpression() << endl;
    // }

    // vector<string> listOfAllSymbols = adKB.getSymbolsOfAdvancedKB();
    // for (int i = 0; i < listOfAllSymbols.size(); i++){
    //     cout << listOfAllSymbols[i] << endl; 
    // }

    TruthTableGenericKB TTGenericKB = TruthTableGenericKB();
    TTGenericKB.solve(adKB, "d");

    return 0;

}