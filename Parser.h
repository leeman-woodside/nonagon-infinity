#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "Token.h"

using namespace std;

class Parser {
    public:
    Parser();
    ~Parser();
    
    void parse(vector<Token> myTokens);
    void match(tokenType t);
    
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    
    void scheme();
    void fact();
    void rule();
    void query();
    
    void headPredicate();
    void predicate();
    
    void predicateList();
    void parameterList();
    void stringList();
    void idList();
    
    void parameter();
    void expression();
    void parseOperator();
    
    private:
    vector<Token> myTokens;
    int myIndex = 1;
};

#endif
